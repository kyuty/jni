// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#include "java.io.h"

namespace wrap {
namespace java::io {
File::Meta::Meta()
    : MetaBaseDroppable(File::getTypeName()),
      init(classRef().getMethod("<init>", "(Ljava/lang/String;)V")),
      init1(classRef().getMethod("<init>",
                                 "(Ljava/lang/String;Ljava/lang/String;)V")),
      init2(classRef().getMethod("<init>",
                                 "(Ljava/io/File;Ljava/lang/String;)V")),
      init3(classRef().getMethod("<init>", "(Ljava/net/URI;)V")),
      exists(classRef().getMethod("exists", "()Z")),
      mkdirs(classRef().getMethod("mkdirs", "()Z")) {
    MetaBaseDroppable::dropClassRef();
}
FileOutputStream::Meta::Meta()
    : MetaBaseDroppable(FileOutputStream::getTypeName()),
      init(classRef().getMethod("<init>", "(Ljava/lang/String;)V")),
      init1(classRef().getMethod("<init>", "(Ljava/lang/String;Z)V")),
      init2(classRef().getMethod("<init>", "(Ljava/io/File;)V")),
      init3(classRef().getMethod("<init>", "(Ljava/io/File;Z)V")),
      init4(classRef().getMethod("<init>", "(Ljava/io/FileDescriptor;)V")),
      close(classRef().getMethod("close", "()V")) {
    MetaBaseDroppable::dropClassRef();
}
} // namespace java::io
} // namespace wrap
