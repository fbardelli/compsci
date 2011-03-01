package com.frankbardelli.sudoku;

public class Runner {
	public static void main(String[] args){
		Grid g = new Grid();
		String sudoku = "200080300\n" +
						"060070084\n" +
						"030500209\n" +
						"000105408\n" +
						"000000000\n" +
						"402706000\n" +
						"301007040\n" +
						"720040060\n" +
						"004010003";
		g.parse(sudoku);
		g.print();
	    g.printVerbose();
		int lastCountPossibleValues = g.totalCountPossibleValues();
		g.solveNakedSingles();
		g.solveHiddenSingles();
		while( g.totalCountPossibleValues()  < lastCountPossibleValues ){
			lastCountPossibleValues = g.totalCountPossibleValues();
			g.solveNakedSingles();
			g.solveHiddenSingles();
		}
		g.print();
	}

}

/*

245|981|376
169|273|584
837|564|219
-----------
976|125|438
513|498|627
482|736|951
-----------
391|657|842
728|349|165
654|812|793

*/