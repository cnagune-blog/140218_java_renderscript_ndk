package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;

import kr.pe.cnagune.renderscripttest.RsJNI;
import kr.pe.renderscripttest.R;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcNdkNeon implements ICalc {
	@Override
	public String name() {
		return "calcNdkNeon";
	}

	@Override
	public Bitmap run(Bitmap bitmapIn) {
		int width = bitmapIn.getWidth();
		int height = bitmapIn.getHeight();
		Bitmap bitmap = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
		RsJNI.CopyToIn(bitmapIn);
		RsJNI.CreateMemoryToOut(width * height);
		RsJNI.CalcNdkNeon(width * height);
		RsJNI.CopyFromOut(bitmap);
		return bitmap;
	}
}
