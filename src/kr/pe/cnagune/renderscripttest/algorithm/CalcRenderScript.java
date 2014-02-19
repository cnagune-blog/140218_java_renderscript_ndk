package kr.pe.cnagune.renderscripttest.algorithm;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.renderscript.Allocation;
import android.renderscript.RenderScript;
import android.renderscript.ScriptC;

import kr.pe.cnagune.renderscripttest.RenderScriptActivity;
import kr.pe.renderscripttest.R;
import kr.pe.renderscripttest.ScriptC_Argb8888_gray;

/**
 * Created by cnagune on 11/11/13.
 */
public class CalcRenderScript implements ICalc {
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
		RenderScript rs = RenderScript.create(context);
		Allocation inAllocation = Allocation.createFromBitmap(rs, bitmapIn,
				Allocation.MipmapControl.MIPMAP_NONE,
				Allocation.USAGE_SCRIPT);
		Allocation outAllocation = Allocation.createTyped(rs, inAllocation.getType());
		ScriptC_Argb8888_gray script = new ScriptC_Argb8888_gray(rs, context.getResources(), R.raw.argb8888_gray);
		script.set_gIn(inAllocation);
		script.set_gOut(outAllocation);
		script.set_gScript(script);
		script.invoke_filter();

		outAllocation.copyTo(bitmap);

		return bitmap;
	}
}
