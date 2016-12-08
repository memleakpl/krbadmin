#ifndef KRBLIB_THROW_UTILS_H
#define KRBLIB_THROW_UTILS_H

#include <jni.h>
#include <kadm5/admin.h>

typedef enum {
  EX,
  EX_RT
} ex;

void throw(JNIEnv *env, ex e, const char* format, ...);

void perror_throw(JNIEnv *env, ex e, const char *fun,
                  krb5_context ctx, krb5_error_code code);

#endif
