package pl.memleak.krblib;

public class Kadm5Exception extends KrbAdminException {
    public Kadm5Exception() {
        super();
    }

    public Kadm5Exception(String message) {
        super(message);
    }

    public Kadm5Exception(String message, Throwable cause) {
        super(message, cause);
    }

    public Kadm5Exception(Throwable cause) {
        super(cause);
    }

    public Kadm5Exception(String message, Throwable cause, boolean enableSuppression, boolean
            writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
