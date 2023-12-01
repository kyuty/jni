# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""
Types used in producing JNI wrappers.

The classes defined here are for representing a Java
type with an object.
"""

from itertools import takewhile

_TYPELETTERS = {
    'Z': 'jboolean',
    'B': 'jbyte',
    'C': 'jchar',
    'S': 'jshort',
    'I': 'jint',
    'J': 'jlong',
    'F': 'jfloat',
    'D': 'jdouble',
    'V': 'void',
}

_LETTERS_FOR_TYPES = {typename: letter
                      for letter, typename in _TYPELETTERS.items()}

# slashed name to the C++ version known by JNIPP
_JNI_TO_CPP = {
    'boolean': 'bool',
    'byte': 'int8_t',
    'char': 'uint16_t',
    'short': 'int16_t',
    'int': 'int32_t',
    'long': 'int64_t',
    'float': 'float',
    'double': 'double',
    'void': 'void',
    'java/lang/String': 'std::string',
}


def _common_prefix(a, b):
    return tuple(takewhile(lambda pair: (pair[0] == pair[1]), zip(a, b)))


def qualified_name_parts_to_qualified_cpp(parts, context=None):
    """
    Get a namespace-qualified C++ name from a list of Java name parts.

    If a list of namespaces is provided in `context`, the type name may be able to be shortened.

    >>> qualified_name_parts_to_qualified_cpp(['java', 'lang', 'Class'])
    'java::lang::Class'

    >>> qualified_name_parts_to_qualified_cpp(['java', 'lang', 'Class'], ['java'])
    'lang::Class'

    >>> qualified_name_parts_to_qualified_cpp(['java', 'lang', 'Class'], ['android', 'content'])
    'java::lang::Class'
    """
    relative_parts = parts
    if context:
        relative_parts = parts[len(_common_prefix(parts, context)):]
    # Handle nested types
    relative_parts[-1] = relative_parts[-1].replace('$', '_')
    return '::'.join(relative_parts)


class VisitorBase:
    """Base type for a visitor."""

    def visit_type(self, t):
        """Visit a type."""
        pass

    def visit_member(self, member):
        """Visit a class member."""
        pass

    def visit_class(self, classdata):
        """Visit class data."""
        pass


class _TypeBase:
    """
    Base class for types.

    Deduplication through inheritance instead of composition,
    because that's OK for this purpose right now.
    """

    @property
    def jnipp_return_type(self):
        """Get the C++ type we should ask JNIPP for."""
        raise NotImplementedError()

    def get_cpp_return_type(self, context=None):
        """Get the type that should be returned from a C++ function."""
        return self.jnipp_return_type

    def get_cpp_param_type(self, context=None):
        """Get the type that should be passed into a C++ function."""
        return self.get_cpp_return_type(context) + "&"

    def apply_visitor(self, visitor):
        """Visit children recursively."""
        visitor.visit_type(self)

    def get_required_includes(self, context=None):
        """
        Get a set of all required includes.

        Includes are double-quoted or bracketed as appropriate.
        """
        return set()

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        return set()

    def get_as_jnipp_param(self, param_name):
        """
        Return an expression that unwraps param_name for passing to jnipp, if required.

        Default implementation is an identity function.
        """
        return param_name

    def convert_expression_from_jnipp(self, expression, context=None):
        """
        Return an expression that wraps expression to return from jnipp, if required.

        Default implementation is an identity function.
        """
        return expression

    def suggest_param_name(self):
        """Get a suggested parameter name for a param of this type."""
        return "p"


class Array(_TypeBase):
    """Wraps an array type."""

    def __init__(self, t):
        """
        Construct an array type.

        t should be another TypeBase-derived (or -resembling) object
        describing the element type.
        """
        super().__init__()
        self.element_type = t

    def apply_visitor(self, visitor):
        """Visit children recursively."""
        super().apply_visitor(visitor)
        self.element_type.apply_visitor(visitor)

    @property
    def known_to_jnipp(self):
        """Report whether JNIPP natively understands this type."""
        return self.element_type.known_to_jnipp

    @property
    def qualified_name(self):
        """Get the fully qualified Java type name."""
        return "{}[]".format(self.element_type.qualified_name)

    @property
    def jnipp_return_type(self):
        """
        Get the C++ type we should ask JNIPP for.

        >>> Array(PrimitiveType("jint")).jnipp_return_type
        'jni::Array<int32_t>'

        >>> Array(JObject.from_slashed_type_name("java/lang/ClassLoader")).jnipp_return_type
        'jni::Array<jni::Object>'

        >>> Array(JObject.from_slashed_type_name("java/lang/String")).jnipp_return_type
        'jni::Array<std::string>'
        """
        return 'jni::Array<{}>'.format(self.element_type.jnipp_return_type)

    def jni_signature(self):
        """Get the JNI signature type indication.

        >>> Array(PrimitiveType("jint")).jni_signature()
        '[I'

        >>> Array(JObject.from_slashed_type_name("java/lang/String")).jni_signature()
        '[Ljava/lang/String;'
        """
        return '[' + self.element_type.jni_signature()

    def has_nested_class(self):
        """
        Check if there's a nested class name in this type.

        Right now we don't handle nested classes, so this is
        transitive-"skip me".
        """
        return self.element_type.has_nested_class

    def get_required_includes(self, context=None):
        """
        Get a set of all required includes.

        Includes are double-quoted or bracketed as appropriate.
        """
        return self.element_type.get_required_includes(context)

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        return self.element_type.get_forward_declarations()

    def suggest_param_name(self):
        """Get a suggested parameter name for a param of this type."""
        return self.element_type.suggest_param_name() + "Array"

    def __repr__(self):
        """Format a representation of this object."""
        return "Array({})".format(repr(self.element_type))


class JObject(_TypeBase):
    """Wraps an Object type."""

    def __init__(self, package, classname):
        """
        Construct a Java object type

        Args:
            package (iterable): list of package levels
            classname (str): name of class
             (nested classes use $)
        """
        super().__init__()
        self.package = package
        self.classname = classname
        # Un-nest nested classes for simplicity.
        self.cpp_classname = classname.replace('$', '_')
        self.parts = package[:]
        self.parts.append(classname)
        self.cpp_parts = package[:]
        self.cpp_parts.append(self.cpp_classname)
        self.slashed_name = '/'.join(self.parts)
        self.has_wrapper = False

    @classmethod
    def from_slashed_type_name(cls, slashed_name):
        """
        Construct a Java object type from its slash-delimited name.

        To construct from the fully-qualified .-delimited name,
        see `JObject.from_qualified_type_name()`

        >>> JObject.from_slashed_type_name("java/lang/String")
        JObject.from_slashed_type_name('java/lang/String')

        >>> JObject.from_slashed_type_name("java/lang/String").parts
        ['java', 'lang', 'String']

        >>> JObject.from_slashed_type_name("java/lang/String").package
        ['java', 'lang']

        >>> JObject.from_slashed_type_name("java/lang/String").classname
        'String'

        >>> JObject.from_slashed_type_name("android/net/Uri$Builder").classname
        'Uri$Builder'

        >>> JObject.from_slashed_type_name("android/net/Uri$Builder").cpp_classname
        'Uri_Builder'
        """
        
        parts = slashed_name.split('/')
        package = parts[:-1]
        classname = parts[-1]
        return cls(package, classname)

    @classmethod
    def from_qualified_type_name(cls, qualified):
        """
        Construct a Java object type from its fully-qualified .-delimited name.

        >>> JObject.from_qualified_type_name("java.lang.String")
        JObject.from_slashed_type_name('java/lang/String')

        >>> JObject.from_qualified_type_name("java.lang.String").parts
        ['java', 'lang', 'String']

        >>> JObject.from_qualified_type_name("java.lang.String").package
        ['java', 'lang']

        >>> JObject.from_qualified_type_name("java.lang.String").classname
        'String'

        >>> JObject.from_qualified_type_name("android.net.Uri.Builder").classname
        'Uri$Builder'

        >>> JObject.from_slashed_type_name("android/net/Uri$Builder").cpp_classname
        'Uri_Builder'
        """
        parts = qualified.split('.')
        package = parts[:-1]
        classname = parts[-1]
        first_letter_of_deepest_package = package[-1][0]
        if first_letter_of_deepest_package.upper() == first_letter_of_deepest_package:
            # Heuristic: This is probably a nested class.
            classname = '$'.join(parts[-2:])
            package = parts[:-2]
        return cls(package, classname)

    def get_required_includes(self, context=None):
        """
        Get a set of all required includes.

        Includes are double-quoted or bracketed as appropriate.
        """
        includes = set()
        if self.slashed_name == 'java/lang/String':
            includes.add("<string>")
        if self.has_wrapper and context != self.package:
            incl = '.'.join(self.package)
            includes.add(f'"{incl}.h"')
        return includes

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        fwd_decls = set()
        if self.has_wrapper:
            fwd_decls.add(tuple(self.cpp_parts))
        return fwd_decls

    def get_as_jnipp_param(self, param_name):
        """
        Return an expression that unwraps param_name for passing to jnipp, if required.

        Default implementation is an identity function.
        """
        if not self.has_wrapper:
            return param_name
        return f'{param_name}.object()'

    def suggest_param_name(self):
        """Get a suggested parameter name for a param of this type."""
        return self.cpp_classname[0].lower() + self.cpp_classname[1:]

    def convert_expression_from_jnipp(self, expression, context=None):
        """
        Return an expression that wraps expression to return from jnipp, if required.

        Default implementation is an identity function.
        """
        if not self.has_wrapper:
            return expression
        qualified_cpp_name = qualified_name_parts_to_qualified_cpp(self.parts, context)
        return f'{qualified_cpp_name}({expression})'

    def get_cpp_return_type(self, context=None):
        """
        Get the type that should be returned from a C++ function.

        If a list of namespaces is provided in `context`, the type name may be able to be shortened.

        >>> JObject.from_slashed_type_name("java/lang/String").get_cpp_return_type()
        'std::string'

        >>> JObject.from_slashed_type_name("java/lang/ClassLoader").get_cpp_return_type()
        'jni::Object'


        >>> classloader = JObject.from_slashed_type_name("java/lang/ClassLoader")
        >>> classloader.has_wrapper = True
        >>> classloader.get_cpp_return_type()
        'java::lang::ClassLoader'

        >>> classloader.get_cpp_return_type(['java'])
        'lang::ClassLoader'
        """
        if not self.has_wrapper:
            return self.jnipp_return_type
        return qualified_name_parts_to_qualified_cpp(self.parts, context)

    @property
    def qualified_name(self):
        """Get the fully-qualified .-delimited Java type name."""
        return '.'.join(self.package + [self.classname])

    @property
    def known_to_jnipp(self):
        """
        Report whether JNIPP natively understands this type.

        >>> JObject.from_slashed_type_name("java/lang/String").known_to_jnipp
        True

        >>> JObject.from_slashed_type_name("java/lang/ClassLoader").known_to_jnipp
        False
        """
        return self.slashed_name in _JNI_TO_CPP

    @property
    def jnipp_return_type(self):
        """
        Get the C++ type we should ask JNIPP for.

        >>> JObject.from_slashed_type_name("java/lang/String").jnipp_return_type
        'std::string'

        >>> JObject.from_slashed_type_name("java/lang/ClassLoader").jnipp_return_type
        'jni::Object'
        """
        return _JNI_TO_CPP.get(self.slashed_name, 'jni::Object')

    @property
    def dotted_package_name(self):
        """
        Get the .-delimited Java package name.

        >>> JObject.from_slashed_type_name("java/lang/String").dotted_package_name
        'java.lang'
        """
        return '.'.join(self.package)

    def jni_signature(self):
        """Get the JNI signature type indication.

        >>> JObject.from_slashed_type_name("java/lang/String").jni_signature()
        'Ljava/lang/String;'

        >>> JObject(["android", "net"], 'Uri$Builder').jni_signature()
        'Landroid/net/Uri$Builder;'

        >>> JObject.from_slashed_type_name("android/net/Uri$Builder").jni_signature()
        'Landroid/net/Uri$Builder;'
        """
        return 'L{};'.format(self.slashed_name)

    def has_nested_class(self):
        """
        Check if there's a nested class name in this type.

        Right now we don't handle nested classes, so this is
        transitive-"skip me".
        """
        return "$" in self.slashed_name

    def __repr__(self):
        """Format a representation of this object."""
        return "JObject.from_slashed_type_name({})".format(repr(self.slashed_name))


class PrimitiveType(_TypeBase):
    """Wraps a basic/primitive type."""

    def __init__(self, name):
        """
        Construct a primitive type from its JNI-defined type name.

        Usually this name starts with 'j'.

        >>> PrimitiveType("jint").name
        'jint'

        >>> PrimitiveType("jint").cpptype
        'int32_t'

        >>> PrimitiveType("void").name
        'void'
        """
        super().__init__()
        assert(name != 'jobject')
        assert(name != 'jstring')
        self.name = name
        self.cpptype = _JNI_TO_CPP[self.qualified_name]

    @property
    def known_to_jnipp(self):
        """Report whether JNIPP natively understands this type."""
        return True

    @property
    def qualified_name(self):
        """
        Get the fully qualified Java type name.

        This is the primitive type name, not the boxed type name.

        >>> PrimitiveType("jint").qualified_name
        'int'

        >>> PrimitiveType("void").qualified_name
        'void'
        """
        return self.name.lstrip('j')

    @property
    def slashed_name(self):
        """
        Get the slash-delimited name.

        For these types, it's the same as `.qualified_name`
        """
        return self.qualified_name

    def jni_signature(self):
        """Get the JNI signature type indication.

        >>> PrimitiveType("jint").jni_signature()
        'I'

        >>> PrimitiveType("void").jni_signature()
        'V'

        >>> PrimitiveType("jboolean").jni_signature()
        'Z'
        """
        return _LETTERS_FOR_TYPES[self.name]

    def has_nested_class(self):
        """Get False, since primitive types are not nested types."""
        return False

    @property
    def jnipp_return_type(self):
        """
        Get the C++ type we should ask JNIPP for.

        >>> PrimitiveType("jint").jnipp_return_type
        'int32_t'

        >>> PrimitiveType("void").jnipp_return_type
        'void'
        """
        return self.cpptype

    def suggest_param_name(self):
        """Get a suggested parameter name for a param of this type."""
        return self.qualified_name + "Param"

    def get_cpp_param_type(self, context=None):
        """
        Get the type that should be passed into a C++ function.

        Overriding base implementation: no need to pass these by reference.

        >>> PrimitiveType("jint").get_cpp_param_type()
        'int32_t'

        >>> PrimitiveType("void").get_cpp_param_type()
        'void'
        """
        # Override - no need to pass by ref.
        return self.jnipp_return_type

    def __repr__(self):
        """Format a representation of this object."""
        return "BasicType({})".format(repr(self.name))


def _parse_signature(in_str):
    """Parse a single type from a signature, returning that type and the remaining string."""
    if not in_str:
        return
    char = in_str[0]
    if char == '[':
        # this is an array: parse the element type
        s, t = _parse_signature(in_str[1:])
        # wrap the element type
        return s, Array(t)
    if char == 'L':
        # this is an object type, terminated by ;
        name, _, rest = in_str[1:].partition(';')
        return rest, JObject.from_slashed_type_name(name)

    # This is presumably a primitive type if we got this far.
    t = _TYPELETTERS.get(char)
    assert(t)
    return in_str[1:], PrimitiveType(t)


def parse_signature(s):
    """Return a list of parameter types (if any) and the return type."""
    if not s:
        return
    # Using lists for both these here since they are reference types:
    # we can make `dest` point to either one.
    params = []
    return_types = []
    dest = return_types
    while s:
        if s[0] == ')':
            # End param parsing
            dest = return_types
            s = s[1:]
            continue
        if s[0] == '(':
            # Start param parsing
            dest = params
            s = s[1:]
            continue
        s, output = _parse_signature(s)
        if not output:
            break
        dest.append(output)

    # We'll always have one of these, unless something is bad
    assert(return_types)
    return params, return_types[0]


if __name__ == "__main__":
    import doctest
    doctest.testmod()
