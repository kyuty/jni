// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.graphics.h"
#include "android.util.h"

namespace wrap {
namespace android::view {
inline void Display::getRealSize(graphics::Point &point) {
    assert(!isNull());
    return object().call<void>(Meta::data().getRealSize, point.object());
}

inline void Display::getRealMetrics(util::DisplayMetrics &displayMetrics) {
    assert(!isNull());
    return object().call<void>(Meta::data().getRealMetrics,
                               displayMetrics.object());
}
inline bool Surface::isValid() {
    assert(!isNull());
    return object().call<bool>(Meta::data().isValid);
}
inline Surface SurfaceHolder::getSurface() {
    assert(!isNull());
    return Surface(object().call<jni::Object>(Meta::data().getSurface));
}
} // namespace android::view
} // namespace wrap
