package github.trainsoundcom.ui;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;

import github.trainsoundcom.boplayer.R;
import medialibrary.Medialibrary;

public class MainActivity extends AppCompatActivity implements SurfaceHolder.Callback{

    static {
        System.loadLibrary("medialib");
    }

    private Button startBtn, stopBtn;
    private String TAG = "MAINACTIVITY";

    Medialibrary media = new Medialibrary();
    SurfaceView surfaceview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startBtn = (Button)findViewById(R.id.startBtn);
        stopBtn = (Button)findViewById(R.id.stoptBtn);

        media.initNative("/sdcard/media/boyoung.mp4");
//        media.nativeInit("/sdcard/media/boyoung.mp4");

        surfaceview = (SurfaceView)findViewById(R.id.surfaceView);
        surfaceview.getHolder().addCallback(this);
    //    Medialibrary media = new Medialibrary();

        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.e(TAG, "start");
                media.nativePlay();
            }
        });

        stopBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Log.e(TAG, "stop");
            }
        });
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.d("GStreamer", "Surface created: " + holder.getSurface());
        Medialibrary.nativeSetSurface(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
