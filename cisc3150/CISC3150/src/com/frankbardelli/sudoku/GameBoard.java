package com.frankbardelli.sudoku;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

public class GameBoard extends JPanel{
	JPanel[] subgridPanel;
	JPanel[][] cellPanel;
	public GameBoard(){
		this.subgridPanel = new JPanel[9];
		this.cellPanel = new JPanel[9][9];
		setLayout(new GridLayout(3,3,2,2));
		for (int subgridIndex = 0; subgridIndex < 9; subgridIndex++) {
			subgridPanel[subgridIndex] = new JPanel();
			subgridPanel[subgridIndex].setLayout(new GridLayout(3, 3, 1, 1));
			subgridPanel[subgridIndex].setBorder(new LineBorder(Color.BLACK));
			add(subgridPanel[subgridIndex]);
			for (int cellIndex = 0; cellIndex < 9; cellIndex++) {
				cellPanel[subgridIndex][cellIndex] = new JPanel();
				cellPanel[subgridIndex][cellIndex].setBorder(new LineBorder(Color.BLUE));
				subgridPanel[subgridIndex].add(cellPanel[subgridIndex][cellIndex]);
			}
		}
	}


	public void updateGrid(Grid grid){
		for (int subgridIndex = 0; subgridIndex < 9; subgridIndex++) {
			CellGroup cg = grid.getGrid(subgridIndex);
			ArrayList<Cell> cells = cg.getCells();
			for (int cellIndex = 0; cellIndex < 9; cellIndex++) {
				Cell c = cells.get(cellIndex);
				JPanel cell = cellPanel[subgridIndex][cellIndex];
				cell.removeAll();
				if (c.getValue() == 0) { 
					cell.setLayout(new GridLayout(3,3)); 
					HashMap<Integer, Boolean> pValues = c.getPossibleValues(); 
					for (int l = 1; l <= 9; l++) {
						JPanel pValue = new JPanel();
						JLabel label = new JLabel();
						if(pValues.get(new Integer(l))) {
							label.setText(new Integer(l).toString());
						}
						label.setForeground(Color.BLUE);
						pValue.add(label);
						cell.add(pValue); 
					} 
				} else {
					cell.setLayout(new FlowLayout());
					JLabel label = new JLabel(new Integer(c.getValue()).toString());
					label.setFont(label.getFont().deriveFont(40.0f));
					cell.add(label);
				}
				//Cell subcomponents and layout may have changed so repaint and revalidate
				cell.repaint();
				cell.revalidate();
			}
		}
		
	}
}