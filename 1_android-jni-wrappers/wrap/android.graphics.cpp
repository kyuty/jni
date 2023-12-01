// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#include "android.graphics.h"

namespace wrap {
namespace android::graphics {
Point::Meta::Meta()
    : MetaBaseDroppable(Point::getTypeName()), x(classRef(), "x"),
      y(classRef(), "y") {
    MetaBaseDroppable::dropClassRef();
}
Bitmap::Meta::Meta()
    : MetaBaseDroppable(Bitmap::getTypeName()),
      createBitmap(classRef().getStaticMethod(
          "createBitmap",
          "(Landroid/graphics/Bitmap;)Landroid/graphics/Bitmap;")),
      createBitmap1(classRef().getStaticMethod(
          "createBitmap",
          "(Landroid/graphics/Bitmap;IIII)Landroid/graphics/Bitmap;")),
      createBitmap2(classRef().getStaticMethod(
          "createBitmap", "(Landroid/graphics/Bitmap;IIIILandroid/graphics/"
                          "Matrix;Z)Landroid/graphics/Bitmap;")),
      createBitmap3(classRef().getStaticMethod(
          "createBitmap",
          "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap4(classRef().getStaticMethod(
          "createBitmap", "(Landroid/util/DisplayMetrics;IILandroid/graphics/"
                          "Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap5(classRef().getStaticMethod(
          "createBitmap",
          "(IILandroid/graphics/Bitmap$Config;Z)Landroid/graphics/Bitmap;")),
      createBitmap6(classRef().getStaticMethod(
          "createBitmap", "(IILandroid/graphics/Bitmap$Config;ZLandroid/"
                          "graphics/ColorSpace;)Landroid/graphics/Bitmap;")),
      createBitmap7(classRef().getStaticMethod(
          "createBitmap", "(Landroid/util/DisplayMetrics;IILandroid/graphics/"
                          "Bitmap$Config;Z)Landroid/graphics/Bitmap;")),
      createBitmap8(classRef().getStaticMethod(
          "createBitmap", "(Landroid/util/DisplayMetrics;IILandroid/graphics/"
                          "Bitmap$Config;ZLandroid/graphics/"
                          "ColorSpace;)Landroid/graphics/Bitmap;")),
      createBitmap9(classRef().getStaticMethod(
          "createBitmap",
          "([IIIIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap10(classRef().getStaticMethod(
          "createBitmap", "(Landroid/util/DisplayMetrics;[IIIIILandroid/"
                          "graphics/Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap11(classRef().getStaticMethod(
          "createBitmap",
          "([IIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap12(classRef().getStaticMethod(
          "createBitmap", "(Landroid/util/DisplayMetrics;[IIILandroid/graphics/"
                          "Bitmap$Config;)Landroid/graphics/Bitmap;")),
      createBitmap13(classRef().getStaticMethod(
          "createBitmap",
          "(Landroid/graphics/Picture;)Landroid/graphics/Bitmap;")),
      createBitmap14(classRef().getStaticMethod(
          "createBitmap", "(Landroid/graphics/Picture;IILandroid/graphics/"
                          "Bitmap$Config;)Landroid/graphics/Bitmap;")),
      compress(classRef().getMethod(
          "compress", "(Landroid/graphics/Bitmap$CompressFormat;ILjava/io/"
                      "OutputStream;)Z")),
      eraseColor(classRef().getMethod("eraseColor", "(I)V")),
      eraseColor1(classRef().getMethod("eraseColor", "(J)V")) {
    MetaBaseDroppable::dropClassRef();
}
Paint::Meta::Meta()
    : MetaBaseDroppable(Paint::getTypeName()),
      init(classRef().getMethod("<init>", "()V")),
      init1(classRef().getMethod("<init>", "(I)V")),
      init2(classRef().getMethod("<init>", "(Landroid/graphics/Paint;)V")),
      setAntiAlias(classRef().getMethod("setAntiAlias", "(Z)V")),
      setFilterBitmap(classRef().getMethod("setFilterBitmap", "(Z)V")),
      setColor(classRef().getMethod("setColor", "(I)V")),
      setColor1(classRef().getMethod("setColor", "(J)V")),
      getTextSize(classRef().getMethod("getTextSize", "()F")),
      setTextSize(classRef().getMethod("setTextSize", "(F)V")),
      ascent(classRef().getMethod("ascent", "()F")),
      descent(classRef().getMethod("descent", "()F")),
      measureText(classRef().getMethod("measureText", "([CII)F")),
      measureText1(
          classRef().getMethod("measureText", "(Ljava/lang/String;II)F")),
      measureText2(
          classRef().getMethod("measureText", "(Ljava/lang/String;)F")),
      measureText3(classRef().getMethod("measureText",
                                        "(Ljava/lang/CharSequence;II)F")) {
    MetaBaseDroppable::dropClassRef();
}
Canvas::Meta::Meta()
    : MetaBaseDroppable(Canvas::getTypeName()),
      init(classRef().getMethod("<init>", "()V")),
      init1(classRef().getMethod("<init>", "(Landroid/graphics/Bitmap;)V")),
      drawText(classRef().getMethod("drawText",
                                    "([CIIFFLandroid/graphics/Paint;)V")),
      drawText1(classRef().getMethod(
          "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V")),
      drawText2(classRef().getMethod(
          "drawText", "(Ljava/lang/String;IIFFLandroid/graphics/Paint;)V")),
      drawText3(classRef().getMethod(
          "drawText",
          "(Ljava/lang/CharSequence;IIFFLandroid/graphics/Paint;)V")) {
    MetaBaseDroppable::dropClassRef();
}
Color::Meta::Meta()
    : MetaBaseDroppable(Color::getTypeName()), BLACK(classRef(), "BLACK"),
      YELLOW(classRef(), "YELLOW") {
    MetaBaseDroppable::dropClassRef();
}
} // namespace android::graphics
} // namespace wrap
