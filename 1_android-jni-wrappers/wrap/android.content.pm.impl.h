// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.content.h"
#include "java.util.h"
#include <string>

namespace wrap {
namespace android::content::pm {
inline os::Bundle PackageItemInfo::getMetaData() const {
    assert(!isNull());
    return get(Meta::data().metaData, object());
}

inline std::string PackageItemInfo::getName() const {
    assert(!isNull());
    return get(Meta::data().name, object());
}

inline std::string PackageItemInfo::getPackageName() const {
    assert(!isNull());
    return get(Meta::data().packageName, object());
}

inline std::string ApplicationInfo::getNativeLibraryDir() const {
    assert(!isNull());
    return get(Meta::data().nativeLibraryDir, object());
}

inline std::string ApplicationInfo::getPublicSourceDir() const {
    assert(!isNull());
    return get(Meta::data().publicSourceDir, object());
}
inline ApplicationInfo PackageInfo::getApplicationInfo() const {
    assert(!isNull());
    return get(Meta::data().applicationInfo, object());
}

inline std::string PackageInfo::getPackageName() const {
    assert(!isNull());
    return get(Meta::data().packageName, object());
}
inline ServiceInfo ResolveInfo::getServiceInfo() const {
    assert(!isNull());
    return get(Meta::data().serviceInfo, object());
}
inline PackageInfo PackageManager::getPackageInfo(std::string &stringParam,
                                                  int32_t intParam) {
    assert(!isNull());
    return PackageInfo(object().call<jni::Object>(Meta::data().getPackageInfo,
                                                  stringParam, intParam));
}

inline PackageInfo
PackageManager::getPackageInfo(std::string &stringParam,
                               jni::Object &packageManager_PackageInfoFlags) {
    assert(!isNull());
    return PackageInfo(
        object().call<jni::Object>(Meta::data().getPackageInfo1, stringParam,
                                   packageManager_PackageInfoFlags));
}

inline PackageInfo PackageManager::getPackageInfo(jni::Object &versionedPackage,
                                                  int32_t intParam) {
    assert(!isNull());
    return PackageInfo(object().call<jni::Object>(Meta::data().getPackageInfo2,
                                                  versionedPackage, intParam));
}

inline PackageInfo
PackageManager::getPackageInfo(jni::Object &versionedPackage,
                               jni::Object &packageManager_PackageInfoFlags) {
    assert(!isNull());
    return PackageInfo(object().call<jni::Object>(
        Meta::data().getPackageInfo3, versionedPackage,
        packageManager_PackageInfoFlags));
}

inline ApplicationInfo
PackageManager::getApplicationInfo(std::string &stringParam, int32_t intParam) {
    assert(!isNull());
    return ApplicationInfo(object().call<jni::Object>(
        Meta::data().getApplicationInfo, stringParam, intParam));
}

inline ApplicationInfo PackageManager::getApplicationInfo(
    std::string &stringParam,
    jni::Object &packageManager_ApplicationInfoFlags) {
    assert(!isNull());
    return ApplicationInfo(object().call<jni::Object>(
        Meta::data().getApplicationInfo1, stringParam,
        packageManager_ApplicationInfoFlags));
}

inline java::util::List PackageManager::queryIntentServices(Intent &intent,
                                                            int32_t intParam) {
    assert(!isNull());
    return java::util::List(object().call<jni::Object>(
        Meta::data().queryIntentServices, intent.object(), intParam));
}

inline java::util::List PackageManager::queryIntentServices(
    Intent &intent, jni::Object &packageManager_ResolveInfoFlags) {
    assert(!isNull());
    return java::util::List(object().call<jni::Object>(
        Meta::data().queryIntentServices1, intent.object(),
        packageManager_ResolveInfoFlags));
}
} // namespace android::content::pm
} // namespace wrap
