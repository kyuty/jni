# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""
Member types used in producing JNI wrappers.

The classes defined are for Java type members: methods and fields.
"""
from .types import parse_signature, JObject


# names we'd rather not use for parameters.
_BANISHED_PARAM_NAMES = set((
    'string',
    'class',
))


class Member:
    """Base class of fields and methods."""

    def __init__(self, name, signature, java_prototype, is_static):
        """Construct this base."""
        self.name = name
        self.signature = signature
        self.java_prototype = java_prototype
        self.is_static = is_static
        self.decoration = ''

    def __str__(self):
        """Convert to string."""
        return repr(self)

    def set_decoration(self, decoration):
        """Set a name "decoration" to disambiguate overloaded names."""
        self.decoration = decoration

    @property
    def decorated_name(self):
        """Get the name including the previously-set "decoration"."""
        return self.name + str(self.decoration)

    @property
    def static_capitalized(self):
        """Get the word Static if this is static."""
        return "Static" if self.is_static else ""

    @property
    def the_word_static_and_a_space(self):
        """Get "static " if this is static."""
        return "static " if self.is_static else ""

    def get_invocation_target(self, meta_instance):
        """Get the thing that we work on when we invoke this."""
        return f"{meta_instance}.clazz()" if self.is_static else "object()"

    def get_declaration_required_includes(self, context=None):
        """
        Get a set of all includes required for the declaration.

        Includes are double-quoted or bracketed as appropriate.
        """
        return set()

    def get_comment_lines(self):
        """Get a list of lines comprising the wrapper function's comment."""
        lines = [
            f'/*!',
            f' * {self.get_comment_text()}',
            f' *',
        ]
        if self.java_prototype:
            lines.extend([
                f' * Java prototype:',
                f' * `{self.java_prototype}`',
                f' *',
            ])
        lines.extend([
            f' * JNI signature: {self.signature}',
            f' *',
            f' */',
        ])
        return lines

    def make_wrapper_decl(self, decl):
        """
        Make a wrapper declaration.

        Utility function for derived classes to use in their get_wrapper_decl method.
        """
        lines = self.get_comment_lines()
        lines.append(decl + ';')
        return '\n'.join(lines)

    def make_wrapper_impl(self, decl, return_expression, before=None, after=None):
        """
        Make a wrapper implementation.

        Utility function for derived classes to use in their get_wrapper_impl method.
        """
        lines = []
        lines.append(decl + ' {')
        indent = ' ' * 4
        if not self.is_static:
            lines.append(indent + 'assert(!isNull());')
        if before:
            lines.append(before)

        if after:
            lines.append(indent + f'auto ret = {return_expression};')
            lines.append(after)
            lines.append(indent + 'return ret;')
        else:
            lines.append(indent + f'return {return_expression};')
        lines.append('}')
        return '\n'.join(lines)


class Method(Member):
    """A class method."""

    def __init__(self, name, signature, java_prototype=None, is_static=False):
        """
        Construct a class method.

        The class it belongs to is implied by its container,
        and isn't specified in this object at all.
        """
        super().__init__(name, signature, java_prototype, is_static)
        self.params, self.return_type = parse_signature(signature)

    def __repr__(self):
        """Format a representation of this object."""
        return "Method({}, {}, {}, {})".format(
            repr(self.name), repr(self.signature), repr(self.java_prototype), repr(self.is_static))

    def has_nested_class(self):
        """
        Check if there's a nested class name referenced in this method.

        Right now we don't handle nested classes, so this is
        transitive-"skip me".
        """
        return (any(x.has_nested_class() for x in self.params)
                or self.return_type.has_nested_class())

    def get_definition_required_includes(self, context=None):
        """
        Get a set of all includes required for the definition.

        Includes are double-quoted or bracketed as appropriate.
        """
        includes = set(self.return_type.get_required_includes(context))
        for t in self.params:
            includes.update(t.get_required_includes(context))
        return includes

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        fwd_decls = set()
        fwd_decls.update(self.return_type.get_forward_declarations())
        for t in self.params:
            fwd_decls.update(t.get_forward_declarations())
        return fwd_decls

    def get_meta_decl(self, context=None):
        """Get the member declaration for the C++ Meta structure."""
        return f"jni::method_t {self.decorated_name};"

    def get_meta_initializer(self):
        """Get the member initializer for the C++ Meta constructor."""
        return f'{self.decorated_name}(classRef().get{self.static_capitalized}Method("{self.name}", "{self.signature}"))'

    def get_comment_text(self):
        """Get the text of the comment."""
        return f'Wrapper for the {self.name} {self.the_word_static_and_a_space}method'

    def apply_visitor(self, visitor):
        """Visit children recursively."""
        visitor.visit_member(self)
        self.return_type.apply_visitor(visitor)
        for t in self.params:
            t.apply_visitor(visitor)

    @property
    def _invocation_method(self):
        return f'call<{self.return_type.jnipp_return_type}>'

    @property
    def _wrapper_name(self):
        return self.name

    def _get_param_names(self, context=None):
        param_types = []
        param_names = []
        param_name_set = set()
        for i, t in enumerate(self.params):
            param_types.append(t.get_cpp_param_type(context))
            name = t.suggest_param_name()
            if name in _BANISHED_PARAM_NAMES:
                name = name + "Param"
            while name in param_name_set:
                # Just in case we have really bad luck
                name = name + str(i)
            param_name_set.add(name)
            param_names.append(name)
        return param_types, param_names

    def get_wrapper_decl(self, context=None):
        """
        Get the wrapped method declaration for the C++ wrapper object.
        """
        decl = []
        if self.is_static:
            decl.append('static')

        param_types, param_names = self._get_param_names(context)
        decl.extend([
            self.return_type.get_cpp_return_type(context),
            self._wrapper_name,
            '(',

            ', '.join('{} {}'.format(t, n)
                      for t, n in zip(param_types, param_names)),
            ')',
        ])
        return self.make_wrapper_decl(
            decl=' '.join(decl)
        )

    def get_wrapper_defn(self, cpp_classname, context=None, meta_instance='Meta::data()', **kwargs):
        """
        Get the wrapped method implementation for the C++ wrapper object.

        This all lives "inline" in the "impl" header file to reduce call overhead.
        """
        decl = ['inline']

        param_types, param_names = self._get_param_names(context)

        decl.extend([
            self.return_type.get_cpp_return_type(context),
            f'{cpp_classname}::{self._wrapper_name}',
            '(',

            ', '.join('{} {}'.format(t, n)
                      for t, n in zip(param_types, param_names)),
            ')',
        ])

        args = [f'{meta_instance}.{self.decorated_name}']
        args.extend(t.get_as_jnipp_param(n)
                    for t, n in zip(self.params, param_names))

        call = [
            self.get_invocation_target(meta_instance),
            f'.{self._invocation_method}(',
            ', '.join(args),
            ')',
        ]

        call_str = self.return_type.convert_expression_from_jnipp(''.join(call), context)
        return self.make_wrapper_impl(
            decl=' '.join(decl),
            return_expression=call_str,
            **kwargs
        )


class Constructor(Method):
    """A specialized method with a special name."""

    MEMBER_NAME = '<init>'

    def __init__(self, signature, java_prototype, name=None):
        """
        Construct a constructor.

        The usual parameters are either implied or don't make sense.
        """
        super().__init__(self.MEMBER_NAME, signature, java_prototype, True)
        self.return_type = JObject.from_qualified_type_name(name)

    def __repr__(self):
        """Format a representation of this object."""
        return "Constructor({}, {})".format(repr(self.signature, self.java_prototype))

    def get_required_includes(self, context=None):
        """
        Get a set of all required includes.

        Includes are double-quoted or bracketed as appropriate.
        """
        return set()

    def get_meta_initializer(self):
        """Get the member initializer for the C++ Meta constructor."""
        return f'{self.decorated_name}(classRef().getMethod("{self.name}", "{self.signature}"))'

    @property
    def decorated_name(self):
        """
        Get the name including the previously-set "decoration".

        Overridden because <init> isn't a valid C++ member name.
        """
        return 'init' + str(self.decoration)

    # The stuff here is to make the regular Method wrapper generate our constructor wrappers correctly.

    def get_comment_text(self):
        """Get the text of the comment."""
        return f'Wrapper for a constructor'

    @property
    def _invocation_method(self):
        return f'newInstance'

    @property
    def _wrapper_name(self):
        return "construct"

    def get_invocation_target(self, meta_instance):
        """Get the thing that we work on when we invoke this."""
        return f"{meta_instance}.clazz()"


class Field(Member):
    """A static or object field."""

    def __init__(self, name, signature, java_prototype=None, is_static=False):
        """
        Construct a field.

        >>> Field("myField", "I")
        Field('myField', 'I', None, False)

        >>> Field("myStringField", "Ljava/lang/String;")
        Field('myStringField', 'Ljava/lang/String;', None, False)
        """
        super().__init__(name, signature, java_prototype, is_static)
        _, self.type = parse_signature(signature)

    def __repr__(self):
        """Format a representation of this object."""
        return "Field({}, {}, {}, {})".format(
            repr(self.name), repr(self.signature), repr(self.java_prototype), repr(self.is_static))

    def apply_visitor(self, visitor):
        """Visit children recursively."""
        visitor.visit_member(self)
        self.type.apply_visitor(visitor)

    def get_declaration_required_includes(self, context=None):
        """
        Get a set of all includes required for the declaration.

        Includes are double-quoted or bracketed as appropriate.
        """
        if self.type.known_to_jnipp or self._type_has_wrapper:
            return self.type.get_required_includes(context)
        return set()

    def get_definition_required_includes(self, context=None):
        """
        Get a set of all includes required for the declaration.

        Includes are double-quoted or bracketed as appropriate.
        """
        if self.type.known_to_jnipp or self._type_has_wrapper:
            return set()
        return self.type.get_required_includes(context)

    def get_forward_declarations(self):
        """
        Get a set of all required forward declarations.

        Each element is a tuple of namespaces.
        """
        return self.type.get_forward_declarations()

    def get_comment_text(self):
        """Get the text of the comment."""
        return f'Getter for the {self.name} {self.the_word_static_and_a_space}field value'

    @property
    def return_type(self):
        """
        Get the type of the field.

        This is provided to allow return_type to be used on all members.
        """
        return self.type

    def get_meta_decl(self, context=None):
        """
        Get the member declaration for the C++ Meta structure.

        In some cases we use a custom wrapper in impl:: instead of just `jni::field_t`

        >>> Field("myField", "I").get_meta_decl()
        'impl::FieldId<int32_t> myField;'

        >>> Field("myStaticField", "I", is_static=True).get_meta_decl()
        'impl::StaticFieldId<int32_t> myStaticField;'

        >>> Field("myStringField", "Ljava/lang/String;").get_meta_decl()
        'impl::FieldId<std::string> myStringField;'

        >>> f = Field("myClassField", "Ljava/lang/Class;")
        >>> f.type.has_wrapper = True
        >>> f.get_meta_decl()
        'impl::WrappedFieldId<java::lang::Class> myClassField;'

        >>> f.get_meta_decl(['java'])
        'impl::WrappedFieldId<lang::Class> myClassField;'
        """
        if self.type.known_to_jnipp:
            return f"impl::{self.static_capitalized}FieldId<{self.type.jnipp_return_type}> {self.decorated_name};"
        if self._type_has_wrapper:
            return f"impl::Wrapped{self.static_capitalized}FieldId<{self.type.get_cpp_return_type(context)}> {self.decorated_name};"
        return f"jni::field_t {self.decorated_name};"

    def get_meta_initializer(self):
        """
        Get the member initializer for the C++ Meta constructor.

        >>> Field("myField", "I").get_meta_initializer()
        'myField(classRef(), "myField")'

        >>> Field("myStringField", "Ljava/lang/String;").get_meta_initializer()
        'myStringField(classRef(), "myStringField")'

        >>> Field("myObjectField", "Ljava/lang/ClassLoader;").get_meta_initializer()
        'myObjectField(classRef().getField("myObjectField", "Ljava/lang/ClassLoader;"))'
        """
        if self.converted:
            return f'{self.decorated_name}(classRef(), "{self.name}")'
        return f'{self.decorated_name}(classRef().get{self.static_capitalized}Field("{self.name}", "{self.signature}"))'

    def has_nested_class(self):
        """
        Check if this field's type references a nested class name.

        Right now we don't handle nested classes, so this is
        transitive-"skip me".
        """
        return self.type.has_nested_class()

    @property
    def getter_name(self):
        """Compute the getter method's name."""
        if self.name.upper() == self.name:
            # This is probably the same as .is_static
            assert(self.is_static)
            return self.name
        assert(not self.is_static)
        return 'get' + self.name[0].upper() + self.name[1:]

    @property
    def _type_has_wrapper(self):
        return (hasattr(self.type, 'has_wrapper') and self.type.has_wrapper)

    @property
    def converted(self):
        """Get whether we converted this from a generic field ID to a typeful one."""
        return self.type.known_to_jnipp or self._type_has_wrapper

    def get_wrapper_decl(self, context=None):
        """
        Get the wrapped "getter" method prototype for the C++ wrapper object.
        """
        decl = []
        if self.is_static:
            decl.append('static')
        decl.append(self.type.get_cpp_return_type(context))
        decl.append(self.getter_name + '()')
        if not self.is_static:
            decl.append('const')

        return self.make_wrapper_decl(
            decl=' '.join(decl)
        )

    def get_wrapper_defn(self, cpp_classname, context=None, meta_instance='Meta::data()', **kwargs):
        """
        Get the wrapped "getter" method implementation for the C++ wrapper object.

        This all lives "inline" in the "impl" header file to reduce call overhead.
        """
        decl = ['inline']
        decl.append(self.type.get_cpp_return_type(context))
        decl.append(f'{cpp_classname}::{self.getter_name}()')
        if not self.is_static:
            decl.append('const')

        if self.converted:
            # The type is encoded in the Meta member type
            return_expression = f'get({meta_instance}.{self.decorated_name}, {self.get_invocation_target(meta_instance)})'
        else:
            return_expression = f'{self.get_invocation_target(meta_instance)}.get<{self.type.jnipp_return_type}>({meta_instance}.{self.decorated_name})'

        return self.make_wrapper_impl(
            decl=' '.join(decl),
            return_expression=return_expression,
            **kwargs
        )


def construct_member(name, signature, java_prototype=None, is_static=False):
    """Construct a member object given its name, signature, and static-ness."""
    if name == Constructor.MEMBER_NAME:
        member = Constructor(signature, java_prototype)
    elif signature[0] == '(':
        member = Method(name, signature, java_prototype, is_static)
    else:
        member = Field(name, signature, java_prototype, is_static)
    return member


if __name__ == "__main__":
    import doctest
    doctest.testmod()
