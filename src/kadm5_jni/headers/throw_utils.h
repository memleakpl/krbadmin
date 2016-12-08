#ifndef KADM5_JNI_THROW_UTILS_H
#define KADM5_JNI_THROW_UTILS_H

#include <stdbool.h>

#include <jni.h>
#include <kadm5/admin.h>

void throw(JNIEnv *env, const char* format, ...);

void krb5_perror_throw(JNIEnv *env, const char *fun, krb5_context ctx,
                       krb5_error_code code);

bool throw_on_invalid_context(JNIEnv *env, krb5_context *ctx);

#endif
