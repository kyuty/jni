// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include <string>

namespace wrap {
namespace java::lang {
inline Class Class::forName(std::string &stringParam) {
    return Class(Meta::data().clazz().call<jni::Object>(Meta::data().forName,
                                                        stringParam));
}

inline Class Class::forName(std::string &stringParam, bool booleanParam,
                            ClassLoader &classLoader) {
    return Class(Meta::data().clazz().call<jni::Object>(
        Meta::data().forName1, stringParam, booleanParam,
        classLoader.object()));
}

inline Class Class::forName(jni::Object &module, std::string &stringParam) {
    return Class(Meta::data().clazz().call<jni::Object>(Meta::data().forName2,
                                                        module, stringParam));
}

inline std::string Class::getCanonicalName() {
    assert(!isNull());
    return object().call<std::string>(Meta::data().getCanonicalName);
}
inline Class ClassLoader::loadClass(std::string &stringParam) {
    assert(!isNull());
    return Class(
        object().call<jni::Object>(Meta::data().loadClass, stringParam));
}

inline std::string ClassLoader::findLibrary(std::string &stringParam) {
    assert(!isNull());
    return object().call<std::string>(Meta::data().findLibrary, stringParam);
}
inline std::string System::mapLibraryName(std::string &stringParam) {
    return Meta::data().clazz().call<std::string>(Meta::data().mapLibraryName,
                                                  stringParam);
}
inline double Math::ceil(double doubleParam) {
    return Meta::data().clazz().call<double>(Meta::data().ceil, doubleParam);
}
} // namespace java::lang
} // namespace wrap
