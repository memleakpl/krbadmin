package pl.memleak.krblib;

import java.io.Closeable;
import java.io.IOException;

/**
 * krb5 MIT Admin API (KADM5) version 2
 *
 * @author mmos
 */
public class Kadm5 implements KrbAdmin, Closeable {
    static {
        try {
            System.loadLibrary("kadm5_jni");
        } catch (UnsatisfiedLinkError e) {
            throw new Kadm5JNIException("Failed to load JNI library", e);
        }
    }

    private Long context;
    private Long handle;

    public Kadm5(String principal, String keytab) {
        context = nativeInitContext();
        handle = nativeInitWithSKey(context, principal, keytab);
    }

    @Override
    public void addPrincipal(String principal, String password) throws Kadm5Exception {
        assertInitialized();
        nativeAddPrincipal(context, handle, principal, password);
    }

    @Override
    public void deletePrincipal(String principal) throws Kadm5Exception {
        assertInitialized();
        nativeDeletePrincipal(context, handle, principal);
    }

    @Override
    public void changePassword(String principal, String password) throws Kadm5Exception {
        assertInitialized();
        nativeChangePassword(context, handle, principal, password);
    }

    @Override
    public void close() throws IOException {
        freeContext();
        freeHandle();
    }

    public String getRealm() {
        assertContextInitialized();
        return nativeGetRealm(context);
    }

    private void freeContext() {
        nativeFreeContext(context);
        context = null;
    }

    private void freeHandle() {
        nativeFreeHandle(handle);
        handle = null;
    }

    private void assertContextInitialized() {
        if (context == null)
            throw new Kadm5RuntimeException("Context is not initialized");
    }

    private void assertHandleInitialized() {
       if(handle == null)
           throw new Kadm5RuntimeException("Handle is not initialized");
    }

    private void assertInitialized() {
       assertContextInitialized();
       assertHandleInitialized();
    }

    private native long nativeInitContext();

    private native void nativeFreeContext(long context);

    private native void nativeFreeHandle(long handle);

    private native long nativeInitWithSKey(long context, String principal, String keytab);

    private native String nativeGetRealm(long context);

    private native void nativeAddPrincipal(long context, long handle, String principal, String
            password);

    private native void nativeDeletePrincipal(long context, long handle, String principal);

    private native void nativeChangePassword(long context, long handle, String principal, String
            password);
}
