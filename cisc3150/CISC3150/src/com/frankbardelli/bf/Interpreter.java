package com.frankbardelli.bf;

import java.io.IOException;
import java.io.InputStream;

public class Interpreter {
	private String program;
	private int programPointer;
	private int localLoopStartPoint;
	private Runtime runtime;
	private String output;
	
	public Interpreter(String p){
		runtime = new Runtime();
		initialize(p,runtime);		
	}
	
	public Interpreter(String p, Runtime r){
		initialize(p,r);
	}
	
	public Interpreter(String p, Runtime r, InputStream i){
		initialize(p,r);
	}
	
	private void initialize(String p, Runtime r){
		InputStream in  = System.in;
		initialize(p, r, in);
	}
	
	private void initialize(String p, Runtime r, InputStream i){
		program = p;
		programPointer = 0;
		localLoopStartPoint = 0;
		runtime = r;
		output = "";
	}
	
	public String parse(){
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
						int i = System.in.read();
						runtime.putCellValue((char)i);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					break;
				case '[':
					int stackFrames = 0;
					localLoopStartPoint = programPointer + 1;
					int loopEndPoint = localLoopStartPoint;
					while(stackFrames > 0){
						loopEndPoint++;
						char next = program.charAt(loopEndPoint);
						if( next == '['){
							stackFrames++;
						}else if (next == ']'){
							stackFrames--;
						}
					}
					if(runtime.getCellValue() != (char)0){
						if (localLoopStartPoint < loopEndPoint){
							new Interpreter(program.substring(localLoopStartPoint, loopEndPoint-1),runtime).parse();
						}
					}else{
						programPointer = loopEndPoint;
					}
					break;
				case ']':
					if(runtime.getCellValue() != (char)0){
						programPointer = localLoopStartPoint-1;
					}
					break;
			}
			programPointer++;
		}
		return output;
	}

}
