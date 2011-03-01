package com.frankbardelli;

import java.util.ArrayList;

public class JumpCalc {
	private ArrayList<MathOp> jumpTable;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JumpCalc j = new JumpCalc();
		try{
			String[] expression = args[0].split(" ", 3);
			//System.out.println(expression[0] + ':' + expression[1]);
			if(expression.length == 3){
				try{
					int a = Integer.parseInt(expression[0]);
					char op = expression[1].charAt(0);
					int b = Integer.parseInt(expression[2]);
					if (j.isValidOp(op)){
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
	
	public JumpCalc(){
		jumpTable = new ArrayList<MathOp>(256);
		for(int i = 0; i < 256; i++)
			jumpTable.add(i, null);
		jumpTable.set((int)'+', new AddOp());
		jumpTable.set((int)'*', new MultiplyOp());
		jumpTable.set((int)'-', new SubtractOp());
		jumpTable.set((int)'/', new DivideOp());	
	}
	
	public boolean isValidOp(char op){
		return jumpTable.get((int)op) != null;
	}
	
	public float calculate(int a, char op, int b){
		MathOp mop = jumpTable.get((int)op);
		return mop.apply(a,b);
	}
	
	public interface MathOp {
		float apply(int a, int b);
	}
	
	public class AddOp implements MathOp {
		public AddOp(){}
		public float apply(int a, int b){
			return a + b;
		}
	}
	
	public class DivideOp implements MathOp {
		public DivideOp(){}
		public float apply(int a, int b) throws ArithmeticException{
			if (b == 0){
				throw new ArithmeticException();
			}
			return (float)a / (float)b;
		}
	}

	public class MultiplyOp implements MathOp {
		public MultiplyOp(){}
		public float apply(int a, int b){
			return a * b;
		}
	}
	
	public class SubtractOp implements MathOp {
		public SubtractOp(){}
		public float apply(int a, int b){
			return a - b;
		}
	}	

}
