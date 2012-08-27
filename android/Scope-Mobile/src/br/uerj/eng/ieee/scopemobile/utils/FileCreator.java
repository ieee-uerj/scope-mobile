package br.uerj.eng.ieee.scopemobile.utils;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;

import android.os.Environment;

public class FileCreator {
	
	private String fileName;
	private double[] intValues;
	
	public FileCreator(String filename) {
		this.fileName = filename;
		constructFileName(filename);
		File dir = new File(Environment.getExternalStorageDirectory().getPath()+"/Scope-Mobile/");
		if(!dir.exists()) {
			if(!dir.mkdirs()) {
				dir.mkdir();
			}
		}
	}
	
	private void constructFileName(String filename){
		fileName = Environment.getExternalStorageDirectory()+"/Scope-Mobile/"+filename;
	}
	
	public String getFileName(){
		return fileName;
	}
		
	public void createNewFile(){
		File file = new File(fileName);	
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(file));		
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void clearFile()
	{
		File file = new File(fileName);
		file.delete();
		createNewFile();
	}
	
	public void AddNewLine(String str){
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(fileName,true));		
			out.write(str);
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void fileToArray(){
		try {
			BufferedReader bufferedReader;
			bufferedReader = new BufferedReader(new FileReader(fileName));
			List<String> lines = new ArrayList<String>();
			String line = null;
			while ((line = bufferedReader.readLine()) != null) {
				lines.add(line);
			}
			bufferedReader.close();
			String[] values =  lines.toArray(new String[lines.size()]);
			intValues = new double[lines.size()];
			for(int i = 0; i<values.length; i++){
				if(values[i].length() == 4)
				{
					
					if(isInteger(values[i]))
					{
						if(Double.parseDouble(values[i]) >= 0 && Double.parseDouble(values[i]) <= 1023)
							intValues[i] = Double.parseDouble(values[i]);
					}
					else
					{
						if (i == 0)
							intValues[0] = 0;
						else
							intValues[i] = intValues[i-1];
					}
				}
				else
				{
					if (i == 0)
						intValues[0] = 0;
					else
						intValues[i] = intValues[i-1];
				}
			}
//			intValues[0] = intValues[1];
//			filterError();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


	private boolean isInteger( String input ) {  
		try {  
			Integer.parseInt( input );  
			return true;  
		}catch( Exception e){  
			return false;  
		}
	} 


	public long getLinesFromFile()
	{
		try {
			LineNumberReader lnr = new LineNumberReader(new FileReader(fileName));
			lnr.skip(Long.MAX_VALUE);
			return lnr.getLineNumber();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return -1;
		} catch (IOException e) {
			e.printStackTrace();
			return -1;
		}
	}
	
	public double[] getAllIntValuesFromFile(){
		return intValues;
	}
	
	public void setZeroAllIntValues(){
		intValues = null;
	}
	
	public double getMaxValueFromFile(){
		double maxValue=0;
		for(int i=0; i<intValues.length;i++){
			if(maxValue<=intValues[i]){
				maxValue=intValues[i];
			}
		}
		return maxValue;
	}
	
	public void arrayToFile(){
		try {
			fileToArray();
			BufferedWriter out = new BufferedWriter(new FileWriter(fileName));
			out.write("Time\tModule\n");
			for(int i=0;i<Globals.NUMBER_DATA;i++){
				out.write(String.format("%.2f", i*Globals.FACTOR_MULTIPLY)+"\t"+intValues[i]+"\n");
			}
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void filterError()
	{
		for(int w = 1; w < intValues.length - 1;w++){
			if (!((intValues[w] < (intValues[w-1]*1.20)) && (intValues[w] > (intValues[w-1]*0.8))))
			{
				intValues[w] = (intValues[w-1] + intValues[w+1])/2;
			}
		}
	}
	
//	private double concatValue(double value) {
	
//	}
	
}
