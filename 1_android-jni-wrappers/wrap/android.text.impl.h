// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

namespace wrap {
namespace android::text {
inline jni::Object TextUtils::ellipsize(jni::Object &charSequence,
                                        jni::Object &textPaint,
                                        float floatParam,
                                        jni::Object &textUtils_TruncateAt) {
    return Meta::data().clazz().call<jni::Object>(
        Meta::data().ellipsize, charSequence, textPaint, floatParam,
        textUtils_TruncateAt);
}

inline jni::Object
TextUtils::ellipsize(jni::Object &charSequence, jni::Object &textPaint,
                     float floatParam, jni::Object &textUtils_TruncateAt,
                     bool booleanParam,
                     jni::Object &textUtils_EllipsizeCallback) {
    return Meta::data().clazz().call<jni::Object>(
        Meta::data().ellipsize1, charSequence, textPaint, floatParam,
        textUtils_TruncateAt, booleanParam, textUtils_EllipsizeCallback);
}
} // namespace android::text
} // namespace wrap
