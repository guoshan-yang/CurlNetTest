package com.uushixun;

import com.example.curltest.R;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	static {
		System.loadLibrary("curl");
		System.loadLibrary("curlTest");
	}
	public native void Init();
	public native void Cleanup();
	public native void TestDownload();
	public native void TestHttpPost();
	private final String TAG = "curlTest";
	private void postDispose(String Data)
	{
		Log.i(TAG, Data);
	}
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Init();
		Button btnPost =  (Button) findViewById(R.id.main_post);
		Button btnDownload =  (Button) findViewById(R.id.main_download);
		btnPost.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				TestHttpPost();
			}
		});
		btnDownload.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				TestDownload();
			}
		});

	}
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		Cleanup();
	}
}
