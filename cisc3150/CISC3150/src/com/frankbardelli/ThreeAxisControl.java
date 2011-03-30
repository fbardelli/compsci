package com.frankbardelli;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;


public class ThreeAxisControl extends JFrame{
	private int x, y, z;
	private ThreeAxisCanvas canvas;
	private PositionIndicator pIndicator;

	public static void main(String[] args){
		ThreeAxisControl tac = new ThreeAxisControl();
	}
	
	public ThreeAxisControl(){
		this.setSize(550, 400);
		this.x = 0;
		this.y = 0;
		this.z = 0;
		this.canvas = new ThreeAxisCanvas(this);
		this.canvas.setBackground(Color.BLACK);
		this.setLayout(new BorderLayout());
		JPanel controls = new JPanel();
		controls.setLayout(new GridLayout(2,3));
		controls.add(new JPanel());
		
		JButton upButton = new JButton("UP");
		upButton.addActionListener(new upActionListener(this));
		controls.add(upButton);
		
		controls.add(new JPanel());
		
		JButton leftButton = new JButton("LEFT");
		leftButton.addActionListener(new leftActionListener(this));
		controls.add(leftButton);
		
		JButton downButton = new JButton("DOWN");
		downButton.addActionListener(new downActionListener(this));
		controls.add(downButton);
		
		JButton rightButton = new JButton("RIGHT");
		rightButton.addActionListener(new rightActionListener(this));
		controls.add(rightButton);
		
		this.add(controls,BorderLayout.SOUTH);
		this.add(canvas,BorderLayout.CENTER);
		
		pIndicator = new PositionIndicator(x,y,z);
		this.add(pIndicator,BorderLayout.EAST);
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
			switch(e.getKeyCode()){
				case KeyEvent.VK_LEFT:
					tac.moveLeft();
					break;
				case KeyEvent.VK_RIGHT:
					tac.moveRight();
					break;
				case KeyEvent.VK_DOWN:
					tac.moveDown();
					break;
				case KeyEvent.VK_UP:
					tac.moveUp();
					break;
			}
		}

		@Override
		public void keyReleased(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void keyTyped(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}
		
	}
	
	public class upActionListener implements ActionListener {
		ThreeAxisControl tac;
		public upActionListener(ThreeAxisControl tac){ this.tac = tac;}
		public void actionPerformed(ActionEvent e) {
			tac.moveUp();
		}
	}
	public class downActionListener implements ActionListener {
		ThreeAxisControl tac;
		public downActionListener(ThreeAxisControl tac){ this.tac = tac;}
		public void actionPerformed(ActionEvent e) {
			tac.moveDown();
		}
	}	
	public class leftActionListener implements ActionListener {
		ThreeAxisControl tac;
		public leftActionListener(ThreeAxisControl tac){ this.tac = tac;}
		public void actionPerformed(ActionEvent e) {
			tac.moveLeft();
		}
	}
	public class rightActionListener implements ActionListener {
		ThreeAxisControl tac;
		public rightActionListener(ThreeAxisControl tac){ this.tac = tac;}
		public void actionPerformed(ActionEvent e) {
			tac.moveRight();
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
