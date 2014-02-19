package kr.pe.cnagune.renderscripttest;

import android.graphics.Bitmap;

/**
 * Created by cnagune on 11/3/13.
 */
public class RsJNI {
	static {
		System.loadLibrary("Rs-jni");
	}

	public native static void CopyToIn(Bitmap bitmap);
	public native static void CreateMemoryToOut(int size);
	public native static void CopyFromOut(Bitmap bitmap);

	public native static void CalcNdk(int size);
	public native static void CalcNdkNeon(int size);
	public native static void CalcNdkThread(int size, int thread_cnt);
	public native static void CalcNdkNeonThread(int size, int thread_cnt);
	public native static void CalcNdkNeonThreadDirect(Bitmap in, Bitmap out, int thread_cnt);
}
