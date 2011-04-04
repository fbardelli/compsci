package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;

public class Solver {
    private Grid grid;
    
    public Solver(Grid grid){
        this.grid = grid;
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
        if(! solveBT(0,0)){
            System.out.println("Failed to solve Puzzle");
        }
    }
    
    private boolean solveBT(int y, int x) {
        if (y == 9) {
            y = 0;
            if (++x == 9)
                return true;
        }
        if ( grid.getCell(x, y).getValue() != 0)  // skip filled cells
            return solveBT(y+1,x);

        for (int val = 1; val <= 9; ++val) {
            if (legal(y,x,val)) {
                grid.getCell(x, y).setValue(val);
                if (solveBT(y+1,x))
                    return true;
            }
        }
        //System.out.println("setting "+ i + " " + j);
        grid.getCell(x, y).setValue(0); // reset on backtrack
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