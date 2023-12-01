# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0

import subprocess
from io import StringIO
import platform
import logging

from .class_data import ClassData
from .file_process import LinewiseFileProcessor
from .members import Constructor, construct_member


class SigExtractor(LinewiseFileProcessor):
    """Class to extract useful data from javap"""

    def __init__(self, classpath):
        super().__init__()
        self._log = logging.getLogger(self.__module__)
        self.classes = {}
        self.classpath = classpath
        delim = ";" if platform.system() == "Windows" else ":"
        self.classpath_param = delim.join(self.classpath)

    def extract_class(self, package, classname):
        """Run javap and extract data on a class type."""
        clazz = f"{package}.{classname}"
        self._log.info("Extracting data on class type %s", clazz)
        cmd = ['javap', "-s", "-public", "-classpath",
               self.classpath_param, clazz]
        self._log.debug("Running javap: %s", str(cmd))
        proc = subprocess.run(cmd, capture_output=True, check=True, encoding='utf-8')

        self._log.debug("output:\n%s", proc.stdout)
        classdata = ClassData(package, classname)
        self.classes[clazz] = classdata
        self.members = self.classes[clazz].members
        self.process_file(filename="stdout", file_handle=StringIO(proc.stdout))
        classdata.assign_decorations()
        return classdata

    def mock_class(self, package, classname):
        """Act like extract_class but don't actually run javap."""
        clazz = f"{package}.{classname}"
        self._log.info("Generating mock object for class type %s", clazz)
        classdata = ClassData(package, classname)
        self.classes[clazz] = classdata
        classdata.assign_decorations()
        return classdata

    def _process_named(self, decl, java_prototype):
        declaration_parts = decl.strip().split()
        # print(declaration_parts)
        # drop access modifier
        declaration_parts = declaration_parts[1:]

        is_static = False

        while declaration_parts and declaration_parts[0] in ('abstract', 'static', 'final', 'native', 'default'):
            if declaration_parts[0] == 'static':
                is_static = True

            declaration_parts = declaration_parts[1:]

        signature = self.next_line.strip().replace('descriptor: ', '')
        if len(declaration_parts) == 1:
            member = Constructor(signature, java_prototype, name=declaration_parts[0])
        else:

            name = declaration_parts[1]
            if name == 'void':
                print("Think we forgot to drop some keyword: ", declaration_parts)
            # if '.' in name:
            #     # conversion? skip now
            #     return
            member = construct_member(name, signature, java_prototype, is_static)

        if member:
            self.members.append(member)

    def process_line(self, line_num, line):
        """Internal method implementation used by LinewiseFileProcessor."""
        # print(line_num, line)
        if "public" not in line:
            return

        if "class" in line:
            return
        if "interface" in line:
            return
        if "(" in line:
            parts = line.strip().split("(")
            self._process_named(parts[0], line.strip())
            return

        self._process_named(self.line_rstripped.rstrip(';'), line.strip())
