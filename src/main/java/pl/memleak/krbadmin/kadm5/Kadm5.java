package pl.memleak.krbadmin.kadm5;

import pl.memleak.krbadmin.KrbAdmin;

import java.io.Closeable;
import java.io.IOException;

/**
 * krb5 MIT Admin API (KADM5) version 2
 *
 * @author mmos
 */
public class Kadm5 implements KrbAdmin, Closeable {
    private Long context;
    private Long handle;

    public Kadm5(String jniAbsolutePath, String principal, String keytab) {
        System.load(jniAbsolutePath);
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

    @Override
    public String getRealm() throws Kadm5Exception {
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

    private native String nativeGetRealm(long context) throws Kadm5JNIException;

    private native void nativeAddPrincipal(long context, long handle, String principal,
                                           String password) throws Kadm5JNIException;

    private native void nativeDeletePrincipal(long context, long handle, String principal) throws
            Kadm5JNIException;

    private native void nativeChangePassword(long context, long handle, String principal,
                                             String password) throws Kadm5JNIException;
}
