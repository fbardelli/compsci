package com.frankbardelli.bf;

import java.io.ByteArrayInputStream;

public class cli {

	public static void main(String[] args) {
		Interpreter bfInterpreter = new Interpreter();
		String inputType = System.getProperty("in");
		String outputType = System.getProperty("out");
		if(args.length > 0){
			String program = args[0];
			String output;
			if(args.length == 1){
				output =  bfInterpreter.parse(program);
			}else if (args.length > 1){
				String input = "";
				if (inputType.equals("int")){
					for (int i = 1; i <= args.length; i ++ ){
						input = input.concat(
							Character.toString(
								(char) Integer.parseInt(args[i])
							)
						);
					}
				} else {
					input = args[1];
				}
				output = bfInterpreter.parse(
						program, 
						new ByteArrayInputStream(input.getBytes())
				);
				System.out.println(program);
			}
		}else{
			System.err.println("invalid number of arguments");
		}

	}

}
// ,>,[<+>-]<.