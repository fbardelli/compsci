package com.frankbardelli.sudoku;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

public class Window extends JFrame {
	public static void main(String[] args){
		Window w = new Window();
		
	}
	public Window(){
		this.setSize(800, 800);
		this.setVisible(true);
		this.setLayout(new BorderLayout());
		this.add(getSudokuGrid(),BorderLayout.CENTER);
	}
	
	public JPanel getSudokuGrid(){
		JPanel sudokuGrid = new JPanel();
		sudokuGrid.setLayout(new GridLayout(3,3,2,2));
		for (int y = 0; y < 3; y++){
			for (int x = 0; x < 3; x++){
				JPanel innerGrid = new JPanel();
				innerGrid.setLayout(new GridLayout(3,3,1,1));
				innerGrid.setBorder(new LineBorder(Color.BLACK));
				sudokuGrid.add(innerGrid);
				Random r = new Random();
				for (int j = 0; j < 3; j++){
					for (int k = 0; k < 3; k++){				
						JPanel cell = new JPanel();
						cell.setBorder(new LineBorder(Color.BLUE));
						innerGrid.add(cell);
						if(r.nextBoolean()){
							cell.setLayout(new GridLayout(3,3));
							for (int l = 1; l <= 9; l++){
									JPanel pValue = new JPanel();
									//pValue.setBorder(new LineBorder(Color.GRAY));
									JLabel label = new JLabel(new Integer(l).toString());
									//label.setSize(5, 5);
									label.setForeground(Color.BLUE);
									//label.setFont(Font.getFont(Font.MONOSPACED));
									pValue.add(label);
									cell.add(pValue);
							}
						} else {
							JLabel label = new JLabel(new Integer(3*j+k+1).toString());
							label.setFont(label.getFont().deriveFont(50.0f));
							cell.add(label);
							
						}
					}
				}
			}
		}
		return sudokuGrid;
	}

}
