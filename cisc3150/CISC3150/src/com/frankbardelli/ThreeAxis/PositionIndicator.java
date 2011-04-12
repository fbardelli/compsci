package com.frankbardelli.ThreeAxis;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class PositionIndicator extends JPanel {
	private JLabel xPos, yPos, zPos;
	public PositionIndicator(int x, int y, int z){
		this.setSize(150, 300);
		setLayout(new GridLayout(3,2));
		add(new JLabel("x:"));
		xPos = new JLabel(Integer.toString(x));
		add(xPos);
		add(new JLabel("y:"));
		yPos = new JLabel(Integer.toString(y));
		add(yPos);
		add(new JLabel("z:"));
		zPos = new JLabel(Integer.toString(z));
		add(zPos);
	}
	
	public void updatePosition(int x, int y, int z){
		xPos.setText(Integer.toString(x));
		yPos.setText(Integer.toString(y));
		zPos.setText(Integer.toString(z));
	}
}
