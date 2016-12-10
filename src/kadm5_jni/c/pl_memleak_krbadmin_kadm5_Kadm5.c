#include "../headers/pl_memleak_krbadmin_kadm5_Kadm5.h"

#include "../headers/throw_utils.h"

#include <string.h>
#include <kadm5/admin.h>

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeInitContext
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeInitContext(
    JNIEnv *env,
    jobject this_obj) {
  krb5_context *krb5_ctx = malloc(sizeof(*krb5_ctx));
  krb5_error_code krb5_error;

  if ((krb5_error = kadm5_init_krb5_context(krb5_ctx))) {
    throw(env, EX_RT,
          "krb5_error_code %d during kadm5_init_krb5_context()", krb5_error);
    free(krb5_ctx);
    return (jlong) NULL;
  }

  return (jlong) krb5_ctx;
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeFreeContext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeFreeContext(
    JNIEnv *env,
    jobject this_obj,
    jlong ctx) {
  krb5_context* krb5_ctx = (krb5_context *) ctx;
  krb5_free_context(*krb5_ctx);
  free(krb5_ctx);
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeFreeHandle
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeFreeHandle(
    JNIEnv *env,
    jobject this_obj,
    jlong j_handle) {
  kadm5_destroy((void *) j_handle);
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeInitWithSKey
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeInitWithSKey(
    JNIEnv *env,
    jobject this_obj,
    jlong j_ctx,
    jstring j_principal,
    jstring j_keytab) {
  krb5_context *krb5_ctx = (krb5_context *) j_ctx;
  char *str_principal, *str_keytab;
  kadm5_config_params kadm5_params;
  krb5_error_code krb5_error;
  void *handle = NULL;

  if (!krb5_ctx) {
    throw(env, EX_RT, "context is NULL");
    return (jlong) NULL;
  }
  if (!j_principal) {
    throw(env, EX_RT, "principal is NULL");
    return (jlong) NULL;
  }
  if (!j_keytab) {
    throw(env, EX_RT, "keytab is NULL");
    return (jlong) NULL;
  }

  memset(&kadm5_params, 0, sizeof(kadm5_params));

  kadm5_params.mask = KADM5_CONFIG_REALM;
  if ((krb5_error = krb5_get_default_realm(*krb5_ctx, &kadm5_params.realm))) {
    perror_throw(env, EX_RT, "krb5_get_default_realm", *krb5_ctx,
                      krb5_error);
    return (jlong) NULL;
  }

  str_principal = (char *) (*env)->GetStringUTFChars(env, j_principal, 0);
  str_keytab = (char *) (*env)->GetStringUTFChars(env, j_keytab, 0);

  if ((krb5_error = kadm5_init_with_skey(*krb5_ctx, str_principal, str_keytab,
                                        NULL, &kadm5_params,
                                        KADM5_STRUCT_VERSION,
                                        KADM5_API_VERSION_4, NULL,
                                        &handle)))
    perror_throw(env, EX, "kadm5_init_with_skey", *krb5_ctx, krb5_error);

  krb5_free_default_realm(*krb5_ctx, kadm5_params.realm);
  (*env)->ReleaseStringUTFChars(env, j_principal, str_principal);
  (*env)->ReleaseStringUTFChars(env, j_keytab, str_keytab);

  return (jlong) handle;
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeGetRealm
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeGetRealm(
    JNIEnv *env,
    jobject this_obj,
    jlong j_ctx) {
  krb5_context *krb5_ctx = (krb5_context *) j_ctx;
  krb5_error_code krb5_error;
  char *realm;
  jstring j_realm;

  if (!krb5_ctx) {
    throw(env, EX_RT, "context is NULL");
    return NULL;
  }

  if ((krb5_error = krb5_get_default_realm(*krb5_ctx, &realm))) {
    perror_throw(env, EX, "krb5_get_default_realm", *krb5_ctx,
                 krb5_error);
    return NULL;
  }

  j_realm = (*env)->NewStringUTF(env, realm);

  krb5_free_default_realm(*krb5_ctx, realm);

  return j_realm;
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeCreatePrincipal
 * Signature: (JJLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeCreatePrincipal(
    JNIEnv *env,
    jobject this_obj,
    jlong j_context,
    jlong j_handle,
    jstring j_principal,
    jstring j_password) {
  krb5_context *krb5_ctx = (krb5_context *) j_context;
  void *krb5_handle = (void *) j_handle;
  krb5_error_code krb5_error;
  kadm5_principal_ent_rec krb5_principal;
  const char *str_principal = NULL;
  const char *str_password = NULL;
  long mask = KADM5_PRINCIPAL;

  if (!krb5_handle) {
    throw(env, EX_RT, "handle is NULL");
    return;
  }
  if (!j_principal) {
    throw(env, EX_RT, "principal is NULL");
    return;
  }
  if (!j_password) {
    throw(env, EX_RT, "password is NULL");
    return;
  }

  memset(&krb5_principal, 0, sizeof(krb5_principal));

  str_principal = (*env)->GetStringUTFChars(env, j_principal, 0);
  krb5_error = krb5_parse_name(*krb5_ctx, str_principal,
                               &krb5_principal.principal);
  (*env)->ReleaseStringUTFChars(env, j_principal, str_principal);
  if (krb5_error) {
    perror_throw(env, EX_RT, "krb5_parse_name", *krb5_ctx, krb5_error);
    return;
  }

  str_password = (*env)->GetStringUTFChars(env, j_password, 0);

  if ((krb5_error = kadm5_create_principal(krb5_handle, &krb5_principal, mask,
                                           (char *) str_password)))
    perror_throw(env, EX, "kadm5_create_principal", *krb5_ctx, krb5_error);

  (*env)->ReleaseStringUTFChars(env, j_password, str_password);
  krb5_free_principal(*krb5_ctx, krb5_principal.principal);
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeDeletePrincipal
 * Signature: (JJLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeDeletePrincipal(
    JNIEnv *env,
    jobject this_obj,
    jlong j_context,
    jlong j_handle,
    jstring j_principal) {
  krb5_context *krb5_ctx = (krb5_context *) j_context;
  void *handle = (void *) j_handle;
  const char* str_principal;
  krb5_error_code krb5_error;
  krb5_principal krb5_principal;

  if (!krb5_ctx) {
    throw(env, EX_RT, "context is NULL");
    return;
  }
  if (!handle) {
    throw(env, EX_RT, "handle is NULL");
    return;
  }
  if (!j_principal) {
    throw(env, EX_RT, "principal is NULL");
    return;
  }

  str_principal = (*env)->GetStringUTFChars(env, j_principal, 0);

  krb5_error = krb5_parse_name(*krb5_ctx, str_principal, &krb5_principal);
  (*env)->ReleaseStringUTFChars(env, j_principal, str_principal);
  if (krb5_error) {
    perror_throw(env, EX_RT, "krb5_parse_name", *krb5_ctx, krb5_error);
    return;
  }

  krb5_error = kadm5_delete_principal(handle, krb5_principal);
  krb5_free_principal(*krb5_ctx, krb5_principal);

  if (krb5_error)
    perror_throw(env, EX, "kadm5_delete_principal", *krb5_ctx, krb5_error);
}

/*
 * Class:     pl_memleak_krbadmin_kadm5_Kadm5
 * Method:    nativeChangePassword
 * Signature: (JJLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_pl_memleak_krbadmin_kadm5_Kadm5_nativeChangePassword(
    JNIEnv *env,
    jobject this_obj,
    jlong j_context,
    jlong j_handle,
    jstring j_principal,
    jstring j_password) {
  krb5_context *krb5_ctx = (krb5_context *) j_context;
  void *handle = (void *) j_handle;
  const char *str_principal, *str_password;
  krb5_error_code krb5_error;
  krb5_principal krb5_principal;

  if (!j_context) {
    throw(env, EX_RT, "context is NULL");
    return;
  }
  if (!handle) {
    throw(env, EX_RT, "handle is NULL");
    return;
  }
  if (!j_principal) {
    throw(env, EX_RT, "principal is NULL");
    return;
  }
  if (!j_password) {
    throw(env, EX_RT, "password is NULL");
    return;
  }

  str_principal = (*env)->GetStringUTFChars(env, j_principal, 0);

  krb5_error = krb5_parse_name(*krb5_ctx, str_principal, &krb5_principal);
  (*env)->ReleaseStringUTFChars(env, j_principal, str_principal);
  if (krb5_error) {
    perror_throw(env, EX_RT, "krb5_parse_name", *krb5_ctx, krb5_error);
    return;
  }

  str_password = (*env)->GetStringUTFChars(env, j_password, 0);

  if ((krb5_error = kadm5_chpass_principal(handle, krb5_principal,
                                           (char*) str_password)))
    perror_throw(env, EX, "kadm5_chpass_principal", *krb5_ctx, krb5_error);

  (*env)->ReleaseStringUTFChars(env, j_password, str_password);
  krb5_free_principal(*krb5_ctx, krb5_principal);
}
