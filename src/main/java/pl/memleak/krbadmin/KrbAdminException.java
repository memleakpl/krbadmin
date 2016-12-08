package pl.memleak.krbadmin;

public class KrbAdminException extends Exception {
    public KrbAdminException() {
        super();
    }

    public KrbAdminException(String message) {
        super(message);
    }

    public KrbAdminException(String message, Throwable cause) {
        super(message, cause);
    }

    public KrbAdminException(Throwable cause) {
        super(cause);
    }

    public KrbAdminException(String message, Throwable cause, boolean enableSuppression, boolean
            writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
