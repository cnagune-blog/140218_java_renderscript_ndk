package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;
import android.util.Log;

import kr.pe.cnagune.renderscripttest.RsJNI;
import kr.pe.renderscripttest.R;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcNdkNeonThreadDirect implements ICalc {
	private static final String TAG = "calcNdkNeonThreadDirect";

	private int threadNum;

	public CalcNdkNeonThreadDirect(int threadNum) {
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
		RsJNI.CalcNdkNeonThreadDirect(bitmapIn, bitmap, threadNum);
		long t2 = System.nanoTime();
		Log.d(TAG, String.format("1. CalcNdkNeonThreadDirect: %f", ((t2 - t1) / 1000.0)));
		return bitmap;
	}
}
