package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class Grid {
	private ArrayList<CellGroup> rows;
	private ArrayList<CellGroup> cols;
	private ArrayList<CellGroup> grids;
	private Cell[][] cells;
	public Grid(){
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
				System.out.println("(" + x + "," + y + ")" + getGridIndexForCellAt(x,y));
				parentGrid.add(cells[y][x]);
				cells[y][x].setParentGrid(parentGrid);
			}
		}
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

	public void populate(int[][] a){
		for (int y = 0; y < 9; y++){
			for (int x = 0; x < 9; x++){
				if (a[y][x]!=0){
					cells[y][x].setValue(a[y][x]); 
				}
			}
		}
	}
	
	public void parse(String s){
		int[][] grid = new int[9][9];
		String[] fileRows = s.split("\n");
		System.out.println(fileRows.length);
		int i = 0;
		for (String r : fileRows){
			for (int j = 0; j < r.length(); j++){
				grid[i][j]= Integer.parseInt(r.substring(j,j+1));
			}
			i++;
		}
		populate(grid);
	}
	
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
			/*
			while(cellIterator.hasNext()){
				Cell cell = cellIterator.next();
				//System.out.print(cell.getValue());
				HashMap<Integer,Boolean> possibles = cell.getPossibleValues();
				Iterator<Integer> intIterator = possibles.iterator();
				System.out.print("(");
				while(intIterator.hasNext()){
					Integer pValue = intIterator.next();
					System.out.print(pValue.toString());
				}
				System.out.print(")");
			}
			System.out.println();
			*/
		}	
	}
	
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
	
	public void solveNakedSingles(){
		for (int y = 0; y < 9; y++ ){
			for (int x = 0; x < 9; x++){
				Cell c = cells[y][x];
				if( c.getValue() < 1){
					CellGroup cRow = c.getParentRow();
					CellGroup cCol = c.getParentColumn();
					CellGroup cGrid = c.getParentGrid();
					ArrayList<Integer> allSolved = cRow.getSolved();
					allSolved.addAll(cCol.getSolved());
					allSolved.addAll(cGrid.getSolved());
					for(Integer i : allSolved){
						c.eliminatePossibleValue(i.intValue());
						c.attemptSolve();
					}
				}
				
			}
		}
	}
	
	public void solveHiddenSingles(){
		for (int y = 0; y < 9; y++ ){
			for (int x = 0; x < 9; x++){
				Cell c = cells[y][x];
				if( c.getValue() < 1){
					//System.out.println("checking cell ("+x+","+y+")for hiddens");
					CellGroup cRow = c.getParentRow();
					CellGroup cCol = c.getParentColumn();
					CellGroup cGrid = c.getParentGrid();
					solveHiddenSingleInCellGroup(c, cRow);
					solveHiddenSingleInCellGroup(c, cCol);
					solveHiddenSingleInCellGroup(c, cGrid);
				}
			}
		}
	}
	
	public void solveHiddenSingleInCellGroup(Cell c, CellGroup cg) {
		HashMap<Integer,Boolean> possibles = new HashMap<Integer,Boolean>();
		//c.getPossibleValues();
		HashMap<Integer,Boolean> cellPossibles = c.getPossibleValues();
		for( Integer i : cellPossibles.keySet()){
			if( cellPossibles.get(i).booleanValue() ){
				possibles.put(i, new Boolean(true));
			}
		}
		for( Cell c2 : cg.getCells()){
			if (! c.equals(c2) ){
				HashMap<Integer,Boolean> cell2Possibles = c2.getPossibleValues();
				for( Integer i : cellPossibles.keySet()){
					if( cell2Possibles.get(i).booleanValue() ){
						possibles.remove(i);
					}
				}
			}
		}
		if(possibles.size() == 1){
			for( Integer i : possibles.keySet()){
				//System.out.println( " For Cell only possibility is " + i.toString() );
				c.setValue(i.intValue());
			}

		}
		
	}
	
	public int countSolved(){
		int countSolved = 0;
		for( CellGroup cg: rows){
			countSolved += cg.getSolved().size();
		}
		return countSolved;
	}
	
	public Cell getCell(int x,int y){
		return cells[y][x];
	}
	
	public int getGridIndexForCellAt(int x, int y){
		int gridIndex = (x/3) + ((y/3)*3);
		return gridIndex;
	}
	
	public CellGroup getGrid(int g){
		return grids.get(g);
	}
	
	public CellGroup getRow(int y){
		return rows.get(y);
	}
	public CellGroup getColumn(int x){
		return cols.get(x);
	}

}
