package com.frankbardelli.ThreeAxis;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.util.List;

import javax.swing.JComponent;

public class Canvas extends JComponent {
	ThreeAxisControl tac;
	public Canvas(ThreeAxisControl tac){
		this.tac = tac;
	}
	
	public void paintComponent(Graphics g){
		g.setColor(Color.MAGENTA);
		List<Point> line = tac.getLine();
		Point lastPoint = line.get(0);
		for(int i = 1; i < line.size(); i++){
			Point p = line.get(i);
			g.drawOval((int)p.getX()-1, (int)p.getY()-1, 2, 2);
			g.drawLine(
					(int)lastPoint.getX(), (int)lastPoint.getY(),
					(int)p.getX(), (int)p.getY()
			);
			lastPoint = p;
		}
		g.setColor(Color.BLUE);
		g.fillOval(tac.getX()-5, tac.getY()-5, 10, 10);
	}
}
