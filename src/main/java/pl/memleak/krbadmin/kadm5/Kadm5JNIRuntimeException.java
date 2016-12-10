package pl.memleak.krbadmin.kadm5;

public class Kadm5JNIRuntimeException extends Kadm5RuntimeException {
    public Kadm5JNIRuntimeException() {
        super();
    }

    public Kadm5JNIRuntimeException(String message) {
        super(message);
    }

    public Kadm5JNIRuntimeException(String message, Throwable cause) {
        super(message, cause);
    }

    public Kadm5JNIRuntimeException(Throwable cause) {
        super(cause);
    }

    public Kadm5JNIRuntimeException(String message, Throwable cause, boolean enableSuppression,
                                    boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
