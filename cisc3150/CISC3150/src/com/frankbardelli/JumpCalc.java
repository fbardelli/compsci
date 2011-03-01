/* Frank Bardelli
 * CISC 3150 Assignment #3 JumpTable calculator
 * February 22, 2010
 */
package com.frankbardelli;

import java.util.ArrayList;

public class JumpCalc {
	
	private ArrayList<MathOp> jumpTable;
	
	/**
	 * The main method.
	 *
	 * @param args command line arguments
	 */
	public static void main(String[] args) {
		JumpCalc j = new JumpCalc();
		try{
		    /* Split first command line argument,
		     * this program expects input in a quoted string,
		     * this avoids shell expansion of "*" which is a wildcard in bash
		     */
			String[] expression = args[0].split(" ", 3);
			if(expression.length == 3){
				try{
				    /* Parse input expression */
					int a = Integer.parseInt(expression[0]);
					char op = expression[1].charAt(0);
					int b = Integer.parseInt(expression[2]);
					if (j.isValidOp(op)){
					    /* Calculate answer and print it */ 
						System.out.println(j.calculate(a, op, b));
					}else{
						System.err.println("invalid operator");
					}
				}catch(NumberFormatException e){
					System.err.println("Error: integer expected");
				}catch(ArithmeticException e){
					System.err.println("Error: divide by zero attempted");
				}
			}else{
				System.err.println("This program requires 3 arguments");
			}
		}catch(ArrayIndexOutOfBoundsException e){
			System.err.println("invalid expression.");
		}		
	}
	
	/**
	 * Instantiates a new jump calc object with the ability to parse simple
	 * Mathematic expressions
	 */
	public JumpCalc(){
		jumpTable = new ArrayList<MathOp>(256);
		for(int i = 0; i < 256; i++)
			jumpTable.add(i, null);
		jumpTable.set((int)'+', new AddOp());
		jumpTable.set((int)'*', new MultiplyOp());
		jumpTable.set((int)'-', new SubtractOp());
		jumpTable.set((int)'/', new DivideOp());	
	}
	
	/**
	 * Checks if character represents a valid operation.
	 *
	 * @param op the op
	 * @return true, if is valid op
	 */
	public boolean isValidOp(char op){
		return jumpTable.get((int)op) != null;
	}
	
	/**
	 * Calculate the expression supplied using a jump table to resolve
	 * the operator
	 *
	 * @param left the operand on the left side of the expression
	 * @param op character representing the math operation to apply
	 * @param right the operand on the right side of the expression
	 * @return the result of operation op on operands
	 */
	public float calculate(int left, char op, int right){
		MathOp mop = jumpTable.get((int)op);
		return mop.apply(left,right);
	}
	
	/**
	 * Generic Math Operation Interface
	 */
	public interface MathOp {
		
		/**
		 * Apply.
		 *
		 * @param left the operand on the left side of the expression
		 * @param right the operand on the right side of the expression
		 * @return the result of performing this MathOp on the arguments supplied
		 */
		float apply(int left, int right);
	}
	
	/**
	 * Add Operation
	 */
	public class AddOp implements MathOp {
		
		/**
		 * Instantiates a new add operation
		 */
		public AddOp(){}
		
		/* (non-Javadoc)
		 * @see com.frankbardelli.JumpCalc.MathOp#apply(int, int)
		 */
		public float apply(int left, int right){
			return left + right;
		}
	}
	
	/**
	 * Divide Operation
	 */
	public class DivideOp implements MathOp {
		
		/**
		 * Instantiates a new divide operation
		 */
		public DivideOp(){}
		
		/* (non-Javadoc)
		 * @see com.frankbardelli.JumpCalc.MathOp#apply(int, int)
		 */
		public float apply(int left, int right) throws ArithmeticException{
			if (right == 0){
				throw new ArithmeticException();
			}
			return (float)left / (float)right;
		}
	}

	/**
	 * Multiplication Operation
	 */
	public class MultiplyOp implements MathOp {
		
		/**
		 * Instantiates a new multiply operation
		 */
		public MultiplyOp(){}
		
		/* (non-Javadoc)
		 * @see com.frankbardelli.JumpCalc.MathOp#apply(int, int)
		 */
		public float apply(int left, int right){
			return left * right;
		}
	}
	
	/**
	 * Subtraction operation
	 */
	public class SubtractOp implements MathOp {
		
		/**
		 * Instantiates a new subtraction operation
		 */
		public SubtractOp(){}
		
		/* (non-Javadoc)
		 * @see com.frankbardelli.JumpCalc.MathOp#apply(int, int)
		 */
		public float apply(int left, int right){
			return left - right;
		}
	}
}