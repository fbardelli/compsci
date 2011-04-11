package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;

public class Solver {
    private Grid grid;
    private long solveCounter;
    
    public Solver(Grid grid){
        this.grid = grid;
        this.solveCounter = 0;
    }
    
    public void solveNakedSingles(){
        for (int y = 0; y < 9; y++ ){
            for (int x = 0; x < 9; x++){
                Cell c = grid.getCell(x, y);//  cells[y][x];
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
                Cell c = grid.getCell(x, y);//cells[y][x];
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
    
    /* Based on Bob Carpenters backtracking sudoku solver 
     * http://www.colloquial.com/games/sudoku/java_sudoku.html
     */
    public void solveBacktracking(){
    	this.solveCounter = 0;
        if(! solveBT(0,0)){
            System.out.println("Failed to solve Puzzle");
        }
        System.out.println("Solved in " + this.solveCounter + " iterations");
    }
    
    private boolean solveBT(int y, int x) {
    	this.solveCounter++;
    	//at end of column?
        if (y == 9) {
        	//go to next column
            y = 0;
            //if we reach (8,8) we are done
            if (++x == 9)
                return true;
        }
        //if cell is already filled, increment
        if ( grid.getCell(x, y).getValue() != 0) 
            return solveBT(y+1,x);

        //try each value
        for (int val = 1; val <= 9; ++val) {
        	//can this value go in this square?
            if (legal(y,x,val)) {
            	//try the value and move on to the next square in the row
                grid.getCell(x, y).setValue(val);
                if (solveBT(y+1,x))
                    return true;
            }
        }
        // if we get this far, there are no legal values
        // reset and go back
        grid.getCell(x, y).setValue(0);
        return false;
    }
    
    private boolean legal(int y, int x, int val) {
        for (int y2 = 0; y2 < 9; ++y2)  // col
            if (val == grid.getCell(x, y2).getValue())
                return false;

        for (int x2 = 0; x2 < 9; ++x2) // row
            if (val == grid.getCell(x2, y).getValue())
                return false;

        int boxRowOffset = (y / 3)*3;
        int boxColOffset = (x / 3)*3;
        for (int k = 0; k < 3; ++k) // box
            for (int m = 0; m < 3; ++m)
                if (val == grid.getCell(boxColOffset+m, boxRowOffset+k).getValue())
                    return false;

        return true; // no violations, so it's legal
    }

}
