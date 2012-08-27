package br.uerj.eng.ieee.scopemobile.utils;

import java.util.ArrayList;

public class SignalProcessing {

	private ArrayList<String> points; 

	public SignalProcessing()
	{
		points = new ArrayList<String>();
	}
	
	public void refreshSignalProcessing(SignalProcessing signalProcessing)
	{
		signalProcessing = new SignalProcessing();
	}
	
	public void addPoint(String str)
	{
		StringBuffer sb = new StringBuffer(str);
		for (int i = 0; i < sb.length(); i++)
		{
			if(sb.charAt(i)=='%') 
			{
				points.add(sb.substring(0, i));
				sb.delete(0, i);
			}
		}
		if (sb.length() > 0)
		{
			points.add(sb.toString());
		}
	}
	
	
	public ArrayList<String> getAllPoints ()
	{
		return points;
	}
	
	public String[] getAllSignal ()
	{
		return points.toArray(new String[points.size()]);
	}
}
