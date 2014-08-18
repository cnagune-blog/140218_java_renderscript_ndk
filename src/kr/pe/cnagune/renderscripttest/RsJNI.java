package kr.pe.cnagune.renderscripttest;

import android.graphics.Bitmap;

/**
 * Created by cnagune on 11/3/13.
 */
public class RsJNI {
	static {
		System.loadLibrary("Rs-jni");
	}

	public native static void CalcNdk(Bitmap bitmapIn, Bitmap bitmapOut);
	public native static void CalcNdkNeon(Bitmap bitmapIn, Bitmap bitmapOut);
	public native static void CalcNdkThread(Bitmap bitmapIn, Bitmap bitmapOut, int threadNum);
	public native static void CalcNdkNeonThread(Bitmap bitmapIn, Bitmap bitmapOut, int threadNum);
}
