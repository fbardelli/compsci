package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

// TODO: Auto-generated Javadoc
/**
 * The Class Grid.
 */
public class Grid {
	
	/** The rows. */
	private ArrayList<CellGroup> rows;
	
	/** The cols. */
	private ArrayList<CellGroup> cols;
	
	/** The grids. */
	private ArrayList<CellGroup> grids;
	
	/** The cells. */
	private Cell[][] cells;
	
	/** The is populated. */
	private boolean isPopulated;
	
	/**
	 * Instantiates a new grid.
	 */
	public Grid(){
		reset();
	}
	
	/**
	 * Reset.
	 */
	public void reset(){
		rows = new ArrayList<CellGroup>();
		cols = new ArrayList<CellGroup>();
		grids = new ArrayList<CellGroup>();
		for(int i = 0; i < 9; i++){
			rows.add(new CellGroup());
			cols.add(new CellGroup());
			grids.add(new CellGroup());
		}
		cells = new Cell[9][9];
		for(int y = 0; y < 9; y++){
			for(int x = 0; x <  9; x++){
				cells[y][x] = new Cell();
				CellGroup parentRow = rows.get(y);
				CellGroup parentColumn = cols.get(x);
				CellGroup parentGrid = grids.get(getGridIndexForCellAt(x,y));
				parentRow.add(cells[y][x]);
				cells[y][x].setParentRow(parentRow);
				parentColumn.add(cells[y][x]);
				cells[y][x].setParentColumn(parentColumn);
				parentGrid.add(cells[y][x]);
				cells[y][x].setParentGrid(parentGrid);
			}
		}
		isPopulated = false;
	}
	/*
	 	 0             1             2
	0,0 1,0 2,0	  3,0 4,0 5,0   0,6 7,0 8,0  0
	0,1 1,1 2,1	  3,1 4,1 5,1   6,1 7,1 8,1  9
	0,2 1,2 2,2	  3,2 4,2 5,2   6,2 7,2 8,2  18
	
		 3             4             5
	0,3 1,3 2,3   3,3 4,3 5,3   6,3 7,3 8,3  27
	0,4 1,4 2,4   3,4 4,4 5,4   6,4 7,4 8,4  36
	0,5 1,5 2,5   3,5 4,5 5,5   6,5 7,5 8,5  45
	
		 6             7             8
	0,6 1,6 2,6   3,6 4,6 5,6   6,6 7,6 8,6  54
	0,7 1,7 2,7   3,7 4,7 5,7   6,7 7,7 8,7  63
	0,8 1,8 2,8   3,8 4,8 5,8   6,8 7,8 8,8	 72

	*/

	/**
	 * Populate.
	 *
	 * @param a the a
	 */
	public void populate(int[][] a){
		for (int y = 0; y < 9; y++){
			for (int x = 0; x < 9; x++){
				if (a[y][x]!=0){
					cells[y][x].setValue(a[y][x]); 
				}
			}
		}
		isPopulated = true;
	}
	
	/**
	 * Parses the.
	 *
	 * @param s the s
	 */
	public void parse(String s){
		if(isPopulated){
			reset();
		}
		int[][] grid = new int[9][9];
		String[] fileRows = new String[9];
		String clean = s.replaceAll("\n","");
		for(int i=0; i<9; i++){
		    fileRows[i] = clean.substring(i*9,i*9+9);
		}
		int i = 0;
		for (String r : fileRows){
			for (int j = 0; j < r.length(); j++){
				grid[i][j]= Integer.parseInt(r.substring(j,j+1));
			}
			i++;
		}
		populate(grid);
	}
	
	/**
	 * First three.
	 *
	 * @return the int
	 */
	public int firstThree(){
	    CellGroup cg = rows.get(0);
	    return cg.getCells().get(0).getValue() * 100 +
	    cg.getCells().get(1).getValue() * 10 +
	    cg.getCells().get(2).getValue();
	}
	
	/**
	 * Prints the.
	 */
	public void print(){
		Iterator<CellGroup> it = rows.iterator();
		while(it.hasNext()){
			CellGroup cg = it.next();
			ArrayList<Cell> c = cg.getCells();
			Iterator<Cell> cellIterator = c.iterator();
			while(cellIterator.hasNext()){
				System.out.print(cellIterator.next().getValue());
			}
			System.out.println();
		}
	}
	
	/**
	 * Prints the verbose.
	 */
	public void printVerbose(){
		//char[] bigGrid = new char[36*36];
		Iterator<CellGroup> it = rows.iterator();
		System.out.print("===========================================\n");
		int currentRow = 1;
		while(it.hasNext()){
			CellGroup cg = it.next();
			ArrayList<Cell> cells = cg.getCells();
			//Iterator<Cell> cellIterator = c.iterator();
			for(int j = 0; j < 3; j++ ){
				System.out.print("| ");
				for (int i = 0; i < cells.size(); i++){
					Cell cell = cells.get(i);
					HashMap<Integer,Boolean> possibles = cell.getPossibleValues();
					for( int k=1; k<=3; k++){
						int index = k + j*3;
						//System.out.println(index);						
						if(possibles.get(new Integer(index)).booleanValue()){
							System.out.print(index);
						}else{
							System.out.print("*");
						}
					}
					if( (i+1) % 3 !=0){
						System.out.print("|");
					}else{
						System.out.print(" | ");					
					}
				}
				System.out.println();
			}
			if(currentRow % 3 > 0){
				System.out.print("|----+---+----+----+---+----+----+---+----|\n");
			} else {
				System.out.print("==========================================\n");
			}
			
			
			currentRow++;
		}	
	}
	
	/**
	 * Total count possible values.
	 *
	 * @return the int
	 */
	public int totalCountPossibleValues(){
		int totalPossibleValues = 0;
		for (int y = 0; y < 9; y++ ){
			for (int x = 0; x < 9; x++){
				HashMap<Integer,Boolean> pValues = cells[y][x].getPossibleValues();
				for(Integer i :pValues.keySet() ){
					if(pValues.get(i)){
						totalPossibleValues++;
					}
				}
			}
		}
		return totalPossibleValues;
	}
	
	
	/**
	 * Count solved.
	 *
	 * @return the int
	 */
	public int countSolved(){
		int countSolved = 0;
		for( CellGroup cg: rows){
			countSolved += cg.getSolved().size();
		}
		return countSolved;
	}
	
	/**
	 * Gets the cell.
	 *
	 * @param x the x
	 * @param y the y
	 * @return the cell
	 */
	public Cell getCell(int x,int y){
		return cells[y][x];
	}
	
	/**
	 * Gets the grid index for cell at.
	 *
	 * @param x the x
	 * @param y the y
	 * @return the grid index for cell at
	 */
	public int getGridIndexForCellAt(int x, int y){
		int gridIndex = (x/3) + ((y/3)*3);
		return gridIndex;
	}
	
	/**
	 * Gets the grid.
	 *
	 * @param g the g
	 * @return the grid
	 */
	public CellGroup getGrid(int g){
		return grids.get(g);
	}
	
	/**
	 * Gets the row.
	 *
	 * @param y the y
	 * @return the row
	 */
	public CellGroup getRow(int y){
		return rows.get(y);
	}
	
	/**
	 * Gets the column.
	 *
	 * @param x the x
	 * @return the column
	 */
	public CellGroup getColumn(int x){
		return cols.get(x);
	}

}
