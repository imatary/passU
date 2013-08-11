package org.ssm232elite.passu.android;

import org.ssm232elite.passu.android.mouse.PassUService;

import android.app.Application;
import android.content.Context;
import android.os.Build;
import android.view.Display;
import android.view.WindowManager;

import com.googlecode.androidannotations.annotations.EApplication;

/***
 * Role : Manage Service as Singleton
 * @author Jake Yoon
 */

@EApplication
public class AR extends Application {
	private static 		AR					m_Instance;
	public				PassUService		m_CurService = null;
	
	public static int width;
	public static int height;
	public static String phone_lcd_size;
	public static String phone_model;
	public static String phone_os_vrsn;
	
	public AR() {
		super();
		m_Instance = this;
	}
	
	@Override
	public void onCreate()
	{
		super.onCreate();		
		Display dp = ((WindowManager) getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
		width = dp.getWidth();
		height = dp.getHeight();
		phone_lcd_size = AR.width + "*" + AR.height;
		phone_model = Build.MODEL;
		phone_os_vrsn = Build.VERSION.RELEASE;
	}
	
	// Double-checked singleton fetching
	public static AR getInstance() {
		if(m_Instance == null) {
			synchronized(AR.class) {
				if(m_Instance == null) new AR();
			}
		}
		return m_Instance;
	}	
}

