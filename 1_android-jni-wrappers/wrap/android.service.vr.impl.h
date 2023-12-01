// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.content.h"

namespace wrap {
namespace android::service::vr {
inline bool VrListenerService::isVrModePackageEnabled(
    content::Context &context, content::ComponentName &componentName) {
    return Meta::data().clazz().call<bool>(Meta::data().isVrModePackageEnabled,
                                           context.object(),
                                           componentName.object());
}
} // namespace android::service::vr
} // namespace wrap
