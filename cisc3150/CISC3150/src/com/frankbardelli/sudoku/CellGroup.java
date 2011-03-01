package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.Arrays;

public class CellGroup {
	private ArrayList<Cell> cells;
	private boolean[] solved;
	public CellGroup(){
		solved = new boolean[9];
		Arrays.fill(solved, false);
		cells = new ArrayList<Cell>();
	}
	
	public void add(Cell c){
		cells.add(c);
	}
	
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
	
	public ArrayList<Integer> getUnsolved(){
		ArrayList<Integer> unsolved = new ArrayList<Integer>();
		for ( int i = 0; i < solved.length; i++){
			if (! solved[i] )
				unsolved.add(new Integer(i+1));
		}
		return unsolved;
	}
	
	public ArrayList<Integer> getSolved(){
		ArrayList<Integer> listSolved = new ArrayList<Integer>();
		for ( int i = 0; i < solved.length; i++){
			if ( solved[i] )
				listSolved.add(new Integer(i+1));
		}
		return listSolved;
	}
	
	public boolean isSolved(){
		return (getUnsolved().size() == 0);
	}
	
	public ArrayList<Cell> getCells(){
		return cells;
	}

}
