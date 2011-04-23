package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

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
                    ArrayList<Integer> allSolved = new ArrayList();
                    for(CellGroup cg : c.getCellGroups()){
                    	allSolved.addAll(cg.getSolved());
                    }
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
                	for (CellGroup cg: c.getCellGroups()){
                		solveHiddenSingleInCellGroup(c, cg);
                	}
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
                c.setValue(i.intValue());
            }

        }
        
    }

    public void solveNakedPair(){
        for (int y = 0; y < 9; y++ ){
            for (int x = 0; x < 9; x++){
                Cell c = grid.getCell(x, y);
                HashMap<Integer,Boolean> pValues = c.getPossibleValues();
                if( c.getPossibleValueCount() == 2){
                	for (CellGroup cg: c.getCellGroups()){
                        solveNakedPairInCellGroup(pValues, cg);
                	}
                }
            }
        }
    }
    
    public void solveNakedPairInCellGroup(HashMap<Integer,Boolean> pValues, CellGroup cg){
    	int count = 0;
    	List<Cell> eliminateCells = new ArrayList();
    	for(Cell c: cg.getCells()){
    		if(pValues.equals(c.getPossibleValues())){
    			count++;
    		}else{
    			eliminateCells.add(c);
    		}
    	}
    	if (count == 2){
    		for(Cell c: eliminateCells){
    			for (Integer i : pValues.keySet()){
    				if(pValues.get(i)){
    					c.eliminatePossibleValue(i.intValue());
    				}
    			}
    		}
    	}
    }
    
    public void solveHiddenPair(){
    	for(int i=0; i<9; i++){
    		solveHiddenPairInCellGroup(grid.getColumn(i));
    		solveHiddenPairInCellGroup(grid.getRow(i));
    		solveHiddenPairInCellGroup(grid.getGrid(i));    		
    	}
    }
    
    public void solveXWing(){
    	for (int y = 0; y < 9; y++){
    		for(int y1 = y+1; y1 < 9; y1++){
    			solveXWingsInRows(y,y1);
    		}
    	}
    }
    
    
    public void solveXWingsInRows(int y, int y1){
    	CellGroup cg1 = grid.getRow(y);
    	CellGroup cg2 = grid.getRow(y1);
    	for (int c = 1; c <= 9; c++){
        	List<Integer> cgPositions = new ArrayList<Integer>();
        	for(int i = 0; i < 9; i++){
        		Integer candidate = new Integer(c);
        		if(cg1.getCells().get(i).getPossibleValues().get(candidate)
        				&&cg2.getCells().get(i).getPossibleValues().get(candidate))
        				cgPositions.add(i);
        	}
        	if (cgPositions.size() == 2){
        		System.out.println("found XWING fo candidate "+ c +"!" +
        				"("+y+","+cgPositions.get(0)+"),"+
        				"("+y+","+cgPositions.get(1)+"),"+
        				"("+y1+","+cgPositions.get(0)+"),"+
        				"("+y1+","+cgPositions.get(1)+"),"
        		);
        	}
    	}
    }

    public void solveHiddenPairInCellGroup(CellGroup cg){
    	for(int pv1 = 9; pv1 > 1; pv1--){
    		for(int pv2 = pv1 - 1; pv2 > 0; pv2--){
				List<Cell> matchingCells = new ArrayList();
    			for(Cell c: cg.getCells()){
    				if(c.getPossibleValues().containsValue(new Integer(pv1)) &&
    						c.getPossibleValues().containsValue(new Integer(pv2))){
    					matchingCells.add(c);
    				}
    			}
    			if(matchingCells.size()==2){
    				Cell c1 = matchingCells.get(0);
    				Cell c2 = matchingCells.get(1);    				
    				for(int i = 1; i <= 9; i++){
    					if(i!=pv1&&i!=pv2){
    						c1.eliminatePossibleValue(i);
    						c2.eliminatePossibleValue(i);
    					}
    				}
    			}
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
