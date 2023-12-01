// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Out-of-line implementations for partially-generated wrapper for the
 * `org.freedesktop.monado.auxiliary` Java package.
 * @author Ryan Pavlik <ryan.pavlik@collabora.com>
 * @ingroup aux_android
 */

#include "org.freedesktop.monado.auxiliary.hpp"

namespace wrap {
namespace org::freedesktop::monado::auxiliary {
	MonadoView::Meta::Meta(jni::jclass clazz)
	    : MetaBase(MonadoView::getTypeName(), clazz),
	      getNativePointer(classRef().getMethod("getNativePointer", "()J")),
	      attachToActivity(classRef().getStaticMethod("attachToActivity",
	                                                  "(Landroid/app/Activity;J)Lorg/freedesktop/"
	                                                  "monado/auxiliary/MonadoView;")),
	      attachToActivity1(classRef().getStaticMethod("attachToActivity",
	                                                   "(Landroid/app/Activity;)Lorg/freedesktop/monado/"
	                                                   "auxiliary/MonadoView;")),
	      getDisplayMetrics(classRef().getStaticMethod("getDisplayMetrics",
	                                                   "(Landroid/app/Activity;)Landroid/util/DisplayMetrics;")),
	      waitGetSurfaceHolder(classRef().getMethod("waitGetSurfaceHolder", "(I)Landroid/view/SurfaceHolder;")),
	      markAsDiscardedByNative(classRef().getMethod("markAsDiscardedByNative", "()V"))
	{}
} // namespace org::freedesktop::monado::auxiliary
} // namespace wrap
