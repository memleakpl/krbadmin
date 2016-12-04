#include "../headers/throw_utils.h"

void throw(JNIEnv *env, const char* format, ...) {
  const jclass e = (*env)->FindClass(env,"pl/memleak/krblib/Kadm5JNIException");
  va_list args;
  char msg[255];

  if (!e) return;

  va_start(args, format);
  vsnprintf(msg, sizeof(msg), format, args);
  va_end(args);

  (*env)->ThrowNew(env, e, msg);
}

void krb5_perror_throw(JNIEnv *env, const char *fun, krb5_context ctx,
                       krb5_error_code code) {
  const char *message;

  if (!env || !fun || !ctx)
    return;

  message = krb5_get_error_message(ctx, code);
  throw(env, "%s() failed: %s", fun, message);
  krb5_free_error_message(ctx, message);
}
