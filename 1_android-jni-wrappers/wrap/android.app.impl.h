// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.content.h"
#include <string>

namespace wrap {
namespace android::app {

inline jni::Object Activity::getSystemService(std::string &stringParam) {
    assert(!isNull());
    return object().call<jni::Object>(Meta::data().getSystemService,
                                      stringParam);
}

inline void Activity::setVrModeEnabled(bool booleanParam,
                                       content::ComponentName &componentName) {
    assert(!isNull());
    return object().call<void>(Meta::data().setVrModeEnabled, booleanParam,
                               componentName.object());
}
} // namespace android::app
} // namespace wrap
