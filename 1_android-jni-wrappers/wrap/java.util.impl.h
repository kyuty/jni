// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

namespace wrap {
namespace java::util {
inline int32_t List::size() {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().size);
}

inline jni::Object List::get(int32_t intParam) {
    assert(!isNull());
    return object().call<jni::Object>(Meta::data().get, intParam);
}
} // namespace java::util
} // namespace wrap
