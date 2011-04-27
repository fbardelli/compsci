package com.frankbardelli.sudoku;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

// TODO: Auto-generated Javadoc
/**
 * The Class Cell.
 */
public class Cell {
	private int value;
	private boolean[] possibleValues;
	private CellGroup parentBox;	
	private CellGroup parentRow;
	private CellGroup parentColumn;
	private boolean highlight;
	private boolean selected;
	
	/**
	 * Instantiates a new cell.
	 */
	public Cell(){
		initializePossibleValues();
		value = 0;
		highlight = false;
		selected = false;
	}
	
	/**
	 * Gets the selected state of the Cell.
	 *
	 * @return the selected state
	 */
	public boolean getSelected() {
		return selected;
	}

	/**
	 * Sets the selected state of the cell.
	 *
	 * @param selected the new selected state
	 */
	public void setSelected(boolean selected) {
		this.selected = selected;
	}

	/**
	 * Instantiates a new cell with a given value
	 *
	 * @param value the solved value of the cell
	 */
	public Cell(int value){
		initializePossibleValues();
		setValue(value);
	}
	
	/**
	 * Clear the cell, setting it to unsolved and opening up all possible values
	 */
	public void clear(){
		initializePossibleValues();
	}
	
	/**
	 * Initialize list of possible values.
	 */
	private void initializePossibleValues(){
		possibleValues = new boolean[9];		
		for( int i = 0; i < 9; i++ ){
			possibleValues[i] = true;
		}
	}
	
	/**
	 * Eliminate a possible value from the Cell.
	 *
	 * @param i the value to eliminate
	 */
	public void eliminatePossibleValue(int i){
		if (i <= 9) {
			possibleValues[i-1] = false;
		}
	}
	
	/**
	 * Attempt to solve the cell.  If the list of possible values contains just one candidate the cell can be solved
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
	 * Gets the cell's highlighting state.
	 *
	 * @return boolean representing if the cell is highlighted
	 */
	public boolean getHighlight(){
        return highlight;
	}
	
	 /**
 	 * Sets the cells highlighting.  Useful for interactively showing solving progress.
 	 *
 	 * @param h boolean representing if the cell is highlighted
 	 */
 	public void setHighlight(boolean h){
	     highlight = h;
	 } 
	
	/**
	 * Sets the value of the cell, eliminating that value from all cell groups the cell is a member of
	 *
	 * @param value the new value
	 */
	public void setValue(int value){
		this.value = value;
		if(value > 0){
    		for( int i = 0; i < 9; i++ ){
    			possibleValues[i] = ( (i+1) == value ? true : false );
    		}
    		parentBox.solve(value);
    		parentRow.solve(value);
    		parentColumn.solve(value);
		}
	}
	
	/**
	 * Gets the possible values for this cell.
	 *
	 * @return Hashmap of all possible values for this cell, true for possible values, false for eliminated values
	 */
	public HashMap<Integer,Boolean> getPossibleValues(){
		HashMap<Integer,Boolean> values = new HashMap<Integer,Boolean>();
		for( int i = 0; i < 9; i++ ){
			values.put(new Integer(i+1), new Boolean(possibleValues[i]));
		}
		return values;
	}
	
	/**
	 * Gets the count of possible values for this cell.
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
	 * Test to determine if the possible values in this cell exactly match those of the Cell supplied.
	 *
	 * @param c2 Cell object
	 * @return true, if possible values are identical
	 */
	public boolean possibleValuesMatch(Cell c2){
		return this.getPossibleValues().equals(c2.getPossibleValues());
	}
	
	/**
	 * Gets the value of this Cell, 1-9 if solved.  0 if unsolved.
	 *
	 * @return value
	 */
	public int getValue(){
		return value;
	}
	
	/**
	 * Gets the parent 3x3 Box this cell belongs to.
	 *
	 * @return the parent box
	 */
	public CellGroup getParentBox() {
		return parentBox;
	}
	
	/**
	 * Sets the parent 3x3 Box.
	 *
	 * @param parentBox the new parent box
	 */
	public void setParentBox(CellGroup parentBox) {
		this.parentBox = parentBox;
	}
	
	/**
	 * Gets the parent row this cell belongs to.
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
	 * Gets the parent column this cell belongs to.
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
	 * Gets the CellGroups(row,column,box) this cell belongs to.
	 *
	 * @return List of the CellGroups
	 */
	public List<CellGroup> getCellGroups(){
		List<CellGroup> cellGroups = new ArrayList<CellGroup>();
		cellGroups.add(parentColumn);
		cellGroups.add(parentRow);
		cellGroups.add(parentBox);
		return cellGroups;
	}
}
