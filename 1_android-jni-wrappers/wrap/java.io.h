// Copyright 2020-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Ryan Pavlik <ryan.pavlik@collabora.com>

#pragma once

#include "ObjectWrapperBase.h"

namespace wrap {
namespace java::io {
class File;
class FileOutputStream;
} // namespace java::io

} // namespace wrap

namespace wrap {
namespace java::io {
/*!
 * Wrapper for java.io.File objects.
 */
class File : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "java/io/File";
    }

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.File(java.lang.String);`
     *
     * JNI signature: (Ljava/lang/String;)V
     *
     */
    static File construct(std::string &stringParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.File(java.lang.String, java.lang.String);`
     *
     * JNI signature: (Ljava/lang/String;Ljava/lang/String;)V
     *
     */
    static File construct(std::string &stringParam, std::string &stringParam1);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.File(java.io.File, java.lang.String);`
     *
     * JNI signature: (Ljava/io/File;Ljava/lang/String;)V
     *
     */
    static File construct(File &file, std::string &stringParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.File(java.net.URI);`
     *
     * JNI signature: (Ljava/net/URI;)V
     *
     */
    static File construct(jni::Object &uRI);

    /*!
     * Wrapper for the exists method
     *
     * Java prototype:
     * `public boolean exists();`
     *
     * JNI signature: ()Z
     *
     */
    bool exists();

    /*!
     * Wrapper for the mkdirs method
     *
     * Java prototype:
     * `public boolean mkdirs();`
     *
     * JNI signature: ()Z
     *
     */
    bool mkdirs();

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        jni::method_t init;
        jni::method_t init1;
        jni::method_t init2;
        jni::method_t init3;
        jni::method_t exists;
        jni::method_t mkdirs;

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
 * Wrapper for java.io.FileOutputStream objects.
 */
class FileOutputStream : public ObjectWrapperBase {
  public:
    using ObjectWrapperBase::ObjectWrapperBase;
    static constexpr const char *getTypeName() noexcept {
        return "java/io/FileOutputStream";
    }

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.FileOutputStream(java.lang.String) throws
     * java.io.FileNotFoundException;`
     *
     * JNI signature: (Ljava/lang/String;)V
     *
     */
    static FileOutputStream construct(std::string &stringParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.FileOutputStream(java.lang.String, boolean) throws
     * java.io.FileNotFoundException;`
     *
     * JNI signature: (Ljava/lang/String;Z)V
     *
     */
    static FileOutputStream construct(std::string &stringParam,
                                      bool booleanParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.FileOutputStream(java.io.File) throws
     * java.io.FileNotFoundException;`
     *
     * JNI signature: (Ljava/io/File;)V
     *
     */
    static FileOutputStream construct(File &file);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.FileOutputStream(java.io.File, boolean) throws
     * java.io.FileNotFoundException;`
     *
     * JNI signature: (Ljava/io/File;Z)V
     *
     */
    static FileOutputStream construct(File &file, bool booleanParam);

    /*!
     * Wrapper for a constructor
     *
     * Java prototype:
     * `public java.io.FileOutputStream(java.io.FileDescriptor);`
     *
     * JNI signature: (Ljava/io/FileDescriptor;)V
     *
     */
    static FileOutputStream construct(jni::Object &fileDescriptor);

    /*!
     * Wrapper for the close method
     *
     * Java prototype:
     * `public void close() throws java.io.IOException;`
     *
     * JNI signature: ()V
     *
     */
    void close();

    /*!
     * Class metadata
     */
    struct Meta : public MetaBaseDroppable {
        jni::method_t init;
        jni::method_t init1;
        jni::method_t init2;
        jni::method_t init3;
        jni::method_t init4;
        jni::method_t close;

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
} // namespace java::io
} // namespace wrap
#include "java.io.impl.h"
