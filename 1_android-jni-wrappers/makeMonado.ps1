# Copyright 2020-2021, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0

$repo = "..\monado-android"
$auxAndroidRelativeDir = "src\xrt\auxiliary\android"
$ipcAndroidRelativeDir = "src\xrt\ipc\android"
$jarBuildDir = "build\intermediates\compile_library_classes_jar"


python makeWrapper.py monado.json (Get-ChildItem -Recurse "$repo\$auxAndroidRelativeDir\$jarBuildDir" -Filter "*.jar") (Get-ChildItem -Recurse "$repo\$ipcAndroidRelativeDir\$jarBuildDir" -Filter "*.jar") $args

clang-format -style=file -i (Get-ChildItem wrap -Recurse -Filter "*.?pp") (Get-ChildItem wrap -Recurse -Filter "*.h")
