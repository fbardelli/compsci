/*
 * Frank Bardelli
 * ThreeAxisControl
 * Renders a canvas with a movable point
 * April 12, 2011
 * CISC 3150  
 */

package com.frankbardelli.ThreeAxis;

import java.awt.BorderLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;

public class ThreeAxisControl extends JFrame{
	private Canvas canvas;
	private Cursor cursor;
	private PositionIndicator pIndicator;
	private boolean leftPressed, rightPressed, upPressed, 
					downPressed, pageUpPressed, pageDownPressed;
	private Line line;

	public static void main(String[] args){
		ThreeAxisControl tac = new ThreeAxisControl();
	}
	
	public ThreeAxisControl(){
		leftPressed = rightPressed = upPressed = downPressed = pageUpPressed = pageDownPressed = false;
		//Create cursor that draws lines on a 2d plane
		cursor = new Cursor(100,100,0);
		//Create 2d plane that allows movement along x and y axis
		canvas = new Canvas(this,cursor);
		//Create a line that tracks the movement of the cursor 
		line = new Line(cursor.getX(),cursor.getY());
	    //PositionIndicator records the x,y,z positions of the cursor
		pIndicator = new PositionIndicator(cursor);
		
		this.setSize(600, 400);
		this.setLayout(new BorderLayout());
		JPanel controls = new JPanel();
		controls.add(new JLabel("Use arrow keys, pageUp and pageDown to move the point"));
		this.add(controls,BorderLayout.SOUTH);
		this.add(canvas,BorderLayout.CENTER);
		this.add(pIndicator,BorderLayout.EAST);

		//update the screen at regular intervals
		new Timer(100, new updateScreenAction(this)).start();
		//Handle Keyboard input
		this.setFocusable(true);
		this.addKeyListener(new motionKeyListener(this));
		this.requestFocus();	
		this.setVisible(true);
	}
	
	public void updatePosition(){
		int lastX = cursor.getX(), 
			lastY = cursor.getY(), 
			lastZ = cursor.getZ();
		if(upPressed)
		    cursor.moveUp();
		if(leftPressed)
			cursor.moveLeft();
		if(rightPressed)
			cursor.moveRight();
		if(downPressed)
			cursor.moveDown();
		if(pageUpPressed)
			cursor.moveOut();
		if(pageDownPressed)
			cursor.moveIn();
		
		if(lastX != cursor.getX() || lastY != cursor.getY() || lastZ != cursor.getZ()){
			pIndicator.updatePosition();
			line.add(new Point(cursor.getX(),cursor.getY()));
			this.repaint();
		}
		this.requestFocus();
	}
	
	public Line getLine() {
		return line;
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
			int key = e.getKeyCode();
			if( key == KeyEvent.VK_LEFT )
				leftPressed = true;
			if( key == KeyEvent.VK_RIGHT )
				rightPressed = true;
			if( key == KeyEvent.VK_DOWN )
				downPressed = true;
			if( key == KeyEvent.VK_UP )
				upPressed = true;
			if( key == KeyEvent.VK_PAGE_UP)
				pageUpPressed = true;
			if( key == KeyEvent.VK_PAGE_DOWN)
				pageDownPressed = true;
		}

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
			if( key == KeyEvent.VK_PAGE_UP)
				pageUpPressed = false;
			if( key == KeyEvent.VK_PAGE_DOWN)
				pageDownPressed = false;
		}

		public void keyTyped(KeyEvent e) {}
		
	}
	
}