package kr.pe.cnagune.renderscripttest;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import kr.pe.cnagune.renderscripttest.algorithm.CalcJava;
import kr.pe.cnagune.renderscripttest.algorithm.CalcNdk;
import kr.pe.cnagune.renderscripttest.algorithm.CalcNdkNeon;
import kr.pe.cnagune.renderscripttest.algorithm.CalcNdkNeonThread;
import kr.pe.cnagune.renderscripttest.algorithm.CalcNdkNeonThreadDirect;
import kr.pe.cnagune.renderscripttest.algorithm.CalcNdkThread;
import kr.pe.cnagune.renderscripttest.algorithm.CalcRenderScript;
import kr.pe.cnagune.renderscripttest.algorithm.ICalc;
import kr.pe.renderscripttest.R;

public class RenderScriptActivity extends Activity
{
	private static final String TAG = "RenderScriptActivity";
	private static final int ScaleImageViewWidth     = 320;
	private static final int ScaleImageViewHeight    = 240;
	private static final int LoopTime = 1;

	private ImageView image;
	private TextView result;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

	    image = (ImageView)findViewById(R.id.imgOrag);
	    result = (TextView)findViewById(R.id.result);

	    BitmapFactory.Options options = new BitmapFactory.Options();
	    options.inPreferredConfig = Bitmap.Config.ARGB_8888;
	    final Bitmap bitmapIn = BitmapFactory.decodeResource(getResources(), R.drawable.img1280, options);

	    image.setImageBitmap(Bitmap.createScaledBitmap(bitmapIn, ScaleImageViewWidth, ScaleImageViewHeight, true));


	    new Thread(new Runnable() {
		    @Override
		    public void run() {

			    // 1. 측정할 항목들 객체로 만든 후 리스트에 보관
			    List<ICalc> calcList= new ArrayList<ICalc>();
			    calcList.add(new CalcJava());
			    calcList.add(new CalcRenderScript(getApplicationContext()));
			    calcList.add(new CalcNdk());
			    calcList.add(new CalcNdkNeon());
			    calcList.add(new CalcNdkThread(2));
			    calcList.add(new CalcNdkThread(4));
			    calcList.add(new CalcNdkThread(8));
			    calcList.add(new CalcNdkNeonThread(2));
			    calcList.add(new CalcNdkNeonThread(4));
			    calcList.add(new CalcNdkNeonThread(8));
			    calcList.add(new CalcNdkNeonThreadDirect(2));
			    calcList.add(new CalcNdkNeonThreadDirect(4));
			    calcList.add(new CalcNdkNeonThreadDirect(8));

			    // 2. calcList 목록에 있는 테스트 1번씩 수행 (jit 관련 최적화 때문)
			    for (ICalc calc : calcList) {
				    calc.run(bitmapIn);
			    }

			    Log.d(TAG, "calc --------------------------------------------");

			    // 3. calcList 목록에 있는 테스트 본격 수행
			    Map<String, Long> sumMap = new LinkedHashMap<String, Long>();
			    for (int i = 0; i < LoopTime; i++) {
				    for (ICalc calc : calcList) {
					    long start = System.nanoTime();
					    calc.run(bitmapIn);
					    long end = System.nanoTime();

					    if (sumMap.containsKey(calc.name()) == false) {
						    sumMap.put(calc.name(), 0l);
					    }
					    sumMap.put(calc.name(), sumMap.get(calc.name()) + (end - start));

					    Log.d(TAG, String.format("Time) %-20s: %d", calc.name(), (end - start)));
				    }
			    }

			    // 4. 측정 결과 출력
			    StringBuffer resultBuffer = new StringBuffer();
			    for (Map.Entry<String, Long> entry : sumMap.entrySet()) {
				    resultBuffer.append(String.format("%-20s: %d\n", entry.getKey(), entry.getValue() / LoopTime));
			    }
			    final String resultString = resultBuffer.toString();
			    RenderScriptActivity.this.runOnUiThread(new Runnable() {
				    @Override
				    public void run() {
					    result.setText(resultString);

				    }
			    });
			    Log.d(TAG, resultString);
		    }
	    }).start();
    }
}


