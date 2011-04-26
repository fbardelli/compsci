package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.Arrays;

// TODO: Auto-generated Javadoc
/**
 * The Class CellGroup.
 */
public class CellGroup {
	
	/** The cells. */
	private ArrayList<Cell> cells;
	
	/** The solved. */
	private boolean[] solved;
	
	/**
	 * Instantiates a new cell group.
	 */
	public CellGroup(){
		solved = new boolean[9];
		Arrays.fill(solved, false);
		cells = new ArrayList<Cell>();
	}
	
	/**
	 * Adds the.
	 *
	 * @param c the c
	 */
	public void add(Cell c){
		cells.add(c);
	}
	
	/**
	 * Solve.
	 *
	 * @param n the n
	 */
	public void solve(int n){
		if (n > 0 && n <= solved.length){ 
			solved[n-1] = true;
		}
		for (Cell c : cells){
			if(c.getValue() != n){
				c.eliminatePossibleValue(n);
			}
		}
	}
	
	/**
	 * Gets the unsolved.
	 *
	 * @return the unsolved
	 */
	public ArrayList<Integer> getUnsolved(){
		ArrayList<Integer> unsolved = new ArrayList<Integer>();
		for ( int i = 0; i < solved.length; i++){
			if (! solved[i] )
				unsolved.add(new Integer(i+1));
		}
		return unsolved;
	}
	
	/**
	 * Gets the solved.
	 *
	 * @return the solved
	 */
	public ArrayList<Integer> getSolved(){
		ArrayList<Integer> listSolved = new ArrayList<Integer>();
		for ( int i = 0; i < solved.length; i++){
			if ( solved[i] )
				listSolved.add(new Integer(i+1));
		}
		return listSolved;
	}
	
	/**
	 * Checks if is solved.
	 *
	 * @return true, if is solved
	 */
	public boolean isSolved(){
		return (getUnsolved().size() == 0);
	}
	
	/**
	 * Gets the cells.
	 *
	 * @return the cells
	 */
	public ArrayList<Cell> getCells(){
		return cells;
	}

}
