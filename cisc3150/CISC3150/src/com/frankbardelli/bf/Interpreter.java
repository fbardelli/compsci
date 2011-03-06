package com.frankbardelli.bf;

import java.io.IOException;
import java.io.InputStream;

public class Interpreter {
	private Runtime runtime;
	private String output;
	private InputStream input;
	
	public Interpreter(){
		initialize();
	}
	
	private void initialize(){
		runtime = new Runtime();
		initialize(runtime);		
	}
	
	private void initialize(Runtime r){
		input =  System.in;
		runtime = r;
		output = "";
	}
	
	public String parse(String p, InputStream i){
		/* temporarily use an alternate Input Stream */
		InputStream lastInput = input;
		input = i;
		String out = parse(p);
		input = lastInput;
		return out;	
	}
	
	public String parse(String program){
		int programPointer = 0;
		while (programPointer < program.length()){
			char op = program.charAt(programPointer);
			switch (op){
				case '>':
					runtime.incrementPointer();
					break;
				case '<':
					runtime.decrementPointer();
					break;
				case '+':
					runtime.incrementCell();
					break;
				case '-':
					runtime.decrementCell();
					break;
				case '.':
					output = output.concat(Character.toString(runtime.getCellValue()));
					break;
				case ',':
					try {
						int i = input.read();
						runtime.putCellValue((char)i);
					} catch (IOException e) {
						e.printStackTrace();
					}
					break;
				case '[':
					int braces = 1;
					int localLoopStartPoint = programPointer + 1;
					int loopEndPoint = localLoopStartPoint;
					/* find matching end bracket */
					do {
						loopEndPoint++;
						char next = program.charAt(loopEndPoint);
						if( next == '['){
							braces++;
						}else if (next == ']'){
							braces--;
						}
					}while(braces > 0);
					if(runtime.getCellValue() != (char)0){
						if (localLoopStartPoint < loopEndPoint){
							/* parse everything between the matching brackets */
							parse(program.substring(localLoopStartPoint, loopEndPoint));
						}
					}else{
						/* advance past end brace */
						programPointer = loopEndPoint+1;
					}
					break;
				case ']':
					/* loop back if current cell is not 0 */					
					if(runtime.getCellValue() != (char)0){
						int loopStartPoint = programPointer;
						/* find matching end bracket */
						braces = 1;
						do {
							loopStartPoint--;
							char next = program.charAt(loopStartPoint);
							if( next == '['){
								braces--;
							}else if (next == ']'){
								braces++;
							}
						}while(braces > 0);
						programPointer = loopStartPoint;
					}
					break;
			}
			programPointer++;
		}
		return output;
	}
}