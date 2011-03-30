/**
 * Frank Bardelli
 * CISC 3150
 * Swing Hello World
 * March 15, 2010
 */

package com.frankbardelli.ui;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class HelloSwing extends JFrame {
	public static void main(String[]args){
		HelloSwing win = new HelloSwing();
		win.setVisible(true);
	}
	public HelloSwing(){
		this.setSize(200, 100);
		this.setTitle("Hello Swing");
		this.add(new JLabel("Hello World!"));
	}
}
