#!/bin/sh
# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
set -e

./makeWrapper.py "$@" && /opt/homebrew/opt/llvm/bin/clang-format -style=file -i wrap/*.cpp wrap/*.h
