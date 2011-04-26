package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

/**
 * The Class Grid.
 */
public class Grid {
	
	private ArrayList<CellGroup> rows;
	private ArrayList<CellGroup> cols;
	private ArrayList<CellGroup> boxes;
	private Cell[][] cells;
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
		boxes = new ArrayList<CellGroup>();
		for(int i = 0; i < 9; i++){
			rows.add(new CellGroup());
			cols.add(new CellGroup());
			boxes.add(new CellGroup());
		}
		cells = new Cell[9][9];
		for(int y = 0; y < 9; y++){
			for(int x = 0; x <  9; x++){
				cells[y][x] = new Cell();
				CellGroup parentRow = rows.get(y);
				CellGroup parentColumn = cols.get(x);
				CellGroup parentBox = boxes.get(getBoxIndexForCellAt(x,y));
				parentRow.add(cells[y][x]);
				cells[y][x].setParentRow(parentRow);
				parentColumn.add(cells[y][x]);
				cells[y][x].setParentColumn(parentColumn);
				parentBox.add(cells[y][x]);
				cells[y][x].setParentBox(parentBox);
			}
		}
		isPopulated = false;
	}

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
		clean = clean.replaceAll("\\.","0");
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
	 * Gets the box index for cell at the given position.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @return the box index for cell at (x,y)
	 */
	public int getBoxIndexForCellAt(int x, int y){
		int gridIndex = (x/3) + ((y/3)*3);
		return gridIndex;
	}
	
	/**
	 * Gets the box.
	 *
	 * @param g the index of the box
	 * @return CellGroup representing the box
	 */
	public CellGroup getBox(int g){
		return boxes.get(g);
	}
	
	/**
	 * Gets the row.
	 *
	 * @param y the index of the row
	 * @return CellGroup representing the row
	 */
	public CellGroup getRow(int y){
		return rows.get(y);
	}
	
	/**
	 * Gets the column.
	 *
	 * @param x the index of the column
	 * @return CellGroup representing the column
	 */
	public CellGroup getColumn(int x){
		return cols.get(x);
	}

}
