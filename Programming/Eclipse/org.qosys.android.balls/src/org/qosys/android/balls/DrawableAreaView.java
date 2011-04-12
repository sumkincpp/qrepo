package org.qosys.android.balls;

import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.OvalShape;
import android.graphics.drawable.shapes.RectShape;
import android.content.Context;
import android.graphics.Canvas;
import android.os.Bundle;

public class DrawableAreaView extends View {
    private ShapeDrawable mDrawable;

	public DrawableAreaView(Context context, AttributeSet attrs) {
		super(context, attrs);

        init (context);
	}
	public DrawableAreaView(Context context) {
        super(context);	
        
        init (context);
	}
	
	public void init (Context context) {
		mDrawable = new ShapeDrawable(new RectShape());
	}
	
	protected void onDraw(Canvas canvas) {
        mDrawable.draw(canvas);
    }	
	
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
	    super.onMeasure(widthMeasureSpec, heightMeasureSpec);

	    int parentWidth = MeasureSpec.getSize(widthMeasureSpec);
	    int parentHeight = MeasureSpec.getSize(heightMeasureSpec);

	    int x = 0, y = 0;
		  
		mDrawable.getPaint().setColor(0xff74AC23);
		mDrawable.setBounds(x, y, x + parentWidth, y + parentHeight);   
		
	    
	    this.setMeasuredDimension(
	            parentWidth, parentHeight);
	}

}
