package medialibrary;

public class Medialibrary {
    long instanceId = 0;

    public static native int nativeInit(Medialibrary lib, String url);
    public static native int nativeSetSurface(Object surface);
    public static native int nativePlay();
    public static native int nativeStop();

    private static Medialibrary medialibrary = new Medialibrary();
}
