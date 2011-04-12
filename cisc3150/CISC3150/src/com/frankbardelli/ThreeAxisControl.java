/*
 * Frank Bardelli
 * ThreeAxisControl
 * Renders a canvas with a movable point
 * March 20, 2011
 * CISC 3150  
 */

package com.frankbardelli;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.border.LineBorder;


public class ThreeAxisControl extends JFrame{
	private int x, y, z;
	private ThreeAxisCanvas canvas;
	private PositionIndicator pIndicator;
	private boolean leftPressed, rightPressed, upPressed, downPressed;
	private List<Point> line;

	public static void main(String[] args){
		ThreeAxisControl tac = new ThreeAxisControl();
	}
	
	public ThreeAxisControl(){
		this.setSize(600, 400);
		leftPressed = rightPressed = upPressed = downPressed = false;
		
		//Create 2d plane that allows movement along x and y axis
		canvas = new ThreeAxisCanvas(this);
		canvas.setBackground(Color.BLACK);
		canvas.setBorder(new LineBorder(Color.BLACK, 1));
		
		x = 100;
		y = 100;
		z = 0;

		line = new ArrayList<Point>();
		Point startPoint = new Point(x,y);
		line.add(startPoint);
		
		this.setLayout(new BorderLayout());
		JPanel controls = new JPanel();
		controls.add(new JLabel("Use arrow keys to move the point"));
		this.add(controls,BorderLayout.SOUTH);
		this.add(canvas,BorderLayout.CENTER);
		
		pIndicator = new PositionIndicator(x,y,z);
		this.add(pIndicator,BorderLayout.EAST);
		new Timer(100, new updateScreenAction(this)).start();
		//Handle Keyboard input
		this.setFocusable(true);
		this.addKeyListener(new motionKeyListener(this));
		this.requestFocus();	
		this.setVisible(true);
	}
	
	public void moveRight(){
		this.x += 5;
	}
	
	public void moveLeft(){
		this.x -= 5;
	}

	public void moveUp(){
		this.y -= 5;
	}
	
	public void moveDown(){
		this.y += 5;
	}
	
	public void updatePosition(){
		int lastX = x, lastY = y;
		if(upPressed)
			moveUp();
		if(leftPressed)
			moveLeft();
		if(rightPressed)
			moveRight();
		if(downPressed)
			moveDown();
		
		if(lastX != x || lastY != y){
			Point point = new Point(x,y);
			pIndicator.updatePosition(x, y, z);
			line.add(point);
			cleanupIndices(line);
			this.repaint();
		}
		this.requestFocus();
	}
	
	private void cleanupIndices(List<Point> line){
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
	
	
	public class updateScreenAction implements ActionListener {
		ThreeAxisControl tac;
		public updateScreenAction(ThreeAxisControl tac){
			this.tac = tac;
		}
	    public void actionPerformed(ActionEvent e) {
	    	tac.updatePosition();
	    }
	}
	
	public class motionKeyListener implements KeyListener{
		ThreeAxisControl tac;
		public motionKeyListener(ThreeAxisControl tac){
			this.tac = tac;
		}
		
		public void keyPressed(KeyEvent e) {
			//System.out.println("key pressed "+e.getKeyCode());
			int key = e.getKeyCode();
			if( key == KeyEvent.VK_LEFT )
				leftPressed = true;
			if( key == KeyEvent.VK_RIGHT )
				rightPressed = true;
			if( key == KeyEvent.VK_DOWN )
				downPressed = true;
			if( key == KeyEvent.VK_UP )
				upPressed = true;
		}

		@Override
		public void keyReleased(KeyEvent e) {
			int key = e.getKeyCode();
			if( key == KeyEvent.VK_LEFT )
				leftPressed = false;
			if( key == KeyEvent.VK_RIGHT )
				rightPressed = false;
			if( key == KeyEvent.VK_DOWN )
				downPressed = false;
			if( key == KeyEvent.VK_UP )
				upPressed = false;
		}

		public void keyTyped(KeyEvent e) {
		}
		
	}
	
	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getZ() {
		return z;
	}

	public void setZ(int z) {
		this.z = z;
	}

	private class PositionIndicator extends JPanel {
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

	private class ThreeAxisCanvas extends JComponent{
		ThreeAxisControl tac;
		public ThreeAxisCanvas(ThreeAxisControl tac){
			this.tac = tac;
		}
		
		public void paintComponent(Graphics g){
			g.setColor(Color.MAGENTA);
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
}