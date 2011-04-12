package org.qosys.android.balls;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import org.qosys.android.balls.R;

import android.app.Activity;
import android.graphics.Canvas;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.view.View;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

// implements Callback, OnTouchListener

public class BallsActitivity extends Activity implements Callback {
    private static final int FRAMES_PER_SECOND = 25;
    private static final int MS_TO_WAIT = 1000 / FRAMES_PER_SECOND;
    
    private FrameLayout main;
    private MainLoop mainLoop;
    private List<IMovable> movable_objects;
	private SurfaceHolder holder;
	private SurfaceView surface;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
/*        LinearLayout l = (LinearLayout) findViewById(R.layout.main);
        mDrawableAreaView = new DrawableAreaView(this);
        l.addView(mDrawableAreaView);*/
        
        setContentView(R.layout.main);

        
        main = (FrameLayout) findViewById(R.id.main);
        movable_objects = new ArrayList<IMovable>();
        
        addView(new DrawableAreaView(this));
        addView(new ViewBall(this,50,50,5));
                
        main.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent e) {
            	if (e.getAction() == MotionEvent.ACTION_UP)
            		{	
					float x = e.getX();
					float y = e.getY();
					
					addView(new ViewBall(getParent(), x,y,5));
					
					//TimeUnit.MILLISECONDS.sleep(MS_TO_WAIT);
					
					return true;
            		}
            	return true;
            	}
        	});
		surface = (SurfaceView) findViewById(R.id.main_surface);
		holder = surface.getHolder();
		surface.getHolder().addCallback(this);
		   
/*		backgroundPaint = new Paint();
		backgroundPaint.setColor(Color.BLUE);
		
		bubblePaint = new Paint();
		bubblePaint.setColor(Color.WHITE);
		bubblePaint.setAntiAlias(true);
		
		surface.setOnTouchListener(this);*/        
    	}
    
    public void addView (View view) {	
    	main.addView (view);
    	
    	try {
    		IMovable b = (IMovable) view;
    		
    		movable_objects.add(b);
    	}
    	catch (ClassCastException exc) {
    		Log.d("exception", "ClassCastException");
    	}
    }
    
    private class MainLoop extends Thread {
    	private volatile boolean running = true;

    	public void run() {
        	while (running) {
	        	try {
		        	// TODO don't like this hardcoding
		        	TimeUnit.MILLISECONDS.sleep(MS_TO_WAIT);
		
//		        	draw();
		        	runOnUiThread(new Runnable() {
			    	     public void run() {
			    	    	 draw();
			    	    }
			    	});
		
		        	} 
	        	catch (InterruptedException ie) {
		        	running = false;
	        		}		        
	        	}
        	}

    	public void safeStop() {
        	running = false;
        	interrupt();
        	}
    	}

    private void draw() {
	    Canvas c = null;
	    try {
		    c = holder.lockCanvas();
		
		    if (c != null) {
			    doDraw(c);
			    }
	    	} 
	    finally {
		    if (c != null) {
			    holder.unlockCanvasAndPost(c);
		    	}
	    	}
	    }

    private void doDraw(Canvas c) {
	    for (IMovable obj : movable_objects) {
		    obj.move();
		    }
	    int count = main.getChildCount();
	    
	    for (int i = 0; i < count; i++) {
	    	ViewBall b1;
	    	try {
	    		b1 = (ViewBall) main.getChildAt(i);
	    		}
	    	catch (Exception e) { continue; }
	    	
		    for (int j = i+1; j < count; j++) {
		    	ViewBall b2;
		    	
		    	try {
		    		b2 = (ViewBall) main.getChildAt(j);
		    		}
		    	catch (Exception e) { continue; }
		    	
		    	b1.collide(b2);
		    	}
	    	}

	    for (int i = 0; i < count; i++) {
	    	main.getChildAt(i).invalidate();
	    	}
    	}
    
    public void surfaceChanged (SurfaceHolder holder, int format, int width, int height) {
//		model.setSize(width, height);
		}

	public void surfaceCreated(SurfaceHolder holder) {
		mainLoop = new MainLoop();
		mainLoop.start();
		}
	
	public void surfaceDestroyed(SurfaceHolder holder) {
		try {
			//model.setSize(0,0);
			mainLoop.safeStop();
			} 
		finally {
			mainLoop = null;
			}
		}
}



