package medialibrary;

public class Medialibrary {
    long instanceId = 0;

    public static native int nativeInit(String url);
    public static native int nativeSetSurface(Object surface);
    public static native int nativePlay();
    public static native int nativeStop();

    public void initNative(String url){
        nativeInit(url);
    }

    private static Medialibrary medialibrary = new Medialibrary();
}
