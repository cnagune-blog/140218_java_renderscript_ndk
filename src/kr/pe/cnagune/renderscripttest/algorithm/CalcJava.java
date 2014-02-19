package kr.pe.cnagune.renderscripttest.algorithm;

import android.graphics.Bitmap;

import kr.pe.renderscripttest.R;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcJava implements ICalc {
	@Override
	public String name() {
		return "calcJava";
	}

	@Override
	public Bitmap run(Bitmap bitmapIn) {
		int width = bitmapIn.getWidth();
		int height = bitmapIn.getHeight();
		Bitmap bitmap = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
		int size = width * height;
		int [] pixels = new int[size];
		bitmapIn.getPixels(pixels, 0, width, 0, 0, width, height);

		for (int i = 0; i < size; i++) {
			int c = pixels[i];  // 0xAARRGGBB
			int r = (c >> 16) & 0xff;   // 0xRR
			int g = (c >> 8)  & 0xff;   // 0xGG
			int b =  c        & 0xff;   // 0xBB
			int y = (r * 76 + g * 151 + b * 29) >> 8; // luminance
			pixels[i] = y | (y << 8) | (y << 16) | (c & 0xff000000);
		}
		bitmap.setPixels(pixels, 0, width, 0, 0, width, height);
		return bitmap;
	}
}
