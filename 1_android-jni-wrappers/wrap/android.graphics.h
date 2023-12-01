// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "ObjectWrapperBase.h"

namespace wrap {
namespace android::graphics {
class Bitmap;
class Canvas;
class Paint;
} // namespace android::graphics

namespace android::util {
class DisplayMetrics;
} // namespace android::util

} // namespace wrap

namespace wrap {
namespace android::graphics {
/*!
 * Wrapper for android.graphics.Point objects.
 */
class Point : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "android/graphics/Point";
    }

    /*!
     * Getter for the x field value
     *
     * Java prototype:
     * `public int x;`
     *
     * JNI signature: I
     *
     */
    int32_t getX() const;

    /*!
     * Getter for the y field value
     *
     * Java prototype:
     * `public int y;`
     *
     * JNI signature: I
     *
     */
    int32_t getY() const;

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        impl::FieldId<int32_t> x;
        impl::FieldId<int32_t> y;

        /*!
         * Singleton accessor
         */
        static Meta &data() {
            static Meta instance{};
            return instance;
        }

      private:
        Meta();
    };
};
/*!
 * Wrapper for android.graphics.Bitmap objects.
 */
class Bitmap : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "android/graphics/Bitmap";
    }

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.graphics.Bitmap);`
     *
     * JNI signature: (Landroid/graphics/Bitmap;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(Bitmap &bitmap);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.graphics.Bitmap, int, int, int, int);`
     *
     * JNI signature: (Landroid/graphics/Bitmap;IIII)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(Bitmap &bitmap, int32_t intParam,
                               int32_t intParam2, int32_t intParam3,
                               int32_t intParam4);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.graphics.Bitmap, int, int, int, int,
     * android.graphics.Matrix, boolean);`
     *
     * JNI signature:
     * (Landroid/graphics/Bitmap;IIIILandroid/graphics/Matrix;Z)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(Bitmap &bitmap, int32_t intParam,
                               int32_t intParam2, int32_t intParam3,
                               int32_t intParam4, jni::Object &matrix,
                               bool booleanParam);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap createBitmap(int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * (IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(int32_t intParam, int32_t intParam1,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.util.DisplayMetrics, int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * (Landroid/util/DisplayMetrics;IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(util::DisplayMetrics &displayMetrics,
                               int32_t intParam, int32_t intParam2,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap createBitmap(int, int,
     * android.graphics.Bitmap$Config, boolean);`
     *
     * JNI signature:
     * (IILandroid/graphics/Bitmap$Config;Z)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(int32_t intParam, int32_t intParam1,
                               jni::Object &bitmap_Config, bool booleanParam);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap createBitmap(int, int,
     * android.graphics.Bitmap$Config, boolean, android.graphics.ColorSpace);`
     *
     * JNI signature:
     * (IILandroid/graphics/Bitmap$Config;ZLandroid/graphics/ColorSpace;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(int32_t intParam, int32_t intParam1,
                               jni::Object &bitmap_Config, bool booleanParam,
                               jni::Object &colorSpace);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.util.DisplayMetrics, int, int,
     * android.graphics.Bitmap$Config, boolean);`
     *
     * JNI signature:
     * (Landroid/util/DisplayMetrics;IILandroid/graphics/Bitmap$Config;Z)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(util::DisplayMetrics &displayMetrics,
                               int32_t intParam, int32_t intParam2,
                               jni::Object &bitmap_Config, bool booleanParam);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.util.DisplayMetrics, int, int,
     * android.graphics.Bitmap$Config, boolean, android.graphics.ColorSpace);`
     *
     * JNI signature:
     * (Landroid/util/DisplayMetrics;IILandroid/graphics/Bitmap$Config;ZLandroid/graphics/ColorSpace;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(util::DisplayMetrics &displayMetrics,
                               int32_t intParam, int32_t intParam2,
                               jni::Object &bitmap_Config, bool booleanParam,
                               jni::Object &colorSpace);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap createBitmap(int[], int, int, int,
     * int, android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * ([IIIIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(jni::Array<int32_t> &intParamArray,
                               int32_t intParam, int32_t intParam2,
                               int32_t intParam3, int32_t intParam4,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.util.DisplayMetrics, int[], int, int, int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * (Landroid/util/DisplayMetrics;[IIIIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(util::DisplayMetrics &displayMetrics,
                               jni::Array<int32_t> &intParamArray,
                               int32_t intParam, int32_t intParam3,
                               int32_t intParam4, int32_t intParam5,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap createBitmap(int[], int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * ([IIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(jni::Array<int32_t> &intParamArray,
                               int32_t intParam, int32_t intParam2,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.util.DisplayMetrics, int[], int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * (Landroid/util/DisplayMetrics;[IIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(util::DisplayMetrics &displayMetrics,
                               jni::Array<int32_t> &intParamArray,
                               int32_t intParam, int32_t intParam3,
                               jni::Object &bitmap_Config);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.graphics.Picture);`
     *
     * JNI signature: (Landroid/graphics/Picture;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(jni::Object &picture);

    /*!
     * Wrapper for the createBitmap static method
     *
     * Java prototype:
     * `public static android.graphics.Bitmap
     * createBitmap(android.graphics.Picture, int, int,
     * android.graphics.Bitmap$Config);`
     *
     * JNI signature:
     * (Landroid/graphics/Picture;IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;
     *
     */
    static Bitmap createBitmap(jni::Object &picture, int32_t intParam,
                               int32_t intParam2, jni::Object &bitmap_Config);

    /*!
     * Wrapper for the compress method
     *
     * Java prototype:
     * `public boolean compress(android.graphics.Bitmap$CompressFormat, int,
     * java.io.OutputStream);`
     *
     * JNI signature:
     * (Landroid/graphics/Bitmap$CompressFormat;ILjava/io/OutputStream;)Z
     *
     */
    bool compress(jni::Object &bitmap_CompressFormat, int32_t intParam,
                  jni::Object &outputStream);

    /*!
     * Wrapper for the eraseColor method
     *
     * Java prototype:
     * `public void eraseColor(int);`
     *
     * JNI signature: (I)V
     *
     */
    void eraseColor(int32_t intParam);

    /*!
     * Wrapper for the eraseColor method
     *
     * Java prototype:
     * `public void eraseColor(long);`
     *
     * JNI signature: (J)V
     *
     */
    void eraseColor(int64_t longParam);

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        jni::method_t createBitmap;
        jni::method_t createBitmap1;
        jni::method_t createBitmap2;
        jni::method_t createBitmap3;
        jni::method_t createBitmap4;
        jni::method_t createBitmap5;
        jni::method_t createBitmap6;
        jni::method_t createBitmap7;
        jni::method_t createBitmap8;
        jni::method_t createBitmap9;
        jni::method_t createBitmap10;
        jni::method_t createBitmap11;
        jni::method_t createBitmap12;
        jni::method_t createBitmap13;
        jni::method_t createBitmap14;
        jni::method_t compress;
        jni::method_t eraseColor;
        jni::method_t eraseColor1;

        /*!
         * Singleton accessor
         */
        static Meta &data() {
            static Meta instance{};
            return instance;
        }

      private:
        Meta();
    };
};
/*!
 * Wrapper for android.graphics.Paint objects.
 */
class Paint : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "android/graphics/Paint";
    }

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public android.graphics.Paint();`
     *
     * JNI signature: ()V
     *
     */
    static Paint construct();

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public android.graphics.Paint(int);`
     *
     * JNI signature: (I)V
     *
     */
    static Paint construct(int32_t intParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public android.graphics.Paint(android.graphics.Paint);`
     *
     * JNI signature: (Landroid/graphics/Paint;)V
     *
     */
    static Paint construct(Paint &paint);

    /*!
     * Wrapper for the setAntiAlias method
     *
     * Java prototype:
     * `public void setAntiAlias(boolean);`
     *
     * JNI signature: (Z)V
     *
     */
    void setAntiAlias(bool booleanParam);

    /*!
     * Wrapper for the setFilterBitmap method
     *
     * Java prototype:
     * `public void setFilterBitmap(boolean);`
     *
     * JNI signature: (Z)V
     *
     */
    void setFilterBitmap(bool booleanParam);

    /*!
     * Wrapper for the setColor method
     *
     * Java prototype:
     * `public void setColor(int);`
     *
     * JNI signature: (I)V
     *
     */
    void setColor(int32_t intParam);

    /*!
     * Wrapper for the setColor method
     *
     * Java prototype:
     * `public void setColor(long);`
     *
     * JNI signature: (J)V
     *
     */
    void setColor(int64_t longParam);

    /*!
     * Wrapper for the getTextSize method
     *
     * Java prototype:
     * `public float getTextSize();`
     *
     * JNI signature: ()F
     *
     */
    float getTextSize();

    /*!
     * Wrapper for the setTextSize method
     *
     * Java prototype:
     * `public void setTextSize(float);`
     *
     * JNI signature: (F)V
     *
     */
    void setTextSize(float floatParam);

    /*!
     * Wrapper for the ascent method
     *
     * Java prototype:
     * `public float ascent();`
     *
     * JNI signature: ()F
     *
     */
    float ascent();

    /*!
     * Wrapper for the descent method
     *
     * Java prototype:
     * `public float descent();`
     *
     * JNI signature: ()F
     *
     */
    float descent();

    /*!
     * Wrapper for the measureText method
     *
     * Java prototype:
     * `public float measureText(char[], int, int);`
     *
     * JNI signature: ([CII)F
     *
     */
    float measureText(jni::Array<uint16_t> &charParamArray, int32_t intParam,
                      int32_t intParam2);

    /*!
     * Wrapper for the measureText method
     *
     * Java prototype:
     * `public float measureText(java.lang.String, int, int);`
     *
     * JNI signature: (Ljava/lang/String;II)F
     *
     */
    float measureText(std::string &stringParam, int32_t intParam,
                      int32_t intParam2);

    /*!
     * Wrapper for the measureText method
     *
     * Java prototype:
     * `public float measureText(java.lang.String);`
     *
     * JNI signature: (Ljava/lang/String;)F
     *
     */
    float measureText(std::string &stringParam);

    /*!
     * Wrapper for the measureText method
     *
     * Java prototype:
     * `public float measureText(java.lang.CharSequence, int, int);`
     *
     * JNI signature: (Ljava/lang/CharSequence;II)F
     *
     */
    float measureText(jni::Object &charSequence, int32_t intParam,
                      int32_t intParam2);

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        jni::method_t init;
        jni::method_t init1;
        jni::method_t init2;
        jni::method_t setAntiAlias;
        jni::method_t setFilterBitmap;
        jni::method_t setColor;
        jni::method_t setColor1;
        jni::method_t getTextSize;
        jni::method_t setTextSize;
        jni::method_t ascent;
        jni::method_t descent;
        jni::method_t measureText;
        jni::method_t measureText1;
        jni::method_t measureText2;
        jni::method_t measureText3;

        /*!
         * Singleton accessor
         */
        static Meta &data() {
            static Meta instance{};
            return instance;
        }

      private:
        Meta();
    };
};
/*!
 * Wrapper for android.graphics.Canvas objects.
 */
class Canvas : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "android/graphics/Canvas";
    }

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public android.graphics.Canvas();`
     *
     * JNI signature: ()V
     *
     */
    static Canvas construct();

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public android.graphics.Canvas(android.graphics.Bitmap);`
     *
     * JNI signature: (Landroid/graphics/Bitmap;)V
     *
     */
    static Canvas construct(Bitmap &bitmap);

    /*!
     * Wrapper for the drawText method
     *
     * Java prototype:
     * `public void drawText(char[], int, int, float, float,
     * android.graphics.Paint);`
     *
     * JNI signature: ([CIIFFLandroid/graphics/Paint;)V
     *
     */
    void drawText(jni::Array<uint16_t> &charParamArray, int32_t intParam,
                  int32_t intParam2, float floatParam, float floatParam4,
                  Paint &paint);

    /*!
     * Wrapper for the drawText method
     *
     * Java prototype:
     * `public void drawText(java.lang.String, float, float,
     * android.graphics.Paint);`
     *
     * JNI signature: (Ljava/lang/String;FFLandroid/graphics/Paint;)V
     *
     */
    void drawText(std::string &stringParam, float floatParam, float floatParam2,
                  Paint &paint);

    /*!
     * Wrapper for the drawText method
     *
     * Java prototype:
     * `public void drawText(java.lang.String, int, int, float, float,
     * android.graphics.Paint);`
     *
     * JNI signature: (Ljava/lang/String;IIFFLandroid/graphics/Paint;)V
     *
     */
    void drawText(std::string &stringParam, int32_t intParam, int32_t intParam2,
                  float floatParam, float floatParam4, Paint &paint);

    /*!
     * Wrapper for the drawText method
     *
     * Java prototype:
     * `public void drawText(java.lang.CharSequence, int, int, float, float,
     * android.graphics.Paint);`
     *
     * JNI signature: (Ljava/lang/CharSequence;IIFFLandroid/graphics/Paint;)V
     *
     */
    void drawText(jni::Object &charSequence, int32_t intParam,
                  int32_t intParam2, float floatParam, float floatParam4,
                  Paint &paint);

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        jni::method_t init;
        jni::method_t init1;
        jni::method_t drawText;
        jni::method_t drawText1;
        jni::method_t drawText2;
        jni::method_t drawText3;

        /*!
         * Singleton accessor
         */
        static Meta &data() {
            static Meta instance{};
            return instance;
        }

      private:
        Meta();
    };
};
/*!
 * Wrapper for android.graphics.Color objects.
 */
class Color : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "android/graphics/Color";
    }

    /*!
     * Getter for the BLACK static field value
     *
     * Java prototype:
     * `public static final int BLACK;`
     *
     * JNI signature: I
     *
     */
    static int32_t BLACK();

    /*!
     * Getter for the YELLOW static field value
     *
     * Java prototype:
     * `public static final int YELLOW;`
     *
     * JNI signature: I
     *
     */
    static int32_t YELLOW();

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        impl::StaticFieldId<int32_t> BLACK;
        impl::StaticFieldId<int32_t> YELLOW;

        /*!
         * Singleton accessor
         */
        static Meta &data() {
            static Meta instance{};
            return instance;
        }

      private:
        Meta();
    };
};
} // namespace android::graphics
} // namespace wrap
#include "android.graphics.impl.h"
