// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "java.lang.h"
#include <string>

namespace wrap {
namespace dalvik::system {
inline DexClassLoader
DexClassLoader::construct(std::string &stringParam, std::string &stringParam1,
                          std::string &stringParam2,
                          java::lang::ClassLoader &classLoader) {
    return DexClassLoader(Meta::data().clazz().newInstance(
        Meta::data().init, stringParam, stringParam1, stringParam2,
        classLoader.object()));
}
} // namespace dalvik::system
} // namespace wrap
