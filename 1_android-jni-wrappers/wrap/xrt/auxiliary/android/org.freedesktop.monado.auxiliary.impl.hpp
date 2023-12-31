// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Inline implementations for partially-generated wrapper for the
 * `org.freedesktop.monado.auxiliary` Java package - do not include on its own!
 * @author Ryan Pavlik <ryan.pavlik@collabora.com>
 * @ingroup aux_android
 */

#pragma once

#include "wrap/android.app.h"
#include "wrap/android.view.h"

namespace wrap {
namespace org::freedesktop::monado::auxiliary {
	inline void *
	MonadoView::getNativePointer()
	{
		assert(!isNull());
		return reinterpret_cast<void *>(
		    static_cast<intptr_t>(object().call<int64_t>(Meta::data().getNativePointer)));
	}

	inline MonadoView
	MonadoView::attachToActivity(android::app::Activity const &activity, void *nativePointer)
	{
		return MonadoView(Meta::data().clazz().call<jni::Object>(
		    Meta::data().attachToActivity, activity.object(),
		    static_cast<long long>(reinterpret_cast<uintptr_t>(nativePointer))));
	}

	inline MonadoView
	MonadoView::attachToActivity(android::app::Activity const &activity)
	{
		return MonadoView(
		    Meta::data().clazz().call<jni::Object>(Meta::data().attachToActivity1, activity.object()));
	}

	inline jni::Object
	MonadoView::getDisplayMetrics(android::app::Activity const &activity)
	{
		return Meta::data().clazz().call<jni::Object>(Meta::data().getDisplayMetrics, activity.object());
	}

	inline android::view::SurfaceHolder
	MonadoView::waitGetSurfaceHolder(int32_t wait_ms)
	{
		assert(!isNull());
		return android::view::SurfaceHolder(
		    object().call<jni::Object>(Meta::data().waitGetSurfaceHolder, wait_ms));
	}

	inline void
	MonadoView::markAsDiscardedByNative()
	{
		assert(!isNull());
		return object().call<void>(Meta::data().markAsDiscardedByNative);
	}
} // namespace org::freedesktop::monado::auxiliary
} // namespace wrap
