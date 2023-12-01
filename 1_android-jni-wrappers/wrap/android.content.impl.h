// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.content.pm.h"
#include "android.database.h"
#include "android.net.h"
#include "android.os.h"
#include "java.lang.h"
#include <string>

namespace wrap {
namespace android::content {
inline std::string Context::DISPLAY_SERVICE() {
    auto &data = Meta::data(true);
    auto ret = get(data.DISPLAY_SERVICE, data.clazz());
    data.dropClassRef();
    return ret;
}

inline std::string Context::WINDOW_SERVICE() {
    auto &data = Meta::data(true);
    auto ret = get(data.WINDOW_SERVICE, data.clazz());
    data.dropClassRef();
    return ret;
}

inline pm::PackageManager Context::getPackageManager() {
    assert(!isNull());
    return pm::PackageManager(
        object().call<jni::Object>(Meta::data().getPackageManager));
}

inline ContentResolver Context::getContentResolver() {
    assert(!isNull());
    return ContentResolver(
        object().call<jni::Object>(Meta::data().getContentResolver));
}

inline Context Context::getApplicationContext() {
    assert(!isNull());
    return Context(
        object().call<jni::Object>(Meta::data().getApplicationContext));
}

inline java::lang::ClassLoader Context::getClassLoader() {
    assert(!isNull());
    return java::lang::ClassLoader(
        object().call<jni::Object>(Meta::data().getClassLoader));
}

inline void Context::startActivity(Intent &intent) {
    assert(!isNull());
    return object().call<void>(Meta::data().startActivity, intent.object());
}

inline void Context::startActivity(Intent &intent, os::Bundle &bundle) {
    assert(!isNull());
    return object().call<void>(Meta::data().startActivity1, intent.object(),
                               bundle.object());
}

inline Context Context::createPackageContext(std::string &stringParam,
                                             int32_t intParam) {
    assert(!isNull());
    return Context(object().call<jni::Object>(Meta::data().createPackageContext,
                                              stringParam, intParam));
}
inline net::Uri_Builder ContentUris::appendId(net::Uri_Builder &uri_Builder,
                                              int64_t longParam) {
    auto &data = Meta::data(true);
    auto ret = net::Uri_Builder(data.clazz().call<jni::Object>(
        data.appendId, uri_Builder.object(), longParam));
    data.dropClassRef();
    return ret;
}
inline ComponentName ComponentName::construct(std::string &stringParam,
                                              std::string &stringParam1) {
    return ComponentName(Meta::data().clazz().newInstance(
        Meta::data().init, stringParam, stringParam1));
}

inline ComponentName ComponentName::construct(Context &context,
                                              std::string &stringParam) {
    return ComponentName(Meta::data().clazz().newInstance(
        Meta::data().init1, context.object(), stringParam));
}

inline ComponentName ComponentName::construct(Context &context,
                                              java::lang::Class &classParam) {
    return ComponentName(Meta::data().clazz().newInstance(
        Meta::data().init2, context.object(), classParam.object()));
}

inline ComponentName ComponentName::construct(jni::Object &parcel) {
    return ComponentName(
        Meta::data().clazz().newInstance(Meta::data().init3, parcel));
}
inline int32_t Intent::FLAG_ACTIVITY_NEW_TASK() {
    return get(Meta::data().FLAG_ACTIVITY_NEW_TASK, Meta::data().clazz());
}

inline Intent Intent::construct() {
    return Intent(Meta::data().clazz().newInstance(Meta::data().init));
}

inline Intent Intent::construct(Intent &intent) {
    return Intent(
        Meta::data().clazz().newInstance(Meta::data().init1, intent.object()));
}

inline Intent Intent::construct(std::string &stringParam) {
    return Intent(
        Meta::data().clazz().newInstance(Meta::data().init2, stringParam));
}

inline Intent Intent::construct(std::string &stringParam, net::Uri &uri) {
    return Intent(Meta::data().clazz().newInstance(Meta::data().init3,
                                                   stringParam, uri.object()));
}

inline Intent Intent::construct(Context &context,
                                java::lang::Class &classParam) {
    return Intent(Meta::data().clazz().newInstance(
        Meta::data().init4, context.object(), classParam.object()));
}

inline Intent Intent::construct(std::string &stringParam, net::Uri &uri,
                                Context &context,
                                java::lang::Class &classParam) {
    return Intent(Meta::data().clazz().newInstance(
        Meta::data().init5, stringParam, uri.object(), context.object(),
        classParam.object()));
}

inline Intent Intent::setFlags(int32_t intParam) {
    assert(!isNull());
    return Intent(object().call<jni::Object>(Meta::data().setFlags, intParam));
}
inline database::Cursor
ContentResolver::query(net::Uri &uri, jni::Array<std::string> &stringArray,
                       std::string &stringParam,
                       jni::Array<std::string> &stringArray3,
                       std::string &stringParam4) {
    assert(!isNull());
    return database::Cursor(object().call<jni::Object>(
        Meta::data().query, uri.object(), stringArray, stringParam,
        stringArray3, stringParam4));
}

inline database::Cursor ContentResolver::query(
    net::Uri &uri, jni::Array<std::string> &stringArray,
    std::string &stringParam, jni::Array<std::string> &stringArray3,
    std::string &stringParam4, jni::Object &cancellationSignal) {
    assert(!isNull());
    return database::Cursor(object().call<jni::Object>(
        Meta::data().query1, uri.object(), stringArray, stringParam,
        stringArray3, stringParam4, cancellationSignal));
}

inline database::Cursor
ContentResolver::query(net::Uri &uri, jni::Array<std::string> &stringArray,
                       os::Bundle &bundle, jni::Object &cancellationSignal) {
    assert(!isNull());
    return database::Cursor(object().call<jni::Object>(
        Meta::data().query2, uri.object(), stringArray, bundle.object(),
        cancellationSignal));
}
} // namespace android::content
} // namespace wrap
