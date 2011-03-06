package com.frankbardelli.bf;

import java.util.Arrays;

public class Runtime {
	private int MAX_MEMORY_SIZE = 30000;
	private char[] memory;
	private int currentPosition;
	
	public Runtime(){
		memory = new char[MAX_MEMORY_SIZE];
		Arrays.fill(memory, (char)0);
		currentPosition = 0;
	}
	
	public void incrementPointer(){
		++currentPosition;
	}
	
	public void decrementPointer(){
		--currentPosition;
	}
	
	public void incrementCell(){
		++memory[currentPosition];
	}
	
	public void decrementCell(){
		--memory[currentPosition];
	}
	
	public char getCellValue(){
		return memory[currentPosition];
	}
	
	public void putCellValue(char c){
		memory[currentPosition] = c;
	}
	
    public void showBuffer(int cellStart, int cellEnd){
    	for(int i = cellStart; i <= cellEnd; i++){
    		if(currentPosition == i){
    		    System.out.print("["+ (int)memory[i]+"]");    			
    		}else{
    		    System.out.print(" "+ (int)memory[i]+" ");
    		}
    	}
    	System.out.println();
    }

}