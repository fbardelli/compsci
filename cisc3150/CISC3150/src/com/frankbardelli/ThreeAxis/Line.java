package com.frankbardelli.ThreeAxis;

import java.awt.Point;
import java.util.ArrayList;
import java.util.List;

public class Line {
	private List<Point> line;
	public Line(int x, int y){
		line = new ArrayList<Point>();
		Point startPoint = new Point(x,y);
		line.add(startPoint);
	}
	public Point get(int index){
		return line.get(index);
	}
	public void add(Point p){
		line.add(p);
		cleanupIndices();
	}

	private void cleanupIndices(){
		if(line.size()>=3){
			Point previousPivot = line.get(line.size()-3);
			Point middlePoint	= line.get(line.size()-2);
			Point currentPoint	= line.get(line.size()-1);
			double slope1, slope2;
			slope1 = (previousPivot.getY()-middlePoint.getY()) / (previousPivot.getX()-middlePoint.getX());
			slope2 = (previousPivot.getY()-currentPoint.getY()) / (previousPivot.getX()-currentPoint.getX());
			if(slope1 == slope2){
				line.remove(line.size()-2);
			}
		}		
	}
	
	public int size(){
		return line.size();
	}
}
