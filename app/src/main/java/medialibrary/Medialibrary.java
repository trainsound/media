package medialibrary;

public class Medialibrary {
    static {
        System.loadLibrary("medialib");
    }
    public static native int nativeInit(String url);
    public static native int nativeSetSurface(Object surface);
    public static native int nativePlay();
    public static native int nativeStop();
}
