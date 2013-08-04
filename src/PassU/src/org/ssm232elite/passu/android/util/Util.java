package org.ssm232elite.passu.android.util;

import org.ssm232elite.passu.android.AR;

import android.content.Context;
import android.content.pm.PackageManager;

public class Util {
	
	//###################################################################################################
	//���� �ڵ�
	//###################################################################################################
	public static int getVersion(Context context) {
		try {
			PackageManager pm = context.getPackageManager();
			return pm.getPackageInfo(AR.class.getPackage().getName(), 0).versionCode;
		} catch(Exception e) {
			return 1;
		}
	}
		
	//###################################################################################################
	//���� ����
	//###################################################################################################
	public static String getVersionName(Context context) {
		try {
			PackageManager pm = context.getPackageManager();
			return pm.getPackageInfo(AR.class.getPackage().getName(), 0).versionName;
		} catch(Exception e) {
			return "1.0";
		}
	}
}
