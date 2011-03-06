package com.frankbardelli.bf;

import static org.junit.Assert.*;

import java.io.ByteArrayInputStream;

import org.junit.Before;
import org.junit.Test;

public class InterpreterTest {
	Interpreter bf;
	@Before
	public void setUp() throws Exception {
		bf = new Interpreter();
	}

	@Test
	public void testHelloWorld() {
		String helloWorldBF = 	"++++++++++" +
		"[>+++++++>++++++++++>+++>+<<<<-]" +
		">++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++."+
		"------.--------.>+.>.";
		String hwOutput = bf.parse(helloWorldBF);
		assertEquals("Hello World!\n",hwOutput);
	}

	@Test
	public void testPowersOfTwo(){
		String pow = "++[>++[>++[>++<-]<-]<-]>>>.";
		String powOut = bf.parse(pow);
		assertEquals((int)Math.pow(2.0,4.0),(int)powOut.charAt(0));
	}

	@Test	
	public void testAdder(){
		String adder = 	", store first number in cell 0" +
		">,store 2nd number in cell 1" +
		"[<+>-] increment first number while subtracting second number toward 0" + 
		"<. output number in cell 0";
		int firstNumber = 5, secondNumber = 9;
		char data[] ={(char)firstNumber,(char)secondNumber};
		String input = new String(data);
		ByteArrayInputStream operands = new ByteArrayInputStream(input.getBytes());
		String adderOut = bf.parse(adder,operands);
		assertEquals(firstNumber + secondNumber,(int)adderOut.charAt(0));
	}

	@Test
	public void testMultiply(){
		String multi = 	",>,< Store operands in cell 0 and 1"+
		"[ while cell 0 is greater than 0" + 
		">[>+ add cell 1 to cell 2" +
		">+<<-]  add cell 1 to cell 3 empting cell 1" +
		">>[<<+>>-] move value in cell 3 to cell 1" +
		"<<<-] decrement cell 0" +
		">>. output cell 2";
		int firstNumber = 5, secondNumber = 9;
		char data[] ={(char)firstNumber,(char)secondNumber};
		String input = new String(data);
		ByteArrayInputStream operands = new ByteArrayInputStream(input.getBytes());
		String multiOut = bf.parse(multi,operands);
		assertEquals(firstNumber * secondNumber,(int)multiOut.charAt(0));
	}

}
