// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "android.util.h"
#include <string>

namespace wrap {
namespace android::graphics {
inline int32_t Point::getX() const {
    assert(!isNull());
    return get(Meta::data().x, object());
}

inline int32_t Point::getY() const {
    assert(!isNull());
    return get(Meta::data().y, object());
}
inline Bitmap Bitmap::createBitmap(Bitmap &bitmap) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap, bitmap.object()));
}

inline Bitmap Bitmap::createBitmap(Bitmap &bitmap, int32_t intParam,
                                   int32_t intParam2, int32_t intParam3,
                                   int32_t intParam4) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap1, bitmap.object(), intParam, intParam2,
        intParam3, intParam4));
}

inline Bitmap Bitmap::createBitmap(Bitmap &bitmap, int32_t intParam,
                                   int32_t intParam2, int32_t intParam3,
                                   int32_t intParam4, jni::Object &matrix,
                                   bool booleanParam) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap2, bitmap.object(), intParam, intParam2,
        intParam3, intParam4, matrix, booleanParam));
}

inline Bitmap Bitmap::createBitmap(int32_t intParam, int32_t intParam1,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap3, intParam, intParam1, bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(util::DisplayMetrics &displayMetrics,
                                   int32_t intParam, int32_t intParam2,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap4, displayMetrics.object(), intParam,
        intParam2, bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(int32_t intParam, int32_t intParam1,
                                   jni::Object &bitmap_Config,
                                   bool booleanParam) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap5, intParam, intParam1, bitmap_Config,
        booleanParam));
}

inline Bitmap Bitmap::createBitmap(int32_t intParam, int32_t intParam1,
                                   jni::Object &bitmap_Config,
                                   bool booleanParam, jni::Object &colorSpace) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap6, intParam, intParam1, bitmap_Config,
        booleanParam, colorSpace));
}

inline Bitmap Bitmap::createBitmap(util::DisplayMetrics &displayMetrics,
                                   int32_t intParam, int32_t intParam2,
                                   jni::Object &bitmap_Config,
                                   bool booleanParam) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap7, displayMetrics.object(), intParam,
        intParam2, bitmap_Config, booleanParam));
}

inline Bitmap Bitmap::createBitmap(util::DisplayMetrics &displayMetrics,
                                   int32_t intParam, int32_t intParam2,
                                   jni::Object &bitmap_Config,
                                   bool booleanParam, jni::Object &colorSpace) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap8, displayMetrics.object(), intParam,
        intParam2, bitmap_Config, booleanParam, colorSpace));
}

inline Bitmap Bitmap::createBitmap(jni::Array<int32_t> &intParamArray,
                                   int32_t intParam, int32_t intParam2,
                                   int32_t intParam3, int32_t intParam4,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap9, intParamArray, intParam, intParam2,
        intParam3, intParam4, bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(util::DisplayMetrics &displayMetrics,
                                   jni::Array<int32_t> &intParamArray,
                                   int32_t intParam, int32_t intParam3,
                                   int32_t intParam4, int32_t intParam5,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap10, displayMetrics.object(), intParamArray,
        intParam, intParam3, intParam4, intParam5, bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(jni::Array<int32_t> &intParamArray,
                                   int32_t intParam, int32_t intParam2,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap11, intParamArray, intParam, intParam2,
        bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(util::DisplayMetrics &displayMetrics,
                                   jni::Array<int32_t> &intParamArray,
                                   int32_t intParam, int32_t intParam3,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap12, displayMetrics.object(), intParamArray,
        intParam, intParam3, bitmap_Config));
}

inline Bitmap Bitmap::createBitmap(jni::Object &picture) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap13, picture));
}

inline Bitmap Bitmap::createBitmap(jni::Object &picture, int32_t intParam,
                                   int32_t intParam2,
                                   jni::Object &bitmap_Config) {
    return Bitmap(Meta::data().clazz().call<jni::Object>(
        Meta::data().createBitmap14, picture, intParam, intParam2,
        bitmap_Config));
}

inline bool Bitmap::compress(jni::Object &bitmap_CompressFormat,
                             int32_t intParam, jni::Object &outputStream) {
    assert(!isNull());
    return object().call<bool>(Meta::data().compress, bitmap_CompressFormat,
                               intParam, outputStream);
}

inline void Bitmap::eraseColor(int32_t intParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().eraseColor, intParam);
}

inline void Bitmap::eraseColor(int64_t longParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().eraseColor1, longParam);
}
inline Paint Paint::construct() {
    return Paint(Meta::data().clazz().newInstance(Meta::data().init));
}

inline Paint Paint::construct(int32_t intParam) {
    return Paint(
        Meta::data().clazz().newInstance(Meta::data().init1, intParam));
}

inline Paint Paint::construct(Paint &paint) {
    return Paint(
        Meta::data().clazz().newInstance(Meta::data().init2, paint.object()));
}

inline void Paint::setAntiAlias(bool booleanParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().setAntiAlias, booleanParam);
}

inline void Paint::setFilterBitmap(bool booleanParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().setFilterBitmap, booleanParam);
}

inline void Paint::setColor(int32_t intParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().setColor, intParam);
}

inline void Paint::setColor(int64_t longParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().setColor1, longParam);
}

inline float Paint::getTextSize() {
    assert(!isNull());
    return object().call<float>(Meta::data().getTextSize);
}

inline void Paint::setTextSize(float floatParam) {
    assert(!isNull());
    return object().call<void>(Meta::data().setTextSize, floatParam);
}

inline float Paint::ascent() {
    assert(!isNull());
    return object().call<float>(Meta::data().ascent);
}

inline float Paint::descent() {
    assert(!isNull());
    return object().call<float>(Meta::data().descent);
}

inline float Paint::measureText(jni::Array<uint16_t> &charParamArray,
                                int32_t intParam, int32_t intParam2) {
    assert(!isNull());
    return object().call<float>(Meta::data().measureText, charParamArray,
                                intParam, intParam2);
}

inline float Paint::measureText(std::string &stringParam, int32_t intParam,
                                int32_t intParam2) {
    assert(!isNull());
    return object().call<float>(Meta::data().measureText1, stringParam,
                                intParam, intParam2);
}

inline float Paint::measureText(std::string &stringParam) {
    assert(!isNull());
    return object().call<float>(Meta::data().measureText2, stringParam);
}

inline float Paint::measureText(jni::Object &charSequence, int32_t intParam,
                                int32_t intParam2) {
    assert(!isNull());
    return object().call<float>(Meta::data().measureText3, charSequence,
                                intParam, intParam2);
}
inline Canvas Canvas::construct() {
    return Canvas(Meta::data().clazz().newInstance(Meta::data().init));
}

inline Canvas Canvas::construct(Bitmap &bitmap) {
    return Canvas(
        Meta::data().clazz().newInstance(Meta::data().init1, bitmap.object()));
}

inline void Canvas::drawText(jni::Array<uint16_t> &charParamArray,
                             int32_t intParam, int32_t intParam2,
                             float floatParam, float floatParam4,
                             Paint &paint) {
    assert(!isNull());
    return object().call<void>(Meta::data().drawText, charParamArray, intParam,
                               intParam2, floatParam, floatParam4,
                               paint.object());
}

inline void Canvas::drawText(std::string &stringParam, float floatParam,
                             float floatParam2, Paint &paint) {
    assert(!isNull());
    return object().call<void>(Meta::data().drawText1, stringParam, floatParam,
                               floatParam2, paint.object());
}

inline void Canvas::drawText(std::string &stringParam, int32_t intParam,
                             int32_t intParam2, float floatParam,
                             float floatParam4, Paint &paint) {
    assert(!isNull());
    return object().call<void>(Meta::data().drawText2, stringParam, intParam,
                               intParam2, floatParam, floatParam4,
                               paint.object());
}

inline void Canvas::drawText(jni::Object &charSequence, int32_t intParam,
                             int32_t intParam2, float floatParam,
                             float floatParam4, Paint &paint) {
    assert(!isNull());
    return object().call<void>(Meta::data().drawText3, charSequence, intParam,
                               intParam2, floatParam, floatParam4,
                               paint.object());
}
inline int32_t Color::BLACK() {
    return get(Meta::data().BLACK, Meta::data().clazz());
}

inline int32_t Color::YELLOW() {
    return get(Meta::data().YELLOW, Meta::data().clazz());
}
} // namespace android::graphics
} // namespace wrap
