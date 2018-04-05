package github.trainsoundcom.ui;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import github.trainsoundcom.boplayer.R;
import medialibrary.Medialibrary;

public class MainActivity extends AppCompatActivity {

    private Button startBtn, stopBtn;
    private String TAG = "MAINACTIVITY";

    Medialibrary media = new Medialibrary();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startBtn = (Button)findViewById(R.id.startBtn);
        stopBtn = (Button)findViewById(R.id.stoptBtn);

    //    Medialibrary media = new Medialibrary();

        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.e(TAG, "start");
                media.nativeInit();
            }
        });

        stopBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Log.e(TAG, "stop");
            }
        });
    }
}
