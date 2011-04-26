package com.frankbardelli.sudoku;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

// TODO: Auto-generated Javadoc
/**
 * The Class Window.
 */
public class Window extends JFrame {
	
	/** The grid. */
	Grid grid;
	
	/** The sudoku board. */
	GameBoard sudokuBoard;


	/**
	 * The main method.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args){
		Grid grid = new Grid();
	    Problems problems = new Problems();
	    List<String> problemList = problems.getProblemList();
	    grid.parse(problemList.get(0));
		Window w = new Window(grid);
	}
	
	/**
	 * Instantiates a new window.
	 *
	 * @param grid the grid
	 */
	public Window(Grid grid){
		this.grid = grid;
		this.setSize(800, 650);
		this.setLayout(new BorderLayout());
		sudokuBoard = new GameBoard();
		this.add(sudokuBoard ,BorderLayout.CENTER);
		createButtons();
		createInteractivePanel();
		createMenu();
		this.updateGrid();
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	    this.setVisible(true);
	}
	
	/**
	 * Creates the buttons.
	 */
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
	
	/**
	 * Creates the interactive panel.
	 */
	public void createInteractivePanel(){
		JPanel sidePanel = new JPanel();
		sidePanel.setLayout(new BoxLayout(sidePanel,BoxLayout.PAGE_AXIS));
		JButton solveNSButton = new JButton("Demonstrate Naked Single");
		sidePanel.add(solveNSButton);
		JButton solveHSButton = new JButton("Demonstrate Hidden Single");
		sidePanel.add(solveHSButton);
		JButton solveNPButton = new JButton("Demonstrate Naked Pair");
		sidePanel.add(solveNPButton);
		JButton solveHPButton = new JButton("Demonstrate Hidden Pair");
		sidePanel.add(solveHPButton);
		JButton solveNTButton = new JButton("Demonstrate Naked Triplet");
		sidePanel.add(solveNTButton);
		JButton solvePPButton = new JButton("Demonstrate Pointing Pair");
		sidePanel.add(solvePPButton);
		JButton solveXWButton = new JButton("Demonstrate X-Wing");
		sidePanel.add(solveXWButton);
		this.add(sidePanel,BorderLayout.EAST);
	}
	
	/**
	 * Creates the menu.
	 */
	public void createMenu(){
		JMenuBar menuBar = new JMenuBar();
		JMenu file = new JMenu("File");
		file.add(new JMenuItem("Import..."));
		JMenuItem exit = new JMenuItem("Exit");
		exit.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				System.exit(DISPOSE_ON_CLOSE);
			}
		});
		file.add(exit);
		menuBar.add(file);
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
			String puzzleTitle = "Puzzle #"+ (j+1);
			JMenuItem menuItem = new JMenuItem(puzzleTitle);
			puzzleList[j/10].add(menuItem);
			menuItem.addActionListener(new PuzzleSelectListener(this,grid,p,puzzleTitle));
			j++;
		}
		String puzzleTitle = "Brute Force Worst Case";
		JMenuItem worstCase = new JMenuItem(puzzleTitle);
		worstCase.addActionListener(new PuzzleSelectListener(this,grid,problems.worstCaseScenario(),puzzleTitle));
		puzzles.add(worstCase);
		menuBar.add(puzzles);
		this.setJMenuBar(menuBar);

	}
	
	/**
	 * Update grid.
	 */
	public void updateGrid(){
		sudokuBoard.updateGrid(grid);
	}

	/**
	 * The listener interface for receiving puzzleSelect events.
	 * The class that is interested in processing a puzzleSelect
	 * event implements this interface, and the object created
	 * with that class is registered with a component using the
	 * component's <code>addPuzzleSelectListener<code> method. When
	 * the puzzleSelect event occurs, that object's appropriate
	 * method is invoked.
	 *
	 * @see PuzzleSelectEvent
	 */
	public class PuzzleSelectListener implements ActionListener{
		
		/** The window. */
		Window window;
		
		/** The grid. */
		Grid grid;
		
		/** The puzzle. */
		String puzzle;
		
		/** The title. */
		String title;
		
		/**
		 * Instantiates a new puzzle select listener.
		 *
		 * @param w the w
		 * @param g the g
		 * @param p the p
		 * @param puzzleTitle the puzzle title
		 */
		public PuzzleSelectListener(Window w, Grid g, String p,String puzzleTitle){
			this.window = w;
			this.grid = g;
			this.puzzle = p;
			this.title = puzzleTitle;
		}
		
		/* (non-Javadoc)
		 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
		 */
		public void actionPerformed(ActionEvent e) {
			this.grid.parse(puzzle);
			this.window.setTitle(title);
			this.window.updateGrid();
		}	
	}

	/**
	 * The listener interface for receiving solveEasy events.
	 * The class that is interested in processing a solveEasy
	 * event implements this interface, and the object created
	 * with that class is registered with a component using the
	 * component's <code>addSolveEasyListener<code> method. When
	 * the solveEasy event occurs, that object's appropriate
	 * method is invoked.
	 *
	 * @see SolveEasyEvent
	 */
	public class SolveEasyListener implements ActionListener{
		
		/** The window. */
		Window window;
		
		/** The grid. */
		Grid grid;
		
		/**
		 * Instantiates a new solve easy listener.
		 *
		 * @param w the w
		 * @param g the g
		 */
		public SolveEasyListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		
		/* (non-Javadoc)
		 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
		 */
		public void actionPerformed(ActionEvent e) {
			Solver s = new Solver(this.grid);
			int lastCountPossibleValues;
			long startSeconds = System.currentTimeMillis();
			int iterations = 0;
			do {
				lastCountPossibleValues = this.grid.totalCountPossibleValues();
				//try simple methods
				do {
					lastCountPossibleValues = this.grid.totalCountPossibleValues();
					s.solveNakedSingles();
					s.solveHiddenSingles();
					s.solveNakedPair();
					s.solveHiddenPair();
				} while( this.grid.totalCountPossibleValues()  < lastCountPossibleValues );
				if(this.grid.totalCountPossibleValues() == 0)
					break;
				//try advanced methods
				s.solveNakedTriplet();
				s.solvePointingPair();
				s.solveXWing();
				iterations++;
			} while( this.grid.totalCountPossibleValues()  < lastCountPossibleValues );
	         long endSeconds = System.currentTimeMillis();
	         System.out.println("Solved deductively in " + (endSeconds-startSeconds) +
	                             "ms in " + iterations + " iterations");
			this.window.updateGrid();
		}
	}
	
	/**
	 * The listener interface for receiving solve events.
	 * The class that is interested in processing a solve
	 * event implements this interface, and the object created
	 * with that class is registered with a component using the
	 * component's <code>addSolveListener<code> method. When
	 * the solve event occurs, that object's appropriate
	 * method is invoked.
	 *
	 * @see SolveEvent
	 */
	public class SolveListener implements ActionListener{
		
		/** The window. */
		Window window;
		
		/** The grid. */
		Grid grid;
		
		/**
		 * Instantiates a new solve listener.
		 *
		 * @param w the w
		 * @param g the g
		 */
		public SolveListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		
		/* (non-Javadoc)
		 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
		 */
		public void actionPerformed(ActionEvent e) {
			Solver s = new Solver(this.grid);
	        long startSeconds = System.currentTimeMillis();
			s.solveBacktracking();
	        long endSeconds = System.currentTimeMillis();
	        System.out.println("Solved with brute force in " + (endSeconds-startSeconds) +
	                "ms in "+ s.getSolveCount() + " iterations");
			this.window.updateGrid();
		}
		
	}
}
