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
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;


public class ThreeAxisControl extends JFrame{
	private int x, y, z;
	private ThreeAxisCanvas canvas;
	private PositionIndicator pIndicator;

	public static void main(String[] args){
		ThreeAxisControl tac = new ThreeAxisControl();
	}
	
	public ThreeAxisControl(){
		this.setSize(600, 400);
		x = y = z = 0;
		
		//Create 2d plane that allows movement along x and y axis
		canvas = new ThreeAxisCanvas(this);
		canvas.setBackground(Color.BLACK);
		canvas.setBorder(new LineBorder(Color.BLACK, 1));
		
		this.setLayout(new BorderLayout());
		JPanel controls = new JPanel();
		controls.add(new JLabel("Use arrow keys to move the point"));
		this.add(controls,BorderLayout.SOUTH);
		this.add(canvas,BorderLayout.CENTER);
		
		pIndicator = new PositionIndicator(x,y,z);
		this.add(pIndicator,BorderLayout.EAST);
		
		//Handle Keyboard input
		this.setFocusable(true);
		this.addKeyListener(new motionKeyListener(this));
		this.requestFocus();	
		this.setVisible(true);
	}
	
	public void moveRight(){
		this.x += 5;
		updatePosition();
	}
	
	public void moveLeft(){
		this.x -= 5;
		updatePosition();
	}

	public void moveUp(){
		this.y -= 5;
		updatePosition();
	}
	
	public void moveDown(){
		this.y += 5;
		updatePosition();
	}
	
	public void updatePosition(){
		this.repaint();
		this.requestFocus();
		pIndicator.updatePosition(x, y, z);
	}
	
	public class motionKeyListener implements KeyListener{
		ThreeAxisControl tac;
		public motionKeyListener(ThreeAxisControl tac){
			this.tac = tac;
		}
		
		public void keyPressed(KeyEvent e) {
			System.out.println("key pressed "+e.getKeyCode());
			int key = e.getKeyCode();
			
			if( key == KeyEvent.VK_LEFT ){
				tac.moveLeft();
			}
			
			if( key == KeyEvent.VK_RIGHT ){
				tac.moveRight();
			}
			
			if( key == KeyEvent.VK_DOWN ){
				tac.moveDown();
			}
			
			if( key == KeyEvent.VK_UP ){
					tac.moveUp();
			}
		}

		@Override
		public void keyReleased(KeyEvent e) {
		}

		@Override
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
			g.setColor(getBackground());
			g.drawRect(0, 0, this.getWidth(), this.getHeight());
			g.setColor(Color.BLUE);
			System.out.println("x "+tac.getX() + " y "+ tac.getY());
			g.fillOval(tac.getX(), tac.getY(), 10, 10);
		}
	}
}