package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.Arrays;

// TODO: Auto-generated Javadoc
/**
 * The Class CellGroup.
 */
public class CellGroup {
	
	private ArrayList<Cell> cells;	
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
	 * Adds a Cell object to the cell group
	 *
	 * @param c the Cell object
	 */
	public void add(Cell c){
		cells.add(c);
	}
	
	/**
	 * Remove value n from the list of possible values for each cell
	 * Usually called when a number has been definitively proven
	 * to be in a specific cell.
	 *
	 * @param n the number to eliminate
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
	 * Gets the unsolved numbers in the CellGroup
	 *
	 * @return the ArrayList of unsolved numbers
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
	 * Gets the solved numbers in the CellGroup
	 *
	 * @return the ArrayList of solved numbers
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
	 * Checks if the entire CellGroup is solved.
	 *
	 * @return true, if the CellGroup is solved
	 */
	public boolean isSolved(){
		return (getUnsolved().size() == 0);
	}
	
	/**
	 * Gets the cells in the CellGroup
	 *
	 * @return a list of the Cell objects in the CellGroup
	 */
	public ArrayList<Cell> getCells(){
		return cells;
	}

}
