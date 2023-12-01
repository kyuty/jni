# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""Utilities to find the Android SDK."""

import os
from pathlib import Path
import platform

def generate_possible_sdk_roots():
    """Return a generator yielding possible Android SDK roots in preference order."""
    android_home = os.getenv('ANDROID_HOME')
    if android_home:
        yield Path(android_home)

    sdk_root = os.getenv('ANDROID_SDK_ROOT')
    if sdk_root:
        yield Path(sdk_root)

    sdk_home = os.getenv('ANDROID_SDK_HOME')
    if sdk_home:
        yield Path(sdk_home)

    if platform.system() == "Windows":
        appdata = os.getenv('appdata')
        if appdata:
            yield Path(appdata) / 'Android' / 'Sdk'
    else:
        home = os.getenv('HOME')
        if home:
            yield Path(home) / 'Android' / 'Sdk'

    ndk_home = os.getenv('ANDROID_NDK_HOME')
    if ndk_home:
        ndk_home = Path(ndk_home)
        # Sometimes this is wrapped in two layers of paths inside the SDK.
        yield ndk_home.parent.parent
        # Sometimes only one
        yield ndk_home.parent


def _version_from_framework_jar(f):
    verstr = f.parent.stem.replace('android-', '')
    return int(verstr)


def find_framework():
    """Find the Android framework jar in the SDK."""
    potential_roots = list()
    for possibility in generate_possible_sdk_roots():
        platforms_dir = (possibility / "platforms")
        if platforms_dir.exists() and (possibility / "sources").exists():
            potential_roots = (
                d / 'android.jar'
                for d in platforms_dir.glob('android-*')
                if (d / 'android.jar').exists()
            )
            # Sort by version, descending
            for jar in sorted(potential_roots, key=_version_from_framework_jar, reverse=True):
                # Take the newest one we find in the first root that has any
                # to match the semantics here:
                # https://developer.android.com/studio/command-line/variables
                return jar
