// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#include "android.text.h"

namespace wrap {
namespace android::text {
TextUtils::Meta::Meta()
    : MetaBaseDroppable(TextUtils::getTypeName()),
      ellipsize(classRef().getStaticMethod(
          "ellipsize",
          "(Ljava/lang/CharSequence;Landroid/text/TextPaint;FLandroid/text/"
          "TextUtils$TruncateAt;)Ljava/lang/CharSequence;")),
      ellipsize1(classRef().getStaticMethod(
          "ellipsize",
          "(Ljava/lang/CharSequence;Landroid/text/TextPaint;FLandroid/text/"
          "TextUtils$TruncateAt;ZLandroid/text/"
          "TextUtils$EllipsizeCallback;)Ljava/lang/CharSequence;")) {
    MetaBaseDroppable::dropClassRef();
}
} // namespace android::text
} // namespace wrap
