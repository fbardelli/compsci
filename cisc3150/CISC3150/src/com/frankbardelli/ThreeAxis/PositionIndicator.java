package com.frankbardelli.ThreeAxis;

import java.awt.GridLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class PositionIndicator extends JPanel {
	private JLabel xPos, yPos, zPos;
	Cursor cursor;
	public PositionIndicator(Cursor cursor){
		this.cursor = cursor;
		this.setSize(150, 300);
		setLayout(new GridLayout(3,2));
		add(new JLabel("x:"));
		xPos = new JLabel(Integer.toString((int)cursor.getX()));
		add(xPos);
		add(new JLabel("y:"));
		yPos = new JLabel(Integer.toString((int)cursor.getY()));
		add(yPos);
		add(new JLabel("z:"));
		zPos = new JLabel(Integer.toString((int)cursor.getY()));
		add(zPos);
	}
	
	public void updatePosition(){
		xPos.setText(Integer.toString((int)cursor.getX()));
		yPos.setText(Integer.toString((int)cursor.getY()));
		zPos.setText(Integer.toString((int)cursor.getZ()));
	}
}
