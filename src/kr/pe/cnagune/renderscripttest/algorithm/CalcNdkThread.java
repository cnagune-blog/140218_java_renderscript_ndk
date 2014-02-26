package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;
import android.util.Log;

import kr.pe.cnagune.renderscripttest.RsJNI;
import kr.pe.renderscripttest.R;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcNdkThread implements ICalc {
	private static final String TAG = "calcNdkThread";

	private int threadNum;

	public CalcNdkThread(int threadNum) {
		this.threadNum = threadNum;
	}

	@Override
	public String name() {
		return TAG + "(" + threadNum + ")";
	}

	@Override
	public Bitmap run(Bitmap bitmapIn) {
		int width = bitmapIn.getWidth();
		int height = bitmapIn.getHeight();
		Bitmap bitmap = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
		long t1 = System.nanoTime();
		RsJNI.CopyToIn(bitmapIn);
		long t2 = System.nanoTime();
		RsJNI.CreateMemoryToOut(width * height);
		long t3 = System.nanoTime();
		RsJNI.CalcNdkThread(width * height, threadNum);
		long t4 = System.nanoTime();
		RsJNI.CopyFromOut(bitmap);
		long t5 = System.nanoTime();

		Log.d(TAG, String.format("1. CopyToIn         : %f", ((t2 - t1) / 1000.0)));
		Log.d(TAG, String.format("2. CreateMemoryToOut: %f", ((t3 - t2) / 1000.0)));
		Log.d(TAG, String.format("3. CalcNdkThread    : %f", ((t4 - t3) / 1000.0)));
		Log.d(TAG, String.format("4. CopyFromOut      : %f", ((t5 - t4) / 1000.0)));

		return bitmap;
	}
}
