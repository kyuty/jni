# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""
Generate an initial draft of some wrapping headers/cpp files.

These are likely to be modified by hand, so re-generation of existing files
should be done only in a version-controlled location, and the changes
should be accepted selectively after clang-format is applied,
to avoid overwriting manual improvements that are infeasible or impractical to
represent concisely in the data format used here.
"""

import json
import logging
from pathlib import PurePath

from .processor import SigExtractor
from .types import JObject, VisitorBase, qualified_name_parts_to_qualified_cpp


def _open_namespace(namespace):
    return f'namespace {namespace} {{'


def _close_namespace(namespace):
    return f'}} // namespace {namespace}'


def _begin_body(package_component_list):
    return '\n'.join((
        _open_namespace('wrap'),
        _open_namespace(qualified_name_parts_to_qualified_cpp(package_component_list)),
    ))


def _end_body(package_component_list):
    return '\n'.join((
        _close_namespace(qualified_name_parts_to_qualified_cpp(package_component_list)),
        _close_namespace('wrap'),
        '',
    ))


class _ClassWrappingVisitor(VisitorBase):
    def __init__(self, wrapped_classes):
        super().__init__()
        self.wrapped_classes = wrapped_classes

    def visit_type(self, t):
        if t.qualified_name in self.wrapped_classes:
            t.has_wrapper = True


def _write_fwd_decls(fwd_decls, fp):
    namespaces_and_classes = (('::'.join(decl[:-1]), decl[-1]) for decl in fwd_decls)
    namespaces = dict()
    for namespace, classname in namespaces_and_classes:
        if namespace not in namespaces:
            namespaces[namespace] = []
        namespaces[namespace].append(classname)

    for namespace in sorted(namespaces.keys()):
        fp.write('namespace %s {\n' % namespace)
        for classname in sorted(namespaces[namespace]):
            fp.write('class %s;\n' % classname)
        fp.write('} // namespace %s\n\n' % namespace)


class _IncludeFixer:

    def __init__(self) -> None:
        self.nondefault_header_ext = None
        self._known_includes = {}
        self._cache = {}

    def add_known_include(self, include: str) -> None:
        path = PurePath(include)
        self._known_includes[path.stem] = f'"{include}"'

    def process(self, include: str) -> str:
        if include.startswith('<'):
            # Can't do better.
            return include
        # Do we have this cached?
        cached = self._cache.get(include)
        if cached:
            return cached

        fn = include[1:-1]
        path = PurePath(fn)

        # Does this match a known stem?
        known = self._known_includes.get(path.stem)
        if known:
            self._cache[include] = known
            return known

        # Change the extension?
        if self.nondefault_header_ext:
            before_ext, dot, ext = fn.rpartition('.')
            if ext == 'h':
                result = f'"{before_ext}.{self.nondefault_header_ext}"'
                self._cache[include] = result
                return result

        # no changes
        self._cache[include] = include
        return include


class _PackageOptions:
    def __init__(self, header_extension: str) -> None:
        self.directory = "wrap"
        self.header_extension = header_extension

    def parse_config(self, options):
        self.directory = options.get("directory", self.directory)


class WrapperWriter:
    def __init__(self, data_filename, framework, extra_classpath=None):

        self._log = logging.getLogger(self.__module__)
        self.only_this_class_type = None
        self.only_this_package = None
        with open(data_filename, 'r') as fp:
            self.data = json.load(fp)
        classpath = [str(framework)]
        if extra_classpath:
            classpath.extend(extra_classpath)
        self.processor = SigExtractor(classpath)
        self.package_data = None

        self._package_options = {}

        # Things changed by global options
        self._include_fixer = _IncludeFixer()
        self.external_include_path = ""
        self.external_include_prefixes = []
        self.header_extension = 'h'

    def handle_arg(self, arg):
        if arg in self.data:
            # This is a package name we were given
            self._log.info("Will only process package %s", arg)
            self.only_this_package = arg
        else:
            self._log.info("Will only process class %s", arg)
            self.only_this_class_type = JObject.from_qualified_type_name(arg)
            self.only_this_package = self.only_this_class_type.dotted_package_name

    def _write_copyright(self, fp):
        fp.write('// Copyright 2020-2021, Collabora, Ltd.\n')
        # This string is broken to avoid confusing REUSE
        fp.write('// SPDX' + '-License-Identifier: BSL-1.0\n')
        fp.write('// Author: Ryan Pavlik <ryan.pavlik@collabora.com>\n\n')

    def _process_include(self, include):
        return self._include_fixer.process(include)

    def write_package_header(self, package, classes):
        self._log.info("Writing header for package %s", package)
        assert(classes)
        package_components = classes[0].type.package
        # fp = sys.stdout

        includes = set()
        fwd_decls = set()
        for classdata in classes:
            if self._should_generate_for_class(classdata):
                includes.update(classdata.get_declaration_required_includes(package_components))
                fwd_decls.update(classdata.get_forward_declarations())

        # Fix up includes
        includes = [self._process_include(f) for f in sorted(includes)]

        options = self._package_options[package]

        with open(f'{options.directory}/{package}.{self.header_extension}', 'w') as fp:
            self._write_copyright(fp)
            fp.write(f'#pragma once\n\n')
            for f in includes:
                fp.write(f'#include {f}\n')
            fp.write('\n')

            if fwd_decls:
                fp.write('namespace wrap {\n')
                _write_fwd_decls(fwd_decls, fp)
                fp.write('} // namespace wrap\n')

            fp.write('\n\n')
            fp.write(_begin_body(package_components))
            fp.write('\n')
            for classdata in classes:
                if not self._should_generate_for_class(classdata):
                    continue
                fp.write(classdata.get_decl(package_components))
                fp.write('\n')
            fp.write(_end_body(package_components))

            fp.write(f'#include "{package}.impl.{self.header_extension}"\n')
            fp.write('\n')

    def write_package_impl_header(self, package, classes):
        self._log.info("Writing impl header for package %s", package)
        assert(classes)
        package_components = classes[0].type.package
        # fp = sys.stdout

        includes = set()
        for classdata in classes:
            if self._should_generate_for_class(classdata):
                includes.update(classdata.get_definition_required_includes(package_components))

        # Fix up includes
        includes = [self._process_include(f) for f in sorted(includes)]

        options = self._package_options[package]

        with open(f'{options.directory}/{package}.impl.{self.header_extension}', 'w') as fp:
            self._write_copyright(fp)
            fp.write(f'#pragma once\n\n')
            for f in includes:
                fp.write(f'#include {f}\n')

            fp.write('\n\n')
            fp.write(_begin_body(package_components))
            fp.write('\n')
            for classdata in classes:
                if not self._should_generate_for_class(classdata):
                    continue
                fp.write(classdata.get_inline_implementations(package_components))
                fp.write('\n')
            fp.write(_end_body(package_components))
            fp.write('\n')

    def write_package_impl(self, package, classes):
        self._log.info("Writing impl cpp for package %s", package)
        assert(classes)
        package_components = classes[0].type.package

        options = self._package_options[package]

        with open(f'{options.directory}/{package}.cpp', 'w') as fp:
            self._write_copyright(fp)
            fp.write(f'#include "{package}.{self.header_extension}"\n\n')
            fp.write(_begin_body(package_components))
            fp.write('\n')
            for classdata in classes:
                if not self._should_generate_for_class(classdata):
                    continue
                fp.write(classdata.get_meta_constructor())
                fp.write('\n')
            fp.write(_end_body(package_components))
            fp.write('\n')

    def _should_generate_for_package(self, package):
        if self.only_this_package and self.only_this_package != package:
            return False
        return True

    def _should_generate_for_class_name(self, className):
        if self.only_this_class_type and self.only_this_class_type.qualified_name != className:
            return False
        return True

    def _should_generate_for_class(self, classdata):
        return self._should_generate_for_class_name(classdata.type.qualified_name)

    def handle_global_options(self, options):
        known_includes = options.get('knownIncludes')
        if known_includes:
            for elt in known_includes:
                self._include_fixer.add_known_include(elt)
        header_extension = options.get('headerExtension')
        if header_extension:
            self._include_fixer.nondefault_header_ext = header_extension
            self.header_extension = header_extension

    def load_classes(self):
        self._log.info("Loading classes")
        package_data = {}
        self.package_data = package_data
        known_classes = set()

        global_options = self.data.get('$globalOptions')
        if global_options:
            self.handle_global_options(global_options)

        for package, classes in self.data.items():
            if package[0] in ('$', '#'):
                continue

            known_classes.update('{}.{}'.format(package, classname) for classname in classes)
            classes_data = []
            package_data[package] = classes_data

            generate_package = self._should_generate_for_package(package)

            package_options = _PackageOptions(self.header_extension)
            self._package_options[package] = package_options

            for classname, membernames in classes.items():
                if classname[0] == '#':
                    continue

                if classname == '$packageOptions':
                    package_options.parse_config(membernames)
                    continue

                generate_class = generate_package and self._should_generate_for_class_name(classname)
                if generate_class:
                    classdata = self.processor.extract_class(package, classname)
                else:
                    classdata = self.processor.mock_class(package, classname)

                # First element of the member list can actually be an options dict.
                if membernames and isinstance(membernames[0], dict):
                    classdata.apply_options(membernames[0])
                    membernames = membernames[1:]

                if generate_class:
                    classdata.filter_members(membernames)
                classes_data.append(classdata)

        visitor = _ClassWrappingVisitor(known_classes)

        for classdata in self.processor.classes.values():
            classdata.assign_decorations()
            classdata.apply_visitor(visitor)

    def output_code(self):
        for package, classes in self.package_data.items():
            if not classes:
                continue
            if not self._should_generate_for_package(package):
                continue
            self.write_package_header(package, classes)
            self.write_package_impl(package, classes)
            self.write_package_impl_header(package, classes)
