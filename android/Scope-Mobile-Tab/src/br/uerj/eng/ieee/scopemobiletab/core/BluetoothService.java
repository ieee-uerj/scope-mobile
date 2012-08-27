package br.uerj.eng.ieee.scopemobiletab.core;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.os.Handler;
import android.util.Log;
import br.uerj.eng.ieee.scopemobiletab.utils.Globals;

public class BluetoothService {
	
	private BluetoothAdapter mAdapter;
	private AcceptThread mAcceptThread;
	private ConnectThread mConnectThread;
	private ConnectedThread mConnectedThread;	
	private int mState;
	private Handler mHandler;

	public BluetoothService(Context context, Handler handler) {
		mAdapter = BluetoothAdapter.getDefaultAdapter();
		mHandler = handler;
		mState = Globals.STATE_NONE;
		
	}

	public synchronized void start() {
		Log.d(Globals.TAG, "start");

		if (mConnectThread != null) {
			mConnectThread.cancel();
			mConnectThread = null;
		}
		if (mConnectedThread != null) {
			mConnectedThread.cancel(); 
			mConnectedThread = null;
		}
		if (mAcceptThread == null) {
			mAcceptThread = new AcceptThread();
			mAcceptThread.start();
		}
	}


	public synchronized void connect(BluetoothDevice device) {
		Log.d(Globals.TAG, "connect to: " + device);

		// Cancel any thread attempting to make a connection
		if (mState == Globals.STATE_CONNECTING) {
			if (mConnectThread != null) {
				mConnectThread.cancel(); 
				mConnectThread = null;
			}
		}

		// Cancel any thread currently running a connection
		if (mConnectedThread != null) {
			mConnectedThread.cancel(); 
			mConnectedThread = null;
		}

		// Start the thread to connect with the given device
		mConnectThread = new ConnectThread(device);
		mConnectThread.start();
		setState(Globals.STATE_CONNECTING);
	}


	public synchronized void connected(BluetoothSocket socket, BluetoothDevice device) {
		Log.d(Globals.TAG, "connected");

		// Cancel the thread that completed the connection
		if (mConnectThread != null) {
			mConnectThread.cancel(); 
			mConnectThread = null;
		}

		// Cancel any thread currently running a connection
		if (mConnectedThread != null) {
			mConnectedThread.cancel();
			mConnectedThread = null;
		}

		// Cancel the accept thread because we only want to connect to one device
		if (mAcceptThread != null) {
			mAcceptThread.cancel(); 
			mAcceptThread = null;
		}

		// Start the thread to manage the connection and perform transmissions
		mConnectedThread = new ConnectedThread(socket);
		mConnectedThread.start();

		setState(Globals.STATE_CONNECTED);
	}

	/**
	 * Stop all threads
	 */
	public synchronized void stop() {
		Log.d(Globals.TAG, "stop");
		if (mConnectThread != null) {
			mConnectThread.cancel(); 
			mConnectThread = null;
		}
		if (mConnectedThread != null) {
			mConnectedThread.cancel();
			mConnectedThread = null;
		}
		if (mAcceptThread != null) {
			mAcceptThread.cancel(); 
			mAcceptThread = null;
		}
		setState(Globals.STATE_NONE);
	}

	private synchronized void setState(int state) {
		Log.d(Globals.TAG, "setState() " + mState + " -> " + state);
		mState = state;
        mHandler.obtainMessage(Globals.MESSAGE_STATE_CHANGE, state, -1).sendToTarget();
	}
	
    public synchronized int getState() {
        return mState;
    }

	private void connectionLost() {
		setState(Globals.STATE_LISTEN);
	}
	
   private void connectionFailed() {
       setState(Globals.STATE_LISTEN);
   }

   public void write(byte[] out) {
       // Create temporary object
       ConnectedThread r;
       // Synchronize a copy of the ConnectedThread
       synchronized (this) {
           if (mState != Globals.STATE_CONNECTED) return;
           r = mConnectedThread;
       }
       // Perform the write unsynchronized
       r.write(out);
   }
	
	private class AcceptThread extends Thread {
		// The local server socket
		private final BluetoothServerSocket mmServerSocket;

		public AcceptThread() {
			BluetoothServerSocket tmp = null;

			// Create a new listening server socket
			try {
				tmp = mAdapter.listenUsingRfcommWithServiceRecord(Globals.NAME, Globals.MY_UUID);
			} catch (IOException e) {
				Log.e(Globals.TAG, "listen() failed", e);
			}
			mmServerSocket = tmp;
		}

		public void run() {
			Log.d(Globals.TAG, "BEGIN mAcceptThread" + this);
			setName("AcceptThread");
			BluetoothSocket socket = null;

			// Listen to the server socket if we're not connected
			while (mState != Globals.STATE_CONNECTED) {
				try {
					// This is a blocking call and will only return on a
					// successful connection or an exception
					socket = mmServerSocket.accept();
				} catch (IOException e) {
					Log.e(Globals.TAG, "accept() failed", e);
					break;
				}

				// If a connection was accepted
				if (socket != null) {
					synchronized (BluetoothService.this) {
						switch (mState) {
						case Globals.STATE_LISTEN:
						case Globals.STATE_CONNECTING:
							// Situation normal. Start the connected thread.
							connected(socket, socket.getRemoteDevice());
							break;
						case Globals.STATE_NONE:
						case Globals.STATE_CONNECTED:
							// Either not ready or already connected. Terminate new socket.
							try {
								socket.close();
							} catch (IOException e) {
								Log.e(Globals.TAG, "Could not close unwanted socket", e);
							}
							break;
						}
					}
				}
			}
			Log.i(Globals.TAG, "END mAcceptThread");
		}

		public void cancel() {
			Log.d(Globals.TAG, "cancel " + this);
			try {
				mmServerSocket.close();
			} catch (IOException e) {
				Log.e(Globals.TAG, "close() of server failed", e);
			}
		}
	}

	
	 private class ConnectThread extends Thread {
	        private final BluetoothSocket mmSocket;
	        private final BluetoothDevice mmDevice;

	        public ConnectThread(BluetoothDevice device) {
	            mmDevice = device;
	            BluetoothSocket tmp = null;

	            // Get a BluetoothSocket for a connection with the
	            // given BluetoothDevice
	            try {
	                tmp = device.createRfcommSocketToServiceRecord(Globals.MY_UUID);
	            } catch (IOException e) {
	                Log.e(Globals.TAG, "create() failed", e);
	            }
	            mmSocket = tmp;
	        }

	        public void run() {
	            Log.i(Globals.TAG, "BEGIN mConnectThread");
	            setName("ConnectThread");

	            // Always cancel discovery because it will slow down a connection
	            mAdapter.cancelDiscovery();

	            // Make a connection to the BluetoothSocket
	            try {
	                // This is a blocking call and will only return on a
	                // successful connection or an exception
	                mmSocket.connect();
	            } catch (IOException e) {
	                connectionFailed();
	                // Close the socket
	                try {
	                    mmSocket.close();
	                } catch (IOException e2) {
	                    Log.e(Globals.TAG, "unable to close() socket during connection failure", e2);
	                }
	                // Start the service over to restart listening mode
	                BluetoothService.this.start();
	                return;
	            }

	            // Reset the ConnectThread because we're done
	            synchronized (BluetoothService.this) {
	                mConnectThread = null;
	            }

	            // Start the connected thread
	            connected(mmSocket, mmDevice);
	        }

	        public void cancel() {
	            try {
	                mmSocket.close();
	            } catch (IOException e) {
	                Log.e(Globals.TAG, "close() of connect socket failed", e);
	            }
	        }
	    }

	 //connected thread class
	 private class ConnectedThread extends Thread {
		private final BluetoothSocket mmSocket;
		private final InputStream mmInStream;
		private final OutputStream mmOutStream;
		private String aux = "";
		int counter = 0;
		final int SIZE = 100;
		double[] display = new double[SIZE];
		
		public ConnectedThread(BluetoothSocket socket) {
			Log.d(Globals.TAG, "create ConnectedThread");
			mmSocket = socket;
			InputStream tmpIn = null;
			OutputStream tmpOut = null;
			
			// Get the BluetoothSocket input and output streams
			try {
				tmpIn = socket.getInputStream();
				tmpOut = socket.getOutputStream();
			} catch (IOException e) {
				Log.e(Globals.TAG, "temp sockets not created", e);
			}

			mmInStream = tmpIn;
			mmOutStream = tmpOut;
		}

		public void run() {
			Log.i(Globals.TAG, "BEGIN mConnectedThread");
			byte[] buffer = new byte[1024];
			int bytes;

			// Keep listening to the InputStream while connected
			while (true) {
				try {
					// Read from the InputStream
					bytes = mmInStream.read(buffer);
//					mHandler.obtainMessage(Globals.MESSAGE_READ, bytes, -1, buffer).sendToTarget();

	                String readMessage = new String(buffer, 0, bytes);                	                
	                String readMessageAux = new String(readMessage);
	              
	                while (readMessageAux.indexOf('%') != -1)
	                {
	                	String vAux = aux + readMessageAux.substring(0, readMessageAux.indexOf('%'));
	                	Log.i(Globals.TAG, "readMessage: "+ vAux); //vector
	                	if(vAux.compareTo("A") == 0)
	                		counter = 0;
	                	else
	                		display[counter++] = Double.parseDouble(vAux);
	                	
	                	Log.i(Globals.TAG,"LOG: "+ counter);
	                	aux = "";
	                	if(readMessageAux.lastIndexOf('%') < readMessageAux.length() - 1)
	                		readMessageAux = readMessageAux.substring(readMessageAux.indexOf('%') + 1);
	                	else
	                		readMessageAux = "";
	                }
	                
	                if(readMessageAux.indexOf('%') == -1 && readMessageAux.length() > 0)
	                {
	                    aux +=  readMessageAux;
	                }
	                
	                if (counter >= SIZE)
	                {
	                	counter = 0;
	                	mHandler.obtainMessage(Globals.MESSAGE_READ, bytes, -1,display).sendToTarget();
	                	display = new double[SIZE];
	                }
				} catch (IOException e) {
					Log.e(Globals.TAG, "disconnected", e);
					connectionLost();
					break;
				}
			}
		}	

		/**
		 * Write to the connected OutStream.
		 * @param buffer  The bytes to write
		 */
		public void write(byte[] buffer) {
			try {
				mmOutStream.write(buffer);
			} catch (IOException e) {
				Log.e(Globals.TAG, "Exception during write", e);
			}
		}

		public void cancel() {
			try {
				mmSocket.close();
			} catch (IOException e) {
				Log.e(Globals.TAG, "close() of connect socket failed", e);
			}
		}
	}
}

