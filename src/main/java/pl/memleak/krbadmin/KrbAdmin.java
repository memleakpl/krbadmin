package pl.memleak.krbadmin;

public interface KrbAdmin extends AutoCloseable {
    void createPrincipal(String principal, String password) throws KrbAdminException;

    void deletePrincipal(String principal) throws KrbAdminException;

    void changePassword(String principal, String password) throws KrbAdminException;

    String getRealm() throws KrbAdminException;
}
