package br.uerj.eng.ieee.scopemobile.utils;

import java.util.UUID;

public class Globals {
	//Strings
	public final static String TAG = "Scope-Mobile";   

	public static boolean lock = true;
	
	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;

	//Extras
	public static String EXTRA_DEVICE_ADDRESS = "device_address";

	// Intent request codes
	public static final int REQUEST_CONNECT_DEVICE = 1;
	public static final int REQUEST_ENABLE_BT = 2;

	//Bluetooth
	public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
	public static final String NAME = "ScopeTransmition";
	public static final int STATE_NONE = 0;       // we're doing nothing
	public static final int STATE_LISTEN = 1;     // now listening for incoming connections
	public static final int STATE_CONNECTING = 2; // now initiating an outgoing connection
	public static final int STATE_CONNECTED = 3;  // now connected to a remote device
	
	//Data
	public static final int NUMBER_DATA = 100;
	public static final float FACTOR_MULTIPLY = 1f;
	public static final float X_AXYS_MIN = 0.000f;
	public static final float X_AXYS_MAX = 100.000f;
	
}
