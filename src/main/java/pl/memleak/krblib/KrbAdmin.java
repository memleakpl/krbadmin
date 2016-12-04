package pl.memleak.krblib;

public interface KrbAdmin {
    void addPrincipal(String principal, String password) throws KrbAdminException;

    void deletePrincipal(String principal) throws KrbAdminException;

    void changePassword(String principal, String password) throws KrbAdminException;
}
