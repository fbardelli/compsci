package com.frankbardelli.sudoku;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

public class Window extends JFrame {
	Grid grid;
	GameBoard sudokuBoard;

	public static void main(String[] args){
		Grid grid = new Grid();
	    Problems problems = new Problems();
	    List<String> problemList = problems.getProblemList();
	    grid.parse(problemList.get(0));
		Window w = new Window(grid);
	}
	
	public Window(Grid grid){
		this.grid = grid;
		this.setSize(600, 600);
		this.setLayout(new BorderLayout());
		sudokuBoard = new GameBoard();
		this.add(sudokuBoard ,BorderLayout.CENTER);
		createButtons();
		createMenu();
		this.updateGrid();
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	    this.setVisible(true);
	}
	
	public void createButtons(){
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BorderLayout());
		JButton solveEasyButton = new JButton("Solve Deductively");
		solveEasyButton.addActionListener(new SolveEasyListener(this,this.grid));
		JButton solveAnyButton = new JButton("Solve Brute Force");
		solveAnyButton.addActionListener(new SolveListener(this,this.grid));
		buttonPanel.add(solveEasyButton,BorderLayout.NORTH);
		buttonPanel.add(solveAnyButton,BorderLayout.SOUTH);
		this.add(buttonPanel,BorderLayout.SOUTH);		
	}
	
	public void createMenu(){
		JMenuBar menuBar = new JMenuBar();
		JMenu puzzles = new JMenu("Puzzles");
		Problems problems = new Problems();
		JMenu[] puzzleList = new JMenu[5];
		for (int i = 0; i < 5; i++){
			puzzleList[i] = new JMenu("Puzzles " + (10 * i + 1) + "-" + (10 * (i+1)) );
			puzzles.add(puzzleList[i]);
		}
		int j = 0;
		for (String p : problems.getProblemList()){
			//a group of JMenuItems
			JMenuItem menuItem = new JMenuItem("Puzzle #"+ (j+1));
			puzzleList[j/10].add(menuItem);
			menuItem.addActionListener(new PuzzleSelectListener(this,grid,p));
			j++;
		}
		JMenuItem worstCase = new JMenuItem("Worst Case Scenario");
		worstCase.addActionListener(new PuzzleSelectListener(this,grid,problems.worstCaseScenario()));
		puzzles.add(worstCase);
		menuBar.add(puzzles);
		this.setJMenuBar(menuBar);

	}
	
	public void updateGrid(){
		sudokuBoard.updateGrid(grid);
	}

	public class PuzzleSelectListener implements ActionListener{
		Window window;
		Grid grid;
		String puzzle;
		public PuzzleSelectListener(Window w, Grid g, String p){
			this.window = w;
			this.grid = g;
			this.puzzle = p;
		}
		public void actionPerformed(ActionEvent e) {
			this.grid.parse(puzzle);
			this.window.updateGrid();
		}	
	}

	public class SolveEasyListener implements ActionListener{
		Window window;
		Grid grid;
		public SolveEasyListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		public void actionPerformed(ActionEvent e) {
			Solver s = new Solver(this.grid);
			int lastCountPossibleValues;
			do {
				lastCountPossibleValues = this.grid.totalCountPossibleValues();
				s.solveNakedSingles();
				s.solveHiddenSingles();
			} while( this.grid.totalCountPossibleValues()  < lastCountPossibleValues );
			//this.grid.print();
			this.window.updateGrid();
		}
	}
	
	public class SolveListener implements ActionListener{
		Window window;
		Grid grid;
		public SolveListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		public void actionPerformed(ActionEvent e) {
			Solver s = new Solver(this.grid);
			s.solveBacktracking();
			//this.grid.print();
			this.window.updateGrid();
		}
		
	}
}
