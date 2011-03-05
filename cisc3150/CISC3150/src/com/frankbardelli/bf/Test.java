package com.frankbardelli.bf;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String helloWorldBF = 	"++++++++++" +
								"[>+++++++>++++++++++>+++>+<<<<-]" +
								">++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++."+
								"------.--------.>+.>.";
		Interpreter bf = new Interpreter(helloWorldBF);
		String bfOutput = bf.parse();
		System.out.println(bfOutput);

	}
}
