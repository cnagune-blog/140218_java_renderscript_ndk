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
        Bitmap bitmapOut = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
        RsJNI.CalcNdkNeon(bitmapIn, bitmapOut);
        return bitmapOut;
	}
}
