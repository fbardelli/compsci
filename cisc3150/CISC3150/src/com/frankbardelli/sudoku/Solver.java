package com.frankbardelli.sudoku;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

// TODO: Auto-generated Javadoc
/**
 * The Class Solver.
 */
public class Solver {
    private Grid grid;
    private long solveCounter;
    private static int COLUMN = 1;
    private static int ROW = 2;
    
    /**
     * Instantiates a new solver.
     *
     * @param grid Grid object representing the state of the puzzle board
     */
    public Solver(Grid grid){
        this.grid = grid;
        this.solveCounter = 0;
    }
    
    /**
     * Solve cells where only one candidate is available 
     */
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
                        if(c.getValue()!=0){
                            c.setHighlight(true);
                        }
                    }
                }
                
            }
        }
    }
    
    /**
     * Solve cells where one candidate is not possible in any other cell in the same row/box/column
     */
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
    
    /**
     * Solve hidden single in cell group.
     *
     * @param c the Cell to be solved
     * @param cg the CellGroup to examine for hidden singles 
     */
    private void solveHiddenSingleInCellGroup(Cell c, CellGroup cg) {
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
                c.setHighlight(true);
                c.setValue(i.intValue());
            }

        }
        
    }

    /**
     * Find two cells in one cell group with two identical possible values.  Eliminate those possible values
     * in all other cells in the Cell Group.
     */
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
    
    /**
     * Solve naked pair in cell group.
     *
     * @param pValues the values of the pair being examined
     * @param cg the CellGroup
     */
    private void solveNakedPairInCellGroup(HashMap<Integer,Boolean> pValues, CellGroup cg){
    	List<Cell> eliminateCells = new ArrayList<Cell>();
    	List<Cell> candidateCells = new ArrayList<Cell>();
    	for(Cell c: cg.getCells()){
    		if(pValues.equals(c.getPossibleValues())){
    			candidateCells.add(c);
    		}else{
    			eliminateCells.add(c);
    		}
    	}
    	if (candidateCells.size() == 2){
    		for(Cell c: candidateCells){
    			c.setSelected(true);
    		}
    		for(Cell c: eliminateCells){
    			for (Integer i : pValues.keySet()){
    				if(pValues.get(i)){
    				    if(c.getPossibleValues().get(i)){
    				        c.setHighlight(true);
                            c.eliminatePossibleValue(i.intValue());
    				    }
    				}
    			}
    		}
    	}
    }
    
    
    /**
     * Find two cells in one CellGroup that are the only possible candidates for two distinct values.
     * Eliminate all other values in those cells
     */
    public void solveHiddenPair(){
        for(int i=0; i<9; i++){
            solveHiddenPairInCellGroup(grid.getColumn(i));
            solveHiddenPairInCellGroup(grid.getRow(i));
            solveHiddenPairInCellGroup(grid.getBox(i));         
        }
    }
    
    /**
     * Solve hidden pair in cell group.
     *
     * @param cg the Cell Group
     */
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
                            if(c1.getPossibleValues().get(new Integer(i))){
                                c1.setHighlight(true);
                                c1.eliminatePossibleValue(i);
                            }
                            if(c2.getPossibleValues().get(new Integer(i))){
                                c2.setHighlight(true);
                                c2.eliminatePossibleValue(i);
                            }
                        }
                    }
                }
            }
        }
    }
    
    /**
     * Find three cells sharing some combination of 3 distinct values.
     * Eliminate those values in other cells in the same CellGroup
     */
    public void solveNakedTriplet(){
        for(int first = 1; first <= 7; first++){
            for(int second = first + 1; second <= 8; second++ ){
                for (int third = second + 1; third <= 9; third++){
                    for(int i = 0; i < 9; i++){
                        solveNakedTripletInCellGroup(grid.getBox(i),first,second,third);
                        solveNakedTripletInCellGroup(grid.getRow(i),first,second,third);
                        solveNakedTripletInCellGroup(grid.getColumn(i),first,second,third);
                    }
                }
            }
        }
    }
    
    /**
     * Solve using naked triplet technique in a given cell group.
     *
     * @param cg the CellGroup to attempt to solve
     * @param first the first number in the triplet
     * @param second the second number in the triplet 
     * @param third the third number in the triplet
     * @return true, if successful
     */
    public boolean solveNakedTripletInCellGroup(CellGroup cg, int first, int second, int third){
        int bitField = (int) Math.pow(2,first) + (int) Math.pow(2,second) + (int)Math.pow(2,third);
        int bitTotal = 0;
        for(int i = 0; i <= 9; i++){
            bitTotal += (int)Math.pow(2,i);
        }
        List<Cell> eliminateCells = new ArrayList<Cell>();
        List<Cell> candidateCells = new ArrayList<Cell>();
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
                candidateCells.add(c);
            }else{
                eliminateCells.add(c);
            }
        }
        if(candidateCells.size() == 3){
        	for(Cell c: candidateCells){
        		c.setSelected(true);
        	}
            for(Cell c : eliminateCells){
                if (c.getValue() == 0){
                    if(c.getPossibleValues().get(new Integer(first))){
                        c.setHighlight(true);
                        c.eliminatePossibleValue(first);
                    }
                    if(c.getPossibleValues().get(new Integer(second))){
                        c.setHighlight(true);
                        c.eliminatePossibleValue(second);
                    }
                    if(c.getPossibleValues().get(new Integer(third))){
                        c.setHighlight(true);
                        c.eliminatePossibleValue(third);
                    }
                }
            }
            return true;
        }
        return false;
    }
    
    /**
     * In a single box, locate two or three cells in a row/column that share a distinct value.
     * Since that value must occur in the current box, eliminate the value in adjacent
     * boxes along the same row/column 
     */
    public void solvePointingPair(){
        for(int i = 0; i < 9; i ++){
            CellGroup cg = grid.getBox(i);
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
                        if(c2.getParentBox() != cg){
                            if(c2.getPossibleValues().get(new Integer(c))){
                                c2.setHighlight(true);
                                c2.eliminatePossibleValue(c);
                            }
                        }else{
                        	c2.setSelected(true);
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
                        if(c2.getParentBox() != cg){
                            if(c2.getPossibleValues().get(new Integer(c))){
                                c2.setHighlight(true);
                                c2.eliminatePossibleValue(c);
                            }
                        }else{
                        	c2.setSelected(true);
                        }
                    }
                }
                
            }
        }
        
    }
    
    /**
     * Match up all rows into pairs.  If a single value occurs twice in the same column position in both rows,
     * that value can be eliminated for that column position in all other rows
     * Repeat this technique for each pair of columns
     */
    public void solveXWing(){
    	for (int y = 0; y < 8; y++){
    		for(int y1 = y+1; y1 < 9; y1++){
    			solveXWingType(y,y1,ROW);
                solveXWingType(y,y1,COLUMN);
    		}
    	}
    }
    
    
    /**
     * Solve x wing type.
     *
     * @param y the position of the first row/column in the grid
     * @param y1 the position of the second row/column in the grid
     * @param TYPE constant representing whether we are operating on rows or columns
     */
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
        		cg1.getCells().get(cg1Positions.get(0)).setSelected(true);
        		cg1.getCells().get(cg1Positions.get(1)).setSelected(true);
        		cg2.getCells().get(cg2Positions.get(0)).setSelected(true);
        		cg2.getCells().get(cg2Positions.get(1)).setSelected(true);
        		for(int groupPos = 0; groupPos < 9; groupPos++){
        		    if(groupPos != y && groupPos != y1){
        		        CellGroup currentGroup = TYPE == ROW ? grid.getRow(groupPos) : grid.getColumn(groupPos);
        		        Cell r = currentGroup.getCells().get(cg1Positions.get(0).intValue());
        		        if(r.getPossibleValues().get(new Integer(c))){
        		            r.setHighlight(true);
            		        r.eliminatePossibleValue(c);
        		        }
        		        Cell r2 = currentGroup.getCells().get(cg1Positions.get(1).intValue());
                        if(r2.getPossibleValues().get(new Integer(c))){
                            r2.setHighlight(true);
        		            r2.eliminatePossibleValue(c);
        		        }
        		    }
        		    
        		}
        	}
    	}
    }


    /**
     * Gets the solve count.
     *
     * @return the solve count
     */
    public long getSolveCount(){
        return this.solveCounter;
    }
    
    
    /* Based on Bob Carpenters backtracking sudoku solver 
     * http://www.colloquial.com/games/sudoku/java_sudoku.html
     */
    /**
     * Solve entire puzzle using brute force recursive backtracking technique.
     */
    public void solveBacktracking(){
    	this.solveCounter = 0;
        if(! solveBT(0,0)){
            System.out.println("Failed to solve Puzzle");
        }
    }
    

    
    /**
     * Solve 
     *
     * @param y the y coordinate of the cell to solve 
     * @param x the x coordinate of the cell to solve 
     * @return true, if solved successfully
     */
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
            if (isLegal(y,x,val)) {
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
    
    /**
     * Is the value of the cell identified by (x,y) legal?
     *
     * @param y the y coordinate of the current cell on the grid
     * @param x the x coordinate of the current cell on the grid
     * @param val the value of the cell
     * @return true, if valid.  False otherwise
     */
    private boolean isLegal(int y, int x, int val) {
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
