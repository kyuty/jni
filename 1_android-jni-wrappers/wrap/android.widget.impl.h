// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.content.h"

namespace wrap {
namespace android::widget {
inline int32_t Toast::LENGTH_LONG() {
    return get(Meta::data().LENGTH_LONG, Meta::data().clazz());
}

inline int32_t Toast::LENGTH_SHORT() {
    return get(Meta::data().LENGTH_SHORT, Meta::data().clazz());
}

inline void Toast::show() {
    assert(!isNull());
    return object().call<void>(Meta::data().show);
}

inline Toast Toast::makeText(content::Context &context,
                             jni::Object &charSequence, int32_t intParam) {
    return Toast(Meta::data().clazz().call<jni::Object>(
        Meta::data().makeText, context.object(), charSequence, intParam));
}

inline Toast Toast::makeText(content::Context &context, int32_t intParam,
                             int32_t intParam2) {
    return Toast(Meta::data().clazz().call<jni::Object>(
        Meta::data().makeText1, context.object(), intParam, intParam2));
}
} // namespace android::widget
} // namespace wrap
