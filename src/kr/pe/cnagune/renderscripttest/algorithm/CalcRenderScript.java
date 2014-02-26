package kr.pe.cnagune.renderscripttest.algorithm;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.renderscript.Allocation;
import android.renderscript.RenderScript;
import android.renderscript.ScriptC;
import android.util.Log;

import kr.pe.cnagune.renderscripttest.RenderScriptActivity;
import kr.pe.renderscripttest.R;
import kr.pe.renderscripttest.ScriptC_Argb8888_gray;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcRenderScript implements ICalc {
	private static final String TAG = "calcRenderScript";

	private Context context;

	public CalcRenderScript(Context context) {
		this.context = context;
	}

	@Override
	public String name() {
		return "calcRs";
	}

	@Override
	public Bitmap run(Bitmap bitmapIn) {
		int width = bitmapIn.getWidth();
		int height = bitmapIn.getHeight();

		Bitmap bitmap = Bitmap.createBitmap(width, height, bitmapIn.getConfig());
		long t1 = System.nanoTime();
		RenderScript rs = RenderScript.create(context);
		long t2 = System.nanoTime();
		Allocation inAllocation = Allocation.createFromBitmap(rs, bitmapIn,
				Allocation.MipmapControl.MIPMAP_NONE,
				Allocation.USAGE_SCRIPT);
		long t3 = System.nanoTime();
		Allocation outAllocation = Allocation.createTyped(rs, inAllocation.getType());
		long t4 = System.nanoTime();
		ScriptC_Argb8888_gray script = new ScriptC_Argb8888_gray(rs, context.getResources(), R.raw.argb8888_gray);
		long t5 = System.nanoTime();
		script.set_gIn(inAllocation);
		long t6 = System.nanoTime();
		script.set_gOut(outAllocation);
		long t7 = System.nanoTime();
		script.set_gScript(script);
		long t8 = System.nanoTime();
		script.invoke_filter();
//		try { Thread.sleep(200); } catch (Exception e) {}
		long t9 = System.nanoTime();

		outAllocation.copyTo(bitmap);
		long t10 = System.nanoTime();

		Log.d(TAG, String.format("1. RenderScript.create                       : %f", ((t2 - t1) / 1000.0)));
		Log.d(TAG, String.format("2. Allocation.createFromBitmap (inAllocation): %f", ((t3 - t2) / 1000.0)));
		Log.d(TAG, String.format("3. Allocation.createTyped (outAllocation)    : %f", ((t4 - t3) / 1000.0)));
		Log.d(TAG, String.format("4. ScriptC_Argb8888_gray                     : %f", ((t5 - t4) / 1000.0)));
		Log.d(TAG, String.format("5. script.set_gIn                            : %f", ((t6 - t5) / 1000.0)));
		Log.d(TAG, String.format("6. script.set_gOut                           : %f", ((t7 - t6) / 1000.0)));
		Log.d(TAG, String.format("7. script.set_gScript                        : %f", ((t8 - t7) / 1000.0)));
		Log.d(TAG, String.format("8. script.invoke_filter                      : %f", ((t9 - t8) / 1000.0)));
		Log.d(TAG, String.format("9. outAllocation.CopyTo                      : %f", ((t10 - t9) / 1000.0)));

		return bitmap;
	}
}
