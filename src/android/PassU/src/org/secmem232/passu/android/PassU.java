package org.secmem232.passu.android;

import org.secmem232.passu.android.intent.PassUIntent;
import org.secmem232.passu.android.mouse.PassUService;
import org.secmem232.passu.android.setting.PassUSetting;
import org.secmem232.passu.android.util.Util;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class PassU extends Activity {
	private final String LOG = "PassU";
	private Button btn_connect;
	private EditText edit_ip;
	private Button btn_setting;
	
	private IPassU mPassUSvc;
	private ServiceConnection conn = new ServiceConnection() {
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			if(D.D) Log.w(LOG, "onServiceConnected");
			mPassUSvc = IPassU.Stub.asInterface(service);
			try {
				// Remote connected requested?
				String ipport = edit_ip.getText().toString();
				String ip = ipport.split(":")[0];
				int port = Integer.parseInt(ipport.split(":")[1]);
				
				// Connect to server when client is not connected to server
				if(!mPassUSvc.isConnected()){
					if(D.D) Log.i(LOG, "Remote-connect requested to " + ip + ":" + port);
					onConnectRequested(ip, port);
				} else {
					if(D.D) Log.e(LOG, "Client already connected to server!");
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
	
	/***
	 * ���񽺷� ���� ���� ��ε�ĳ��Ʈ ������ �޾Ƽ� ó���ϴ� ���ù�
	 */
	private BroadcastReceiver serviceConnReceiver = new BroadcastReceiver(){
		@Override
		public void onReceive(Context context, Intent intent) {
			if(D.D) Log.w("BroadcastReceiver", "onReceive");
			String action = intent.getAction();
			if(PassUIntent.ACTION_CONNECTED.equals(action)){
				printOutput("Welcome to PassU");
				HideBackground();
				AR.getInstance().m_Service.onViewInit();
				AR.getInstance().m_Service.ShowCursor();
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

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		if(D.D) Log.w(LOG, "onCreate");
		super.onCreate(savedInstanceState);
		setContentView(R.layout.layout_main);
		
		btn_connect = (Button)findViewById(R.id.btn_connect);
		edit_ip = (EditText)findViewById(R.id.edit_ip);
		btn_setting = (Button)findViewById(R.id.btn_setting);
		
		edit_ip.setText("211.189.20.139:3737");
		btn_connect.setOnClickListener( new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				String ipport = edit_ip.getText().toString();
				String ip = ipport.split(":")[0];
				int port = Integer.parseInt(ipport.split(":")[1]);
				tryConnect(ip, port);
			}
		});
		
		btn_setting.setOnClickListener( new OnClickListener() {
			@Override
			public void onClick(View v) {
				startActivity(new Intent(PassU.this, PassUSetting.class));
			}
		});
	}

	@Override
	protected void onStop() {
		super.onStop();
	}
	@Override
	protected void onResume() {
		if(D.D) Log.w(LOG, "onResume");
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
		if(D.D) Log.w(LOG, "onPause");
		super.onPause();
		unregisterReceiver(serviceConnReceiver);
	}

	public void onConnectRequested(String ip, int port) {
		if(D.D) Log.w(LOG, "onConnectRequested");
		try {
			mPassUSvc.connect(ip, port);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void onBackPressed() {
		if(D.D) Log.w(LOG, "onBackPressed");
		android.os.Process.killProcess(android.os.Process.myPid());
		super.onBackPressed();
	}
	
	private void tryConnect(final String ip, final int port) {
		if(D.D) Log.w(LOG, "tryConnect");
		/*StrictMode.enableDefaults();
		Socket socket = new Socket();
		try {
			InetAddress ia = InetAddress.getByName(ip);
			InetSocketAddress remoteAddr = new InetSocketAddress(ia, port);
			final int connectionTimeout = 1000;	// 1 seconds
			socket.connect(remoteAddr, connectionTimeout);
			if(socket.isConnected())
			{
				if(!socket.isClosed()) 
					socket.close();
				*/
				if(!Util.Services.isServiceAliveU(getApplicationContext())){
					Util.Services.startPassUService(PassU.this, ip, port);
				}
				bindService(new Intent(this, PassUService.class), conn, Context.BIND_AUTO_CREATE);
	/*		} else {
				printOutput("Connection failed");
			}
		} catch (IOException e) {
			e.printStackTrace();
			printOutput("Connection failed");
		} catch (Exception e) {
			e.printStackTrace();
			printOutput("Unknown error");
		} finally {
			try {
				if(!socket.isClosed()) 
					socket.close();
			} catch (Exception e) {};
		}*/
	}

	private void printOutput(final String update) {
		if(D.D) Log.w(LOG, "printOutput");
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(PassU.this, update, Toast.LENGTH_SHORT).show();
			}
		});
	}

	public void HideBackground() {
		if(D.D) Log.w(LOG, "HideBackground");
		Intent home = new Intent(Intent.ACTION_MAIN); 
		home.addCategory(Intent.CATEGORY_HOME);
		home.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(home);
	}
}
