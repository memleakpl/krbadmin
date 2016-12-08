package pl.memleak.krblib;

public class Kadm5JNIException extends Kadm5Exception {
    public Kadm5JNIException() {
        super();
    }

    public Kadm5JNIException(String message) {
        super(message);
    }

    public Kadm5JNIException(String message, Throwable cause) {
        super(message, cause);
    }

    public Kadm5JNIException(Throwable cause) {
        super(cause);
    }

    public Kadm5JNIException(String message, Throwable cause, boolean enableSuppression, boolean
            writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
