package com.frankbardelli.bf;

import java.io.IOException;
import java.io.InputStream;

public class Interpreter {
	
	/** The bf runtime object. */
	private Runtime runtime;
	
	/** The output of the program. */
	private String output;
	
	/** The input stream, defaults to standard input. */
	private InputStream input;
	
	/**
	 * Instantiates a new interpreter.
	 */
	public Interpreter(){
		initialize();
	}
	
	/**
     * Initialize bf interpreter.
	 */
	private void initialize(){
		runtime = new Runtime();
		initialize(runtime);		
	}
	
	/**
	 * Initialize bf program variables.
	 *
	 * @param r the bf runtime object
	 */
	private void initialize(Runtime r){
		input =  System.in;
		runtime = r;
		output = "";
	}
	
	/**
	 * Parses the program with an alternate input stream, allowing for non interactive I/O.
	 *
     * @param program the bf program as a string
	 * @param in the input stream
     * @return the output of the program
	 */
	public String parse(String p, InputStream in){
		/* temporarily use an alternate Input Stream */
		InputStream lastInput = input;
		input = in;
		String out = parse(p);
		input = lastInput;
		return out;	
	}
	
	/**
	 * Parses and executes the brainf**k program supplied.
	 *
	 * @param program the bf program as a string
	 * @return the output of the program
	 */
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
					output = output.concat(
					    Character.toString(runtime.getCellValue())
					);
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
							parse(
							    program.substring(localLoopStartPoint, loopEndPoint)
							);
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