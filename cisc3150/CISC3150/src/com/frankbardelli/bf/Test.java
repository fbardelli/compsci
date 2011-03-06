package com.frankbardelli.bf;

import java.io.ByteArrayInputStream;

public class Test {

	public static void main(String[] args) {
		String helloWorldBF = 	"++++++++++" +
								"[>+++++++>++++++++++>+++>+<<<<-]" +
								">++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++."+
								"------.--------.>+.>.";
		Interpreter bf = new Interpreter();
		String hwOutput = bf.parse(helloWorldBF);
		System.out.print(hwOutput);
		
		bf = new Interpreter();
		String adder = 	"Test of adder program containing comments" +
						", store first number in cell 0" +
						">,store 2nd number in cell 1" +
						"[<+>-] increment first number while subtracting second number toward 0" + 
						"<. output number in cell 0";
		String input = Character.toString((char)5) + Character.toString((char)9); 
		ByteArrayInputStream operands = new ByteArrayInputStream(input.getBytes());
		String adderOut = bf.parse(adder,operands);
		System.out.println((int)adderOut.charAt(0));
	}
}
