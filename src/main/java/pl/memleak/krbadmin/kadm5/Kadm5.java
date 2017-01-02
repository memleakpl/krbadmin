package pl.memleak.krbadmin.kadm5;

import pl.memleak.krbadmin.KrbAdmin;

import java.io.IOException;

/**
 * krb5 MIT Admin API (KADM5) version 2
 *
 * @author mmos
 */
public class Kadm5 implements KrbAdmin {
    private String principal;
    private String keytab;

    public Kadm5(String jniAbsolutePath, String principal, String keytab) {
        this.keytab = keytab;
        this.principal = principal;
        System.load(jniAbsolutePath);
    }

    @Override
    public void createPrincipal(String principal, String password) throws Kadm5Exception {
        Long context = null;
        Long handle = null;
        try {
            context = nativeInitContext();
            handle = nativeInitWithSKey(context, this.principal, keytab);
            nativeCreatePrincipal(context, handle, principal, password);
        } finally {
            if(handle != null) nativeFreeHandle(handle);
            if(context != null) nativeFreeContext(context);
        }
    }

    @Override
    public void deletePrincipal(String principal) throws Kadm5Exception {
        Long context = null;
        Long handle = null;
        try {
            context = nativeInitContext();
            handle = nativeInitWithSKey(context, this.principal, keytab);
            nativeDeletePrincipal(context, handle, principal);
        } finally {
            if(handle != null) nativeFreeHandle(handle);
            if(context != null) nativeFreeContext(context);
        }
    }

    @Override
    public void changePassword(String principal, String password) throws Kadm5Exception {
        Long context = null;
        Long handle = null;
        try {
            context = nativeInitContext();
            handle = nativeInitWithSKey(context, this.principal, keytab);
            nativeChangePassword(context, handle, principal, password);
        } finally {
            if(handle != null) nativeFreeHandle(handle);
            if(context != null) nativeFreeContext(context);
        }
    }

    @Override
    public void close() throws IOException {
    }

    @Override
    public String getRealm() throws Kadm5Exception {
        Long context = null;
        String realm;
        try {
            context = nativeInitContext();
            realm = nativeGetRealm(context);
        } finally {
            if(context != null) nativeFreeContext(context);
        }
        return realm;
    }

    private native long nativeInitContext();

    private native void nativeFreeContext(long context);

    private native void nativeFreeHandle(long handle);

    private native long nativeInitWithSKey(long context, String principal, String keytab);

    private native String nativeGetRealm(long context) throws Kadm5JNIException;

    private native void nativeCreatePrincipal(long context, long handle, String principal,
                                              String password) throws Kadm5JNIException;

    private native void nativeDeletePrincipal(long context, long handle, String principal) throws
            Kadm5JNIException;

    private native void nativeChangePassword(long context, long handle, String principal,
                                             String password) throws Kadm5JNIException;
}
