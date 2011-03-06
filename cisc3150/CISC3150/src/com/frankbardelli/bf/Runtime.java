package com.frankbardelli.bf;

import java.util.Arrays;

public class Runtime {
	private int MAX_MEMORY_SIZE = 30000;	
	/** The memory array for the bf program. */
	private char[] memory;
	/** The current pointer position. */
	private int currentPosition;
	
	/**
	 * Instantiates a new runtime.
	 */
	public Runtime(){
		memory = new char[MAX_MEMORY_SIZE];
		Arrays.fill(memory, (char)0);
		currentPosition = 0;
	}
	
	/**
	 * Move pointer forward
	 */
	public void incrementPointer(){
		++currentPosition;
	}
	
	/**
	 * Move pointer backward
	 */
	public void decrementPointer(){
		--currentPosition;
	}
	
	/**
	 * Increment value in the cell at pointer
	 */
	public void incrementCell(){
		++memory[currentPosition];
	}
	
    /**
     * Decrement value in the cell at pointer
     */
	public void decrementCell(){
		--memory[currentPosition];
	}
	
	/**
	 * Return the cell value at the current pointer position.
	 *
	 * @return cell value as a character 
	 */
	public char getCellValue(){
		return memory[currentPosition];
	}
	
	/**
	 * Put value supplied in the cell at the current pointer.
	 *
	 * @param c character value to insert
	 */
	public void putCellValue(char c){
		memory[currentPosition] = c;
	}
	
    /**
     * Show a section of memory for debugging purposes.
     *
     * @param start the start point of the memory array range
     * @param end the end point of the memory array range
     */
    public void showBuffer(int start, int end){
    	for(int i = start; i <= end; i++){
    		if(currentPosition == i){
    		    System.out.print("["+ (int)memory[i]+"]");    			
    		}else{
    		    System.out.print(" "+ (int)memory[i]+" ");
    		}
    	}
    	System.out.println();
    }

}