package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;

/**
 * Created by cnagune on 11/11/13.
 */
public interface ICalc {
	String name();
	Bitmap run(Bitmap bitmapIn);
}
