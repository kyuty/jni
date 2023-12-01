// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include <string>

namespace wrap {
namespace android::database {
inline int32_t Cursor::getCount() {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().getCount);
}

inline bool Cursor::moveToFirst() {
    assert(!isNull());
    return object().call<bool>(Meta::data().moveToFirst);
}

inline bool Cursor::moveToNext() {
    assert(!isNull());
    return object().call<bool>(Meta::data().moveToNext);
}

inline int32_t Cursor::getColumnIndex(std::string &stringParam) {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().getColumnIndex, stringParam);
}

inline std::string Cursor::getString(int32_t intParam) {
    assert(!isNull());
    return object().call<std::string>(Meta::data().getString, intParam);
}

inline int32_t Cursor::getInt(int32_t intParam) {
    assert(!isNull());
    return object().call<int32_t>(Meta::data().getInt, intParam);
}

inline void Cursor::close() {
    assert(!isNull());
    return object().call<void>(Meta::data().close);
}
} // namespace android::database
} // namespace wrap
