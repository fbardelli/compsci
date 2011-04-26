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

/**
 * The Class Window.
 */
public class Window extends JFrame {
	Grid grid;
	GameBoard sudokuBoard;

	/**
	 * The main method.
	 *
	 * @param args command line arguments
	 */
	public static void main(String[] args){
		Grid grid = new Grid();
	    Problems problems = new Problems();
	    List<String> problemList = problems.getProblemList();
	    grid.parse(problemList.get(0));
		Window w = new Window(grid);
	}
	
	/**
	 * Instantiates a new Sudoku Solver window.
	 *
	 * @param grid the Grid object
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
	 * Creates buttons to complete solve the puzzle using two different methods
	 */
	public void createButtons(){
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BorderLayout());
		JButton solveEasyButton = new JButton("Solve Deductively");
		solveEasyButton.addActionListener(new SolveDeductiveListener(this,this.grid));
		JButton solveAnyButton = new JButton("Solve Brute Force");
		solveAnyButton.addActionListener(new SolveBacktrackingListener(this,this.grid));
		buttonPanel.add(solveEasyButton,BorderLayout.NORTH);
		buttonPanel.add(solveAnyButton,BorderLayout.SOUTH);
		this.add(buttonPanel,BorderLayout.SOUTH);		
	}
	
	/**
	 * Creates a panel with buttons to let the user interactively solve the puzzle.
	 */
	public void createInteractivePanel(){
		JPanel sidePanel = new JPanel();
		sidePanel.setLayout(new BoxLayout(sidePanel,BoxLayout.PAGE_AXIS));
		JButton solveNSButton = new JButton("Solve Naked Single");
		solveNSButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveNakedSingles();
                updateGrid();               
            }    
		});
		sidePanel.add(solveNSButton);
		JButton solveHSButton = new JButton("Solve Hidden Single");
        solveHSButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveHiddenSingles();
                updateGrid();               
            }    
        });		
		sidePanel.add(solveHSButton);
		JButton solveNPButton = new JButton("Solve Naked Pair");
        solveNPButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveNakedPair();
                updateGrid();               
            }    
        });
		sidePanel.add(solveNPButton);
		JButton solveHPButton = new JButton("Solve Hidden Pair");
        solveHPButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveHiddenPair();
                updateGrid();               
            }    
        });
		sidePanel.add(solveHPButton);
		JButton solveNTButton = new JButton("Solve Naked Triplet");
        solveNTButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveNakedTriplet();
                updateGrid();               
            }    
        });
		sidePanel.add(solveNTButton);
		JButton solvePPButton = new JButton("Solve Pointing Pair");
        solvePPButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solvePointingPair();
                updateGrid();               
            }    
        });
		sidePanel.add(solvePPButton);
		JButton solveXWButton = new JButton("Solve X-Wing");
        solveXWButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent arg0) {
                Solver s = new Solver(grid);
                s.solveXWing();
                updateGrid();               
            }    
        });
		sidePanel.add(solveXWButton);
		this.add(sidePanel,BorderLayout.EAST);
	}
	
	/**
	 * Create the application menu bar.
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
	 * Update the window with the current state of the grid
	 */
	public void updateGrid(){
		sudokuBoard.updateGrid(grid);
	}

	/**
	 * The listener interface for receiving puzzleSelect events.
	 *
	 * @see PuzzleSelectEvent
	 */
	public class PuzzleSelectListener implements ActionListener{
		Window window;
		Grid grid;
		String puzzle;
		String title;
		
		/**
		 * Listener for puzzle selection, Parses a new puzzle into the grid.
		 *
		 * @param w the Sudoku Window
		 * @param g the Grid object
		 * @param p String representing an unsolved Puzzle
		 * @param puzzleTitle the puzzle title
		 */
		public PuzzleSelectListener(Window w, Grid g, String p,String puzzleTitle){
			this.window = w;
			this.grid = g;
			this.puzzle = p;
			this.title = puzzleTitle;
		}
		
		public void actionPerformed(ActionEvent e) {
			this.grid.parse(puzzle);
			this.window.setTitle(title);
			this.window.updateGrid();
		}	
	}

	/**
	 * The listener interface for receiving solveDeductive events.
	 *
	 * @see SolveDeductiveEvent
	 */
	public class SolveDeductiveListener implements ActionListener{
		Window window;
		Grid grid;
		
		/**
		 * Instantiates a new solve listener using human-like deductive reasoning methods.
		 *
         * @param w the Sudoku Window
         * @param g the Grid object
		 */
		public SolveDeductiveListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		
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
	 *
	 * @see SolveBacktrackingEvent
	 */
	public class SolveBacktrackingListener implements ActionListener{
		Window window;
		Grid grid;
		
		/**
		 * Instantiates a new listeners for solving using brute force backtracking.
		 *
         * @param w the Sudoku Window
         * @param g the Grid object
		 */
		public SolveBacktrackingListener(Window w, Grid g){
			this.window = w;
			this.grid = g;
		}
		
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
