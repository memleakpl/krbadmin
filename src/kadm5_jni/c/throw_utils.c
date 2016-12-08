#include "../headers/throw_utils.h"

const char *exception_map[] = {
  "pl/memleak/krblib/Kadm5JNIException",
  "pl/memleak/krblib/Kadm5JNIRuntimeException"
};

void throw(JNIEnv *env, ex e, const char* format, ...) {
  const jclass j_ex = (*env)->FindClass(env, exception_map[e]);
  va_list args;
  char msg[255];

  if(!j_ex) return;

  va_start(args, format);
  vsnprintf(msg, sizeof(msg), format, args);
  va_end(args);

  (*env)->ThrowNew(env, j_ex, msg);
}

void perror_throw(JNIEnv *env, ex e, const char *fun,
                  krb5_context ctx, krb5_error_code code) {
  const char *message = krb5_get_error_message(ctx, code);
  throw(env, e, "%s() failed: %s", fun, message);
  krb5_free_error_message(ctx, message);
}
