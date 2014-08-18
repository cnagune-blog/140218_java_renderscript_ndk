package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;

import kr.pe.cnagune.renderscripttest.RsJNI;
import kr.pe.renderscripttest.R;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcNdkThread implements ICalc {
	private int threadNum;

	public CalcNdkThread(int threadNum) {
		this.threadNum = threadNum;
	}

	@Override
	public String name() {
		return "calcNdkThread(" + threadNum + ")";
	}

	@Override
	public Bitmap run(Bitmap bitmapIn) {
        int width = bitmapIn.getWidth();
        int height = bitmapIn.getHeight();
        Bitmap bitmapOut = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
        RsJNI.CalcNdkThread(bitmapIn, bitmapOut, threadNum);
        return bitmapOut;
	}
}
