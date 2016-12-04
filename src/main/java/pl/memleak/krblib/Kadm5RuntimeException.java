package pl.memleak.krblib;

public class Kadm5RuntimeException extends RuntimeException {
    public Kadm5RuntimeException() {
        super();
    }

    public Kadm5RuntimeException(String message) {
        super(message);
    }

    public Kadm5RuntimeException(String message, Throwable cause) {
        super(message, cause);
    }

    public Kadm5RuntimeException(Throwable cause) {
        super(cause);
    }

    public Kadm5RuntimeException(String message, Throwable cause, boolean enableSuppression,
                                 boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
