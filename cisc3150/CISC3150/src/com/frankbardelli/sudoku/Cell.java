package com.frankbardelli.sudoku;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

// TODO: Auto-generated Javadoc
/**
 * The Class Cell.
 */
public class Cell {
	
	/** The value. */
	int value;
	
	/** The possible values. */
	boolean[] possibleValues;
	
	/** The parent grid. */
	CellGroup parentGrid;	
	
	/** The parent row. */
	CellGroup parentRow;
	
	/** The parent column. */
	CellGroup parentColumn;
	
	/**
	 * Instantiates a new cell.
	 */
	public Cell(){
		initializePossibleValues();
		value = 0;
	}
	
	/**
	 * Instantiates a new cell.
	 *
	 * @param value the value
	 */
	public Cell(int value){
		initializePossibleValues();
		setValue(value);
	}
	
	/**
	 * Clear.
	 */
	public void clear(){
		initializePossibleValues();
	}
	
	/**
	 * Initialize possible values.
	 */
	private void initializePossibleValues(){
		possibleValues = new boolean[9];		
		for( int i = 0; i < 9; i++ ){
			possibleValues[i] = true;
		}
	}
	
	/**
	 * Eliminate possible value.
	 *
	 * @param i the i
	 */
	public void eliminatePossibleValue(int i){
		if (i <= 9) {
			possibleValues[i-1] = false;
		}
	}
	
	/**
	 * Attempt solve.
	 */
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
	
	
	/**
	 * Sets the value.
	 *
	 * @param value the new value
	 */
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
	
	/**
	 * Gets the possible values.
	 *
	 * @return the possible values
	 */
	public HashMap<Integer,Boolean> getPossibleValues(){
		HashMap<Integer,Boolean> values = new HashMap<Integer,Boolean>();
		for( int i = 0; i < 9; i++ ){
			values.put(new Integer(i+1), new Boolean(possibleValues[i]));
		}
		return values;
	}
	
	/**
	 * Gets the possible value count.
	 *
	 * @return the possible value count
	 */
	public int getPossibleValueCount(){
		int pvCount = 0;
		for ( boolean b : possibleValues ){
			if(b){
				pvCount++;
			}
		}
		return pvCount;
	}
	
	/**
	 * Possible values match.
	 *
	 * @param c2 the c2
	 * @return true, if successful
	 */
	public boolean possibleValuesMatch(Cell c2){
		return this.getPossibleValues().equals(c2.getPossibleValues());
	}
	
	/**
	 * Gets the value.
	 *
	 * @return the value
	 */
	public int getValue(){
		return value;
	}
	
	/**
	 * Gets the parent grid.
	 *
	 * @return the parent grid
	 */
	public CellGroup getParentGrid() {
		return parentGrid;
	}
	
	/**
	 * Sets the parent grid.
	 *
	 * @param parentGrid the new parent grid
	 */
	public void setParentGrid(CellGroup parentGrid) {
		this.parentGrid = parentGrid;
	}
	
	/**
	 * Gets the parent row.
	 *
	 * @return the parent row
	 */
	public CellGroup getParentRow() {
		return parentRow;
	}
	
	/**
	 * Sets the parent row.
	 *
	 * @param parentRow the new parent row
	 */
	public void setParentRow(CellGroup parentRow) {
		this.parentRow = parentRow;
	}
	
	/**
	 * Gets the parent column.
	 *
	 * @return the parent column
	 */
	public CellGroup getParentColumn() {
		return parentColumn;
	}
	
	/**
	 * Sets the parent column.
	 *
	 * @param parentColumn the new parent column
	 */
	public void setParentColumn(CellGroup parentColumn) {
		this.parentColumn = parentColumn;
	}
	
	/**
	 * Gets the cell groups.
	 *
	 * @return the cell groups
	 */
	public List<CellGroup> getCellGroups(){
		List<CellGroup> cellGroups = new ArrayList<CellGroup>();
		cellGroups.add(parentColumn);
		cellGroups.add(parentRow);
		cellGroups.add(parentGrid);
		return cellGroups;
	}
}
