package org.qosys.android.balls;

import java.util.Random;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;
import android.view.View.MeasureSpec;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;


public class ViewBall extends View implements IMovable, SensorEventListener {
	private float x;
	private float y;
	private float vx;
	private float vy;
	private final int r;
	private float dt;
	private final Paint mPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
	
	private int screenWidth = 0;
	private int screenHeight = 0;
	
	public static float TIME_STEP = 0.1f; 
	
	public ViewBall(Context context, float ix, float iy, int ir) {
		super(context);
		
		
		Random r = new Random();
		int c =  Color.rgb(r.nextInt(150), r.nextInt(150), r.nextInt(150));
		
		Log.d(Integer.toString(c), "colo");
		
		mPaint.setColor(c);
		this.x = ix;
		this.y = iy;
		this.vx = r.nextInt(10);
		this.vy = r.nextInt(10);
		this.r = ir;
		this.dt = 0.1f;
	}

	 @Override
	 protected void onDraw(Canvas canvas) {
	     super.onDraw(canvas);
	     canvas.drawCircle(x, y, r, mPaint);
	 	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
	    super.onMeasure(widthMeasureSpec, heightMeasureSpec);

	    screenWidth = MeasureSpec.getSize(widthMeasureSpec);
	    screenHeight = MeasureSpec.getSize(heightMeasureSpec);
	    
	    Log.d("ViewBall::onMeasure", Integer.toString(screenWidth)+ " - "+Integer.toString(screenHeight));
	    
	    this.setMeasuredDimension(screenWidth, screenHeight);
		}
	 
	public void move () {
		float a = 9f;
		
		x += vx;
		y += vy*dt;
		vy += a*dt;
		
		if (x + r >= screenWidth || x - r <= 0) {
			vx = -vx;
			x += 2*vx;
			}
		if (y + r >= screenHeight || y - r <= 0) {
			vy = -vy;
			vy += a*dt;
//			y += 2*vy;
			}
		}
	
	public void collide (ViewBall b) {
		int l1 = (int) ( (Math.pow(b.getX() - x, 2) + Math.pow(b.getY() - y, 2)) );
		int l2 = (int) Math.pow(b.getR() + r, 2);
		
		if (l1 < l2) {
			float vxt = b.getVx();
			b.setVx(vx);
			vx = vxt;
			
			float vyt = b.getVy();
			b.setVy(vy);
			vy = vyt;
			}	
		}

	public float getR() { return r; }

	public float getX() { return x; }
	public float getY() { return y; }

	public float getVx() { return vx; }
	public float getVy() { return vy; }

	public void setVx( float ivx ) { vx = ivx; }
	public void setVy( float ivy ) { vy = ivy; }

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		
	}

	public void onSensorChanged(SensorEvent event) {
		// TODO Auto-generated method stub
		
	}

}
