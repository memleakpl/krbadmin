package pl.memleak.krbadmin;

public interface KrbAdmin extends AutoCloseable {
    void addPrincipal(String principal, String password) throws KrbAdminException;

    void deletePrincipal(String principal) throws KrbAdminException;

    void changePassword(String principal, String password) throws KrbAdminException;

    String getRealm() throws KrbAdminException;
}
