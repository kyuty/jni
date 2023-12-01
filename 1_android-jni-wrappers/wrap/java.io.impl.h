// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include <string>

namespace wrap {
namespace java::io {
inline File File::construct(std::string &stringParam) {
    return File(
        Meta::data().clazz().newInstance(Meta::data().init, stringParam));
}

inline File File::construct(std::string &stringParam,
                            std::string &stringParam1) {
    return File(Meta::data().clazz().newInstance(Meta::data().init1,
                                                 stringParam, stringParam1));
}

inline File File::construct(File &file, std::string &stringParam) {
    return File(Meta::data().clazz().newInstance(Meta::data().init2,
                                                 file.object(), stringParam));
}

inline File File::construct(jni::Object &uRI) {
    return File(Meta::data().clazz().newInstance(Meta::data().init3, uRI));
}

inline bool File::exists() {
    assert(!isNull());
    return object().call<bool>(Meta::data().exists);
}

inline bool File::mkdirs() {
    assert(!isNull());
    return object().call<bool>(Meta::data().mkdirs);
}
inline FileOutputStream FileOutputStream::construct(std::string &stringParam) {
    return FileOutputStream(
        Meta::data().clazz().newInstance(Meta::data().init, stringParam));
}

inline FileOutputStream FileOutputStream::construct(std::string &stringParam,
                                                    bool booleanParam) {
    return FileOutputStream(Meta::data().clazz().newInstance(
        Meta::data().init1, stringParam, booleanParam));
}

inline FileOutputStream FileOutputStream::construct(File &file) {
    return FileOutputStream(
        Meta::data().clazz().newInstance(Meta::data().init2, file.object()));
}

inline FileOutputStream FileOutputStream::construct(File &file,
                                                    bool booleanParam) {
    return FileOutputStream(Meta::data().clazz().newInstance(
        Meta::data().init3, file.object(), booleanParam));
}

inline FileOutputStream
FileOutputStream::construct(jni::Object &fileDescriptor) {
    return FileOutputStream(
        Meta::data().clazz().newInstance(Meta::data().init4, fileDescriptor));
}

inline void FileOutputStream::close() {
    assert(!isNull());
    return object().call<void>(Meta::data().close);
}
} // namespace java::io
} // namespace wrap
