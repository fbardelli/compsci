/*
 * Frank Bardelli
 * ThreeAxisControl
 * Canvas control
 * April 12, 2011
 * CISC 3150  
 */

package com.frankbardelli.ThreeAxis;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

import javax.swing.JComponent;
import javax.swing.border.LineBorder;

public class Canvas extends JComponent {
	ThreeAxisControl tac;
	Cursor cursor;
	public Canvas(ThreeAxisControl tac, Cursor cursor){
		this.tac = tac;
		this.cursor = cursor;
		setBackground(Color.BLACK);
		setBorder(new LineBorder(Color.BLACK, 1));
	}
	
	public void paintComponent(Graphics g){
		g.setColor(Color.MAGENTA);
		Line line = tac.getLine();
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
		g.fillOval(cursor.getX()-5, cursor.getY()-5, 10, 10);
	}
}
