package br.uerj.eng.ieee.scopemobile;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.PowerManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import br.uerj.eng.ieee.scopemobile.core.BluetoothService;
import br.uerj.eng.ieee.scopemobile.graph.GraphLayout;
import br.uerj.eng.ieee.scopemobile.utils.DeviceListActivity;
import br.uerj.eng.ieee.scopemobile.utils.FileCreator;
import br.uerj.eng.ieee.scopemobile.utils.Globals;

public class Main extends Activity {

	private BluetoothAdapter mBluetoothAdapter;
	private String address;
	private BluetoothService mBluetoothService;

	private TextView txTimeDiv, txScaleFactor;
	private Button btTimeDiv, btScaleFactor;
	private LinearLayout layout;
	private GraphLayout graphLayout;
	
	private FileCreator fileCreator;
	private FileCreator fileCreator2;
	
	private Context mContext;

	PowerManager pm;
	PowerManager.WakeLock wl;
	
	boolean stateConnection = false;
	StringBuffer stringBuffer = new StringBuffer(); 	
	int samplingRateArray[] = {50, 250, 500, 2500, 5000, 25000, 50000};	
	int samplingRate = 0;
	int counterSample = 0;
	
	String aux = "";
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	
		mContext = this;

		setContentView(R.layout.main);

		txTimeDiv = (TextView)findViewById(R.id.txTimeDiv);
		txScaleFactor = (TextView)findViewById(R.id.txScaleFactor);
		
		btTimeDiv = (Button)findViewById(R.id.btTimeDiv);
		btScaleFactor = (Button)findViewById(R.id.btScaleFactor);
		
		pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
		wl = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, Globals.TAG);

		fileCreator = new FileCreator("scope-mobile.txt");
		fileCreator.createNewFile();
		
		//debug file 
		fileCreator2 = new FileCreator("scope-mobile-all.txt");
		fileCreator2.createNewFile();
		
		
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		
		if (mBluetoothAdapter == null) {
			Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
			finish();
			return;
		}
        graphLayout = new GraphLayout(this);
        layout = (LinearLayout)findViewById(R.id.graphView);
    	layout.addView(graphLayout.drawGraphSensor());
    }
    
    
    @Override
    protected void onStart() {
    	super.onStart();
    	configureButtons();
    	if (!mBluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, Globals.REQUEST_ENABLE_BT);
		} else {
			if(mBluetoothService==null){
				mBluetoothService = new BluetoothService(this,handler);
				setupConfigurations();
			}
		}
    }
    
    @Override
  	protected synchronized void onPause() {	
  		super.onPause();
  	}

  	@Override
  	protected void onStop() {
  		super.onStop();
  	}
  	
      @Override
  	protected void onDestroy() {
  		super.onDestroy();
  		if(mBluetoothService!=null) mBluetoothService.stop();
  	}
    
    @Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		switch (requestCode) {
		case Globals.REQUEST_CONNECT_DEVICE:
			if (resultCode == Activity.RESULT_OK) {
				address = data.getExtras().getString(Globals.EXTRA_DEVICE_ADDRESS);
				BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
				mBluetoothService.connect(device);
			}
		case Globals.REQUEST_ENABLE_BT:
			if (resultCode == Activity.RESULT_OK) {
				setupConfigurations();
			} else {
				Log.d(Globals.TAG, "BT not enabled");
				Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
				finish();
			}
			break;
		}
	}
    
    @Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.option_menu, menu);
		return true;
	}
	
    @Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.scan:
			Intent serverIntent = new Intent(this, DeviceListActivity.class);
			startActivityForResult(serverIntent, Globals.REQUEST_CONNECT_DEVICE);
			return true;
		case R.id.discoverable:
			ensureDiscoverable();
			return true;
		case R.id.info:
			dialogInflate();
			return true;
		}
		return false;
	}

    private void dialogInflate() {
    	//TODO: Implementar dialog;
    }

    private void ensureDiscoverable() {
  		Log.d(Globals.TAG, "ensure discoverable");
  		if (mBluetoothAdapter.getScanMode() !=
  				BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE) {
  			Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
  			discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
  			startActivity(discoverableIntent);
  		}
  	}
   
    private final Handler handler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			switch (msg.what) {
			case Globals.MESSAGE_STATE_CHANGE:
                switch (msg.arg1) {
                case Globals.STATE_CONNECTED:
                	stateConnection=true;
                    break;
                case Globals.STATE_CONNECTING:
                	stateConnection=false;
                	break;
                case Globals.STATE_LISTEN:
                case Globals.STATE_NONE:
                	stateConnection=false;
                	break;
                }
                break;
			case Globals.MESSAGE_READ:
				
				double[] readBuf =  (double[]) msg.obj;
				layout.removeAllViews();
            	layout.addView(graphLayout.refreshGraph(readBuf));

            	
                break;
			}
		};
    };


    private void setupConfigurations() {

    	if(mBluetoothService==null)
    		mBluetoothService = new BluetoothService(this,handler);

    }

    private void configureButtons() {
    	btTimeDiv.setOnClickListener(new View.OnClickListener() {
    		
    		@Override
    		public void onClick(View v) {
    			if (mBluetoothService != null)
    			{
    				int timeDiv = getTimeDiv();
    				txTimeDiv.setText("x "+timeDiv);
    				switch (timeDiv) {
    				case 0:
        				mBluetoothService.write("aa".getBytes());
    					break;
    				case 1:
    					mBluetoothService.write("ab".getBytes());
    					break;
    				case 2:
    					mBluetoothService.write("ac".getBytes());
    					break;
    				case 3:
    					mBluetoothService.write("ad".getBytes());
    					break;
    				case 4:
    					mBluetoothService.write("ae".getBytes());
    					break;
    				case 5:
    					mBluetoothService.write("af".getBytes());
    					break;
    				case 6:
    					mBluetoothService.write("ag".getBytes());
    					break;					
    				default:
    					break;
    				}
    			}
    		}
    	});
    	btScaleFactor.setOnClickListener(new View.OnClickListener() {

    		@Override
    		public void onClick(View v) {

    		}
    	});
    }
    
    private int getTimeDiv()
    {
    	if (counterSample < 6)
    		counterSample++;
    	else
    		counterSample = 0;

    	return samplingRateArray[counterSample];
    }
}

