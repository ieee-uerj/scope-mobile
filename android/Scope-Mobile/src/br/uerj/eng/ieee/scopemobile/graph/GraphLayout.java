package br.uerj.eng.ieee.scopemobile.graph;

import android.content.Context;
import br.uerj.eng.ieee.scopemobile.R;
import br.uerj.eng.ieee.scopemobile.utils.Globals;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphView.GraphViewData;
import com.jjoe64.graphview.GraphView.GraphViewSeries;
import com.jjoe64.graphview.LineGraphView;

public class GraphLayout {
	
	private Context mContext;
	private GraphView graphView;
	
	
	public GraphLayout(Context context) {
		mContext = context;
	}
	
	public GraphView drawGraphSensor() {
		GraphViewData[] data = new GraphViewData[Globals.NUMBER_DATA];  
		for (int i=0; i<Globals.NUMBER_DATA; i++) {  
		   data[i] = new GraphViewData(i*Globals.FACTOR_MULTIPLY, 0);  
		}  
		graphView = new LineGraphView(mContext
		      , mContext.getString(R.string.titleGraph) 
		);  
		graphView.addSeries(new GraphViewSeries(data));  
		graphView.setViewPort(Globals.X_AXYS_MIN, Globals.X_AXYS_MAX);  
		graphView.setScrollable(true); 
		graphView.setScalable(true);  
		return graphView;
	}

	public GraphView refreshGraph(double[] values){
		GraphViewData[] data = new GraphViewData[Globals.NUMBER_DATA];  
		for (int i = 0; i < Globals.NUMBER_DATA; i++) {  
			data[i] = new GraphViewData((i*Globals.FACTOR_MULTIPLY), values[i]);  
			
		}  
		graphView = new LineGraphView(mContext
				, mContext.getString(R.string.titleGraph) 
				);  
		graphView.addSeries(new GraphViewSeries(data));  
		graphView.setViewPort(Globals.X_AXYS_MIN, Globals.X_AXYS_MAX);  
		graphView.setScrollable(true); 
		graphView.setScalable(true);  
		return graphView;	
	}
}
