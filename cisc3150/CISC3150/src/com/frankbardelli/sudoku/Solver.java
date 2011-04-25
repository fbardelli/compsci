package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Solver {
    private Grid grid;
    private long solveCounter;
    static int COLUMN = 1;
    static int ROW = 2;
    
    public Solver(Grid grid){
        this.grid = grid;
        this.solveCounter = 0;
    }
    
    public void solveNakedSingles(){
        for (int y = 0; y < 9; y++ ){
            for (int x = 0; x < 9; x++){
                Cell c = grid.getCell(x, y);//  cells[y][x];
                if( c.getValue() < 1){
                    ArrayList<Integer> allSolved = new ArrayList<Integer>();
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
    	List<Cell> eliminateCells = new ArrayList<Cell>();
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
    
    public void SolveNakedTriplet(){
        for(int first = 1; first <= 7; first++){
            for(int second = first + 1; second <= 8; second++ ){
                for (int third = second + 1; third <= 9; third++){
                    for(int i = 0; i < 9; i++){
                        //System.out.println("triplet "+first+" "+second+" "+third);
                        int bitField = (int) Math.pow(2,first) + (int) Math.pow(2,second) + (int)Math.pow(2,third);
                        if(solveNakedTripletInCellGroup(grid.getGrid(i),bitField,first,second,third)){
                            //System.out.println("Found naked triple in grid "+i +" on ("+ first+","+second+","+third+")");
                        }
                        if(solveNakedTripletInCellGroup(grid.getRow(i),bitField,first,second,third)){
                            //System.out.println("Found naked triple in row "+i +" on ("+ first+","+second+","+third+")");

                        }
                        if(solveNakedTripletInCellGroup(grid.getColumn(i),bitField,first,second,third)){
                            //System.out.println("Found naked triple in column "+i +" on ("+ first+","+second+","+third+")");

                        }
                        
                    }
                }
            }
        }
    }
    
    public boolean solveNakedTripletInCellGroup(CellGroup cg, int bitField, int first, int second, int third){
        int nakedTripleCandidates = 0;
        int bitTotal = 0;
        for(int i = 0; i <= 9; i++){
            bitTotal += (int)Math.pow(2,i);
        }
        List<Cell> eliminateCells = new ArrayList<Cell>();
        for(Cell c: cg.getCells()){
            if( c.getPossibleValueCount() < 2){
                continue;
            }
            int bitSum = 0;
            for(Integer pv : c.getPossibleValues().keySet()){
                if(c.getPossibleValues().get(pv)){
                    bitSum += (int)Math.pow(2,pv.intValue());
                }
            }
            
            boolean match = ((~(bitSum) | bitField) & bitTotal) == bitTotal;
            if(match){
                nakedTripleCandidates++;
                //System.out.println(Integer.toBinaryString(bitSum));
                //System.out.println(Integer.toBinaryString(bitField));
                //System.out.println(Integer.toBinaryString(bitTotal));
            }else{
                eliminateCells.add(c);
            }
        }
        if(nakedTripleCandidates == 3){
            for(Cell c : eliminateCells){
                c.eliminatePossibleValue(first);
                c.eliminatePossibleValue(second);
                c.eliminatePossibleValue(third);
            }
            return true;
        }
        return false;
    }
    
    public void solveHiddenPair(){
    	for(int i=0; i<9; i++){
    		solveHiddenPairInCellGroup(grid.getColumn(i));
    		solveHiddenPairInCellGroup(grid.getRow(i));
    		solveHiddenPairInCellGroup(grid.getGrid(i));    		
    	}
    }
    
    public void solvePointingPair(){
        for(int i = 0; i < 9; i ++){
            CellGroup cg = grid.getGrid(i);
            for(int c=1; c<=9; c++){
                CellGroup col=null;
                boolean clearColumn = false;
                for(Cell cell : cg.getCells()){
                    if(cell.getPossibleValues().get(new Integer(c))){
                        if(col == null){
                            col = cell.getParentColumn();
                        }else if(cell.getParentColumn() == col){
                            clearColumn = true;
                        }else{
                            clearColumn = false;
                            break;
                        }
                    }
                }
                if(clearColumn){
                    for(Cell c2 : col.getCells()){
                        if(c2.getParentGrid() != cg){
                            c2.eliminatePossibleValue(c);
                        }
                    }
                }
                
                CellGroup row= null;
                boolean clearRow = false;
                for(Cell cell : cg.getCells()){
                    if(cell.getPossibleValues().get(new Integer(c))){
                        if(row == null){
                            row = cell.getParentRow();
                        }else if(cell.getParentRow() == row){
                            clearRow = true;
                        }else{
                            clearRow = false;
                            break;
                        }
                    }
                }
                if(clearRow){
                    for(Cell c2 : row.getCells()){
                        if(c2.getParentGrid() != cg){
                            c2.eliminatePossibleValue(c);
                        }
                    }
                }
                
            }
        }
        
    }
    
    public void solveXWing(){
    	for (int y = 0; y < 8; y++){
    		for(int y1 = y+1; y1 < 9; y1++){
    			solveXWingType(y,y1,ROW);
                solveXWingType(y,y1,COLUMN);
    		}
    	}
    }
    
    
    public void solveXWingType(int y, int y1, int TYPE){
    	CellGroup cg1 = TYPE == ROW ? grid.getRow(y) : grid.getColumn(y);
    	CellGroup cg2 = TYPE == ROW ? grid.getRow(y1) : grid.getColumn(y1);
    	for (int c = 1; c <= 9; c++){
        	List<Integer> cg1Positions = new ArrayList<Integer>();
            List<Integer> cg2Positions = new ArrayList<Integer>();
        	for(int i = 0; i < 9; i++){
        		Integer candidate = new Integer(c);
        		if(cg1.getCells().get(i).getPossibleValues().get(candidate))
                    cg1Positions.add(new Integer(i));
                if(cg2.getCells().get(i).getPossibleValues().get(candidate))
                    cg2Positions.add(new Integer(i));
        	}
        	if (cg1Positions.size() == 2 && cg1Positions.equals(cg2Positions)){
        		for(int groupPos = 0; groupPos < 9; groupPos++){
        		    if(groupPos != y && groupPos != y1){
        	            //System.out.println("found XWING for candidate "+ c +"!" +
        	            //            "("+y+","+cg1Positions.get(0)+"),"+
        	            //            "("+y+","+cg1Positions.get(1)+"),"+
        	            //            "("+y1+","+cg1Positions.get(0)+"),"+
        	            //            "("+y1+","+cg1Positions.get(1)+")"
        	            //);
        		        CellGroup currentGroup = TYPE == ROW ? grid.getRow(groupPos) : grid.getColumn(groupPos);
        		        Cell r = currentGroup.getCells().get(cg1Positions.get(0).intValue());
        		        if(r.getPossibleValues().get(new Integer(c))){
        		            //System.out.println("eliminating "+ c +" from cell at (" + groupPos + ","+ cg1Positions.get(0).intValue() +")");
        		            r.eliminatePossibleValue(c);
        		            //r.attemptSolve();
        		        }
        		        Cell r2 = currentGroup.getCells().get(cg1Positions.get(1).intValue());
                        if(r2.getPossibleValues().get(new Integer(c))){
                            //System.out.println("eliminating "+ c +" from cell at (" + groupPos + ","+ cg1Positions.get(1).intValue() +")");
        		            r2.eliminatePossibleValue(c);
        		            //r.attemptSolve();
        		        }
        		    }
        		    
        		}
        	}
    	}
    }

    public void solveHiddenPairInCellGroup(CellGroup cg){
    	for(int pv1 = 9; pv1 > 1; pv1--){
    		for(int pv2 = pv1 - 1; pv2 > 0; pv2--){
				List<Cell> matchingCells = new ArrayList<Cell>();
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
    }
    
    public long getSolveCount(){
        return this.solveCounter;
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
