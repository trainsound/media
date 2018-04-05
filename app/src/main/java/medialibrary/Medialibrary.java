package medialibrary;

public class Medialibrary {
    static {
        System.loadLibrary("medialib");
    }
    public static native int nativeInit();
}
