# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""Provides the object type used to track a wrapped class."""

from .types import JObject, qualified_name_parts_to_qualified_cpp
from .members import construct_member


class _DecorationTracker:
    def __init__(self):
        self.decorations = {}

    def assign_next(self, name):
        decoration = self.decorations.get(name, '')
        decoration_num = decoration
        if not decoration_num:
            decoration_num = 0
        self.decorations[name] = decoration_num + 1
        return decoration


class ClassData:
    """Data for a single Java class."""

    def __init__(self, package, classname):
        """Construct empty class data from a dotted qualified package and class name."""
        self.type = JObject(package.split('.'), classname)
        self.members = []
        self.meta_droppable = True
        self.meta_defer_drop = False
        self._decorations_assigned = False
        self.base = 'ObjectWrapperBase'
        self.base_include = 'ObjectWrapperBase.h'
        self.base_parts = [self.base]
        self.static_init = False
        self.provide_qualified_name = False

    def apply_visitor(self, visitor):
        """Visit children recursively."""
        visitor.visit_class(self)
        for member in self.members:
            member.apply_visitor(visitor)

    def set_base(self, dotted_qualified_name):
        """Set the base class you wish for this type."""
        base = JObject.from_qualified_type_name(dotted_qualified_name)
        self.base_parts = base.parts
        self.base = base.cpp_classname
        self.base_include = f'{base.dotted_package_name}.h'

    def apply_options(self, options):
        """Apply a dictionary of options."""
        if not options:
            return
        if 'base' in options:
            self.set_base(options['base'])
        if 'droppable' in options:
            if options['droppable'] is False:
                self.meta_droppable = False

        if 'provideQualifiedName' in options:
            self.provide_qualified_name = options['provideQualifiedName']

        if 'deferDrop' in options:
            self.meta_defer_drop = options['deferDrop']

        if 'staticInit' in options:
            self.static_init = options['staticInit']
            if self.static_init:
                # implies not droppable
                self.meta_droppable = False

        if 'extraMembers' in options:
            for member_data in options['extraMembers']:
                new_member = construct_member(
                    member_data['name'],
                    member_data['jniSignature'],
                    is_static=member_data['static'],
                    java_prototype=member_data.get('javaPrototype'))

                self.members.append(new_member)

    def assign_decorations(self):
        """Assign decorations to any overloaded member names."""
        if not self._decorations_assigned:
            self._decorations_assigned = True
            decorations = _DecorationTracker()
            for member in self.members:
                decoration = decorations.assign_next(member.name)
                member.set_decoration(decoration)

    @property
    def package_include(self):
        """Get include for this package's wrapper."""
        return '"{}.h"'.format('.'.join(self.type.package))

    def get_declaration_required_includes(self, context=None):
        """
        Get a set of all includes required for the declaration.

        This recursively gets info from each member and all associated classes.

        Includes are double-quoted or bracketed as appropriate.
        """
        includes = set()
        includes.add(f'"{self.base_include}"')
        for member in self.members:
            includes.update(member.get_declaration_required_includes(context))
        includes.discard(self.package_include)

        return includes

    def get_definition_required_includes(self, context=None):
        """
        Get a set of all includes required for the definition.

        This recursively gets info from each member and all associated classes.

        Includes are double-quoted or bracketed as appropriate.
        """
        includes = set()
        for member in self.members:
            includes.update(member.get_definition_required_includes(context))
        includes.discard(self.package_include)

        return includes

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        fwd_decls = set()
        for member in self.members:
            fwd_decls.update(member.get_forward_declarations())
        return fwd_decls

    @property
    def meta_base_name(self):
        """Get the meta class base name."""
        return 'MetaBaseDroppable' if self.meta_droppable else 'MetaBase'

    def get_meta_base_initializer(self):
        """Get the initializer for this class's Meta structure's base type."""
        args = [f'{self.type.cpp_classname}::getTypeName()']
        if self.static_init:
            args.append('clazz')

        return f'{self.meta_base_name}({", ".join(args)})'

    def get_meta_constructor_body(self):
        """Get the body for this class's Meta structure's constructor."""
        if self.meta_defer_drop:
            return 'if (!deferDrop) { MetaBaseDroppable::dropClassRef(); }'
        if self.meta_droppable:
            return 'MetaBaseDroppable::dropClassRef();'
        return ''

    def filter_members(self, membernames):
        """Keep only the members whose name are in the provided list."""
        keepers = set(membernames)
        self.members = list(x for x in self.members
                            if x.name in keepers)
        missing = keepers - set(x.name for x in self.members)
        if missing:
            print("WARNING: Class {} does not have the following requested members: {}".format(
                self.type.qualified_name, missing))

    def generate_meta_constructor_args(self):
        """
        Get the arguments for the meta class.

        Yields (type, name, defaultValue) tuples.
        """
        if self.static_init:
            yield ('jni::jclass', 'clazz', '= nullptr')
        if self.meta_defer_drop:
            yield ('bool', 'deferDrop', '= false')

    def get_decl(self, context=None):
        """Get the header-file part of this class's wrapper."""
        self.assign_decorations()
        members = [x.get_wrapper_decl(context) for x in self.members]
        meta_decls = [x.get_meta_decl(context) for x in self.members]
        minimally_qualified_base = qualified_name_parts_to_qualified_cpp(self.base_parts, context)
        lines = [
            '/*!',
            f' * Wrapper for {self.type.qualified_name} objects.',
            ' */',
            f'class {self.type.cpp_classname}: public {minimally_qualified_base} {{',
            'public:',
            f'using {self.base}::{self.base};',
            'static constexpr const char *getTypeName() noexcept {',
            f'    return "{self.type.slashed_name}";',
            '}',
            '', ]

        if self.provide_qualified_name:
            lines.extend([
                'static constexpr const char *getFullyQualifiedTypeName() noexcept {',
                f'    return "{self.type.qualified_name}";',
                '}',
                '',
            ])

        lines.extend([
            '\n\n'.join(members),
            '',
        ])

        if self.static_init:
            lines.extend([
                '/*!',
                ' * Initialize the static metadata of this wrapper with a known',
                ' * (non-null) Java class.',
                ' */',
                'static void',
                'staticInitClass(jni::jclass clazz)',
                '{',
                f'    Meta::data(clazz{", true" if self.meta_defer_drop else ""});',
                '}',
                '', ])
        arg_decls_with_defaults = [' '.join(x) for x in self.generate_meta_constructor_args()]
        arg_decls = [' '.join(x[:2]) for x in self.generate_meta_constructor_args()]
        args = [x[1] for x in self.generate_meta_constructor_args()]
        lines.extend([
            '/*!',
            ' * Class metadata',
            ' */',
            f'struct Meta : public {self.meta_base_name} {{',
            '\n'.join(meta_decls),
            '',
            '  /*!',
            '   * Singleton accessor',
            '   */',
            f'  static Meta &data({", ".join(arg_decls_with_defaults)}) {{',
            f'      static Meta instance{{ {", ".join(args)} }};',
            '      return instance;',
            '  }',
            '',
            'private:',
            f'  {"explicit " if arg_decls else ""} Meta({", ".join(arg_decls)});',
            '};',
            '};'
        ])
        return '\n'.join(lines)

    def get_inline_implementations(self, context=None):
        """Get the impl-header-file part of this class's wrapper."""
        self.assign_decorations()

        def make_member(x):
            if self.meta_defer_drop and x.is_static:
                # Use our "deferDrop" ability on static members.
                return x.get_wrapper_defn(self.type.cpp_classname,
                                          context,
                                          meta_instance='data',
                                          before='auto &data = Meta::data(true);',
                                          after='data.dropClassRef();')
            return x.get_wrapper_defn(self.type.cpp_classname, context)
        members = [make_member(x) for x in self.members]
        return '\n\n'.join(members)

    def get_meta_constructor(self):
        """Get the full constructor of this class's Meta struct, usually the only thing in the cpp file."""
        self.assign_decorations()
        initializers = [
            self.get_meta_base_initializer()
        ]
        initializers.extend(m.get_meta_initializer() for m in self.members)
        # for this purpose we drop the default value
        arg_decls = (' '.join(x[:2]) for x in self.generate_meta_constructor_args())
        lines = [
            f'{self.type.cpp_classname}::Meta::Meta({", ".join(arg_decls)}) : ',
            ',\n'.join(initializers),
            '{',
            self.get_meta_constructor_body(),
            '}'
        ]
        return '\n'.join(lines)
