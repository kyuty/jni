// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include <string>

namespace wrap {
namespace android::os {
inline bool BaseBundle::containsKey(std::string &stringParam) {
    assert(!isNull());
    return object().call<bool>(Meta::data().containsKey, stringParam);
}

inline std::string BaseBundle::getString(std::string &stringParam) {
    assert(!isNull());
    return object().call<std::string>(Meta::data().getString, stringParam);
}

inline std::string BaseBundle::getString(std::string &stringParam,
                                         std::string &stringParam1) {
    assert(!isNull());
    return object().call<std::string>(Meta::data().getString1, stringParam,
                                      stringParam1);
}

inline ParcelFileDescriptor ParcelFileDescriptor::adoptFd(int32_t intParam) {
    return ParcelFileDescriptor(
        Meta::data().clazz().call<jni::Object>(Meta::data().adoptFd, intParam));
}

inline int32_t ParcelFileDescriptor::getFd() {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().getFd);
}

inline int32_t ParcelFileDescriptor::detachFd() {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().detachFd);
}

inline void ParcelFileDescriptor::close() {
    assert(!isNull());
    return object().call<void>(Meta::data().close);
}

inline void ParcelFileDescriptor::checkError() {
    assert(!isNull());
    return object().call<void>(Meta::data().checkError);
}
} // namespace android::os
} // namespace wrap
