package org.secmem232.passu.android;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;

import org.secmem232.passu.android.intent.PassUIntent;
import org.secmem232.passu.android.mouse.PassUService;
import org.secmem232.passu.android.network.ServerCheckListener;
import org.secmem232.passu.android.setting.PassUSetting;
import org.secmem232.passu.android.util.Util;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.googlecode.androidannotations.annotations.AfterViews;
import com.googlecode.androidannotations.annotations.Background;
import com.googlecode.androidannotations.annotations.Click;
import com.googlecode.androidannotations.annotations.EActivity;
import com.googlecode.androidannotations.annotations.UiThread;
import com.googlecode.androidannotations.annotations.ViewById;

@EActivity(R.layout.layout_main)
public class PassU extends Activity implements ServerCheckListener {
	private final String LOG = "PassU";

	@ViewById(R.id.btn_connect)
	Button btn_connect;

	@ViewById(R.id.edit_ip)
	EditText edit_ip;

	private IPassU mPassUSvc;
	private ServiceConnection conn = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.w(LOG, "onServiceConnected");
			mPassUSvc = IPassU.Stub.asInterface(service);
			try {
				// Remote connected requested?
				String ipport = edit_ip.getText().toString();
				String ip = ipport.split(":")[0];
				int port = Integer.parseInt(ipport.split(":")[1]);
				
				// Connect to server when client is not connected to server
				if(!mPassUSvc.isConnected()){
					Log.i(LOG, "Remote-connect requested to " + ip + ":" + port);
					onConnectRequested(ip, port);
				} else {
					Log.e(LOG, "Client already connected to server!");
				}
			} catch (ArrayIndexOutOfBoundsException e) {
				printOutput("Insert IP:PORT");
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			mPassUSvc = null;
		}
	};

	@AfterViews
	protected void onInitialize() {
		edit_ip.setText("211.189.20.139:3737");
	}

	@Click
	void btn_connect() {
		String ipport = edit_ip.getText().toString();
		String ip = ipport.split(":")[0];
		int port = Integer.parseInt(ipport.split(":")[1]);
		
		tryConnect(ip, port);
	}

	@Click
	void btn_setting() {
		startActivity(new Intent(PassU.this, PassUSetting.class));
	}

	@Override
	protected void onResume() {
		super.onResume();
		IntentFilter filter = new IntentFilter();
		filter.addAction(PassUIntent.ACTION_CONNECTED);
		filter.addAction(PassUIntent.ACTION_DEVICE_OPEN_FAILED);
		filter.addAction(PassUIntent.ACTION_CONNECTION_FAILED);
		filter.addAction(PassUIntent.ACTION_DISCONNECTED);
		filter.addAction(PassUIntent.ACTION_INTERRUPTED);

		registerReceiver(serviceConnReceiver, filter);
	}

	@Override
	protected void onPause(){
		super.onPause();
		unregisterReceiver(serviceConnReceiver);
	}
	
	@Override
	protected void onStop() {
		unbindService(conn);
		super.onStop();
	}

	/***
	 * ���񽺷� ���� ���� ��ε�ĳ��Ʈ ������ �޾Ƽ� ó���ϴ� ���ù�
	 */
	private BroadcastReceiver serviceConnReceiver = new BroadcastReceiver(){
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();

			if(PassUIntent.ACTION_CONNECTED.equals(action)){
				printOutput("Welcome to PassU");
				HideBackground();
			} else if(PassUIntent.ACTION_DEVICE_OPEN_FAILED.equals(action)) {
				printOutput("Device open failed\nis Rooted device?");
			} else if(PassUIntent.ACTION_DISCONNECTED.equals(action)) {
				printOutput("Disconnected");
			} else if(PassUIntent.ACTION_INTERRUPTED.equals(action)) {
				printOutput("Interrupted Server");
			} else if(PassUIntent.ACTION_CONNECTION_FAILED.equals(action)){
				printOutput("Connection Failed");
			}
		}
	};

	public void onConnectRequested(String ip, int port) {
		try {
			mPassUSvc.connect(ip, port);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void onBackPressed() {
		android.os.Process.killProcess(android.os.Process.myPid());
		super.onBackPressed();
	}
	
	// tryConnect to Server
	@Background
	void tryConnect(final String ip, final int port) {
		Socket socket = new Socket();
		try {
			InetAddress ia = InetAddress.getByName(ip);
			InetSocketAddress remoteAddr = new InetSocketAddress(ia, port);
			final int connectionTimeout = 1000;	// 2 seconds
			socket.connect(remoteAddr, connectionTimeout);
			if(socket.isConnected())
			{
				printOutput("Connection Succeed");
				onServerCheckIsOn();
			} else {
				printOutput("Connection failed");
			}
		} catch (IOException e) {
			printOutput("Connection failed");
		} catch (Exception e) {
			printOutput("Unknown error");
		} finally {
			try {
				if(!socket.isClosed()) 
					socket.close();
			} catch (Exception e) {};
		}
	}

	@UiThread
	void printOutput(String update) {
		Toast.makeText(PassU.this, update, Toast.LENGTH_SHORT).show();
	}

	public void HideBackground() {
		Intent home = new Intent(Intent.ACTION_MAIN); 
		home.addCategory(Intent.CATEGORY_HOME);
		home.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(home);
		finish();
	}

	@Override
	public void onServerCheckIsOn() {
		if(!Util.Services.isServiceAliveU(getApplicationContext())){
			Util.Services.startPassUService(getApplicationContext());
		}
		bindService(new Intent(this, PassUService.class), conn, Context.BIND_AUTO_CREATE);
	}
}
