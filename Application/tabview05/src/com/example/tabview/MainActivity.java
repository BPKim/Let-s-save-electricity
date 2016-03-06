package com.example.tabview;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import android.app.TabActivity;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.MediaController;
import android.widget.TabHost;
import android.widget.ToggleButton;
import android.widget.VideoView;

public class MainActivity extends TabActivity implements OnClickListener {

	TabHost mTabHost;

	private ToggleButton toggle_l;
	private ToggleButton toggle_c;
	private ToggleButton toggle_f;
	Socket sock;
	//
	private Socket socket;
	private BufferedReader networkReader;
	private PrintWriter networkWriter;

	private String hostname = "192.168.0.28";

	//private String hostname = "localhost";

	private int port = 5568;
	protected CompoundButton togglebutton;
	protected CompoundButton onoff;

	ImageView image;
	ImageView image2;

	int a = 0;
	int b = 0;

	int light = 0;
	int com = 0;
	int fan = 0;
	
	boolean flag = true;
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);
		TabHost mTabHost = getTabHost();

		image = (ImageView) findViewById(R.id.homeimage);
		image2 = (ImageView) findViewById(R.id.box3);

		toggle_l = (ToggleButton) findViewById(R.id.toggle1);
		toggle_c = (ToggleButton) findViewById(R.id.toggle2);
		toggle_f = (ToggleButton) findViewById(R.id.toggle3);

		ImageView boximage = (ImageView) findViewById(R.id.box3);

		mTabHost.addTab(mTabHost.newTabSpec("tab1").setContent(R.id.tabs1)
				.setIndicator("HOME"));
		
	     VideoView videoView = (VideoView) findViewById(R.id.VideoView);
	     Uri video = Uri
	             .parse("http://192.168.0.28:11341/cc.mp4");
	     videoView.setVideoURI(video);
	     videoView.start();

		toggle_c.setChecked(false);
		toggle_l.setChecked(false);
		toggle_f.setChecked(false);



		mTabHost.addTab(mTabHost.newTabSpec("tab2").setContent(R.id.tabs2)
				.setIndicator("CONTROL"));

		mTabHost.addTab(mTabHost.newTabSpec("tab3").setContent(R.id.tabs3)
				.setIndicator("TIP"));


		toggle_l.setOnClickListener(this);
		toggle_c.setOnClickListener(this);
		toggle_f.setOnClickListener(this);

		new ConnectThread().start();

	}

	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

	public void onClick(View v) {
		// TODO Auto-generated method stub


		if(v == toggle_l)
		{
			light++;

			if((light % 2) == 0)
			{
				networkWriter.println("1");
				networkWriter.flush();
			}
			else
			{
				networkWriter.println("2");
				networkWriter.flush();
			}
		}

		else if(v == toggle_c)
		{
			com++;

			if((com % 2) == 0)
			{
				networkWriter.println("3");
				networkWriter.flush();
			}
			else
			{
				networkWriter.println("4");
				networkWriter.flush();
			}
		}

		else if(v == toggle_f)
		{
			fan++;

			if((fan % 2) == 0)
			{
				networkWriter.println("5");
				networkWriter.flush();
			}
			else
			{
				networkWriter.println("6");
				networkWriter.flush();
			}
		}
	}


	class ConnectThread extends Thread
	{
		@Override
		public void run() {
			try {

				Log.d("TAG","ConnectThread Start");
				sock = new Socket(hostname, port);
				Log.d("TAG","ConnectThread Connect");
				new ReceiveServerThread().start();
				networkWriter = new PrintWriter(new OutputStreamWriter(sock.getOutputStream()));

			}
			catch(IOException e){
				e.printStackTrace();
			}
		}
	}

	
	Handler mHandler = new Handler()
	{
		
		public void handleMessage(android.os.Message msg)
		{
			int n = (Integer)msg.obj;
			switch(n){
			case 0:
				toggle_l.setChecked(false);
				toggle_c.setChecked(false);
				toggle_f.setChecked(false);
				break;
			case 1:
				toggle_l.setChecked(true);
				toggle_c.setChecked(false);
				toggle_f.setChecked(false);
				break;
			case 2:
				toggle_l.setChecked(false);
				toggle_c.setChecked(true);
				toggle_f.setChecked(false);
				break;
			case 3:
				toggle_l.setChecked(true);
				toggle_c.setChecked(true);
				toggle_f.setChecked(false);
				break;
			case 4:
				toggle_l.setChecked(false);
				toggle_c.setChecked(false);
				toggle_f.setChecked(true);
				break;
			case 5:
				toggle_l.setChecked(true);
				toggle_c.setChecked(false);
				toggle_f.setChecked(true);
				break;
			case 6:
				toggle_l.setChecked(false);
				toggle_c.setChecked(true);
				toggle_f.setChecked(true);
				break;
			case 7:
				toggle_l.setChecked(true);
				toggle_c.setChecked(true);
				toggle_f.setChecked(true);
				break;
			}
			/*
			if(n%2==1)
			{
				Log.d("TAG",n+"!");
				light = 1;
				toggle_l.setChecked(true);
				n = n/2;
				if(n==0)
				{
					return;
				}
			}
			if(n%2==1)
			{
				Log.d("TAG",n+"!!");
				
				com = 1;
				toggle_c.setChecked(true);
				n = n/2;
				if(n==0)
				{
					return;
				}
			}
			if(n%2==1)
			{
				Log.d("TAG",n+"!!!");
				fan = 1;
				toggle_f.setChecked(true);
			}
			
			
			if(n/2==1)
			{
				Log.d("TAG",n+"!!!");
				com = 1;
				toggle_c.setChecked(true);
			}
			
			if(n/2==2)
			{
				Log.d("TAG",n+"!!!");
				fan = 1;
				toggle_f.setChecked(true);
			}
			
			
			if(n/2==3)
			{
				Log.d("TAG",n+"!!!");
				com = 1;
				fan = 1;
				toggle_c.setChecked(true);
				toggle_f.setChecked(true);
			}*/
		};
	};
	
	
	int old_n = 0;
	class ReceiveServerThread extends Thread
	{
		@Override
		public void run() {
			//sock.getInputStream()
			try
			{
				Log.d("TAG","ReceiveThread Start");
				networkReader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
				while(flag)
				{
					
					String receiveMessage = networkReader.readLine();
					int n = Integer.parseInt(receiveMessage);
					if(old_n != n){
						Log.e("TAG", "state change : " + old_n + " > " + n);
						Message mm = new Message();
						mm.obj = n;
						mHandler.sendMessage(mm);
					}
					old_n = n;
				}			
			}
			
			catch(Exception e)
			{
				Log.d("TAG",e.toString());
			}

		}
	}
	
	class CCTVThread extends Thread
	{

	}



	@Override
	public void finish() {
		flag = false;
		super.finish();
	}
	
}
