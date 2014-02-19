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
		Bitmap bitmap = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
		RsJNI.CopyToIn(bitmapIn);
		RsJNI.CreateMemoryToOut(width * height);
		RsJNI.CalcNdkThread(width * height, threadNum);
		RsJNI.CopyFromOut(bitmap);
		return bitmap;
	}
}
