package com.frankbardelli.sudoku;
import java.util.HashMap;

public class Cell {
	int value;
	boolean[] possibleValues;
	CellGroup parentGrid;	
	CellGroup parentRow;
	CellGroup parentColumn;
	public Cell(){
		initializePossibleValues();
		value = 0;
	}
	
	public Cell(int value){
		initializePossibleValues();
		setValue(value);
	}
	
	public void clear(){
		initializePossibleValues();
	}
	
	private void initializePossibleValues(){
		possibleValues = new boolean[9];		
		for( int i = 0; i < 9; i++ ){
			possibleValues[i] = true;
		}
	}
	
	public void eliminatePossibleValue(int i){
		if (i <= 9) {
			possibleValues[i-1] = false;
		}
	}
	
	public void attemptSolve(){
		int lastTrue = 0;
		int totalTrue = 0;
		for(int i = 0; i < possibleValues.length; i++){
			boolean b = possibleValues[i];
			if(b){
				lastTrue = i;
				totalTrue++;
			}
		}
		if (totalTrue == 1 ){
			this.setValue(lastTrue+1);
		}
	}
	
	
	public void setValue(int value){
		this.value = value;
		if(value > 0){
    		for( int i = 0; i < 9; i++ ){
    			possibleValues[i] = ( (i+1) == value ? true : false );
    		}
    		parentGrid.solve(value);
    		parentRow.solve(value);
    		parentColumn.solve(value);
		}
	}
	
	public HashMap<Integer,Boolean> getPossibleValues(){
		HashMap<Integer,Boolean> values = new HashMap<Integer,Boolean>();
		for( int i = 0; i < 9; i++ ){
			values.put(new Integer(i+1), new Boolean(possibleValues[i]));
		}
		return values;
	}
	
	public int getPossibleValueCount(){
		int pvCount = 0;
		for ( boolean b : possibleValues ){
			if(b){
				pvCount++;
			}
		}
		return pvCount;
	}
	
	public boolean possibleValuesMatch(Cell c2){
		return this.getPossibleValues().equals(c2.getPossibleValues());
	}
	
	public int getValue(){
		return value;
	}
	
	public CellGroup getParentGrid() {
		return parentGrid;
	}
	public void setParentGrid(CellGroup parentGrid) {
		this.parentGrid = parentGrid;
	}
	public CellGroup getParentRow() {
		return parentRow;
	}
	public void setParentRow(CellGroup parentRow) {
		this.parentRow = parentRow;
	}
	public CellGroup getParentColumn() {
		return parentColumn;
	}
	public void setParentColumn(CellGroup parentColumn) {
		this.parentColumn = parentColumn;
	}
}
