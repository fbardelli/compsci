package com.frankbardelli.sudoku;

import java.util.Iterator;
import java.util.List;

public class Runner {
	public static void main(String[] args){
		Grid g = new Grid();
		Solver solver = new Solver(g);
		String sudoku = "200080300" +
						"060070084" +
						"030500209" +
						"000105408" +
						"000000000" +
						"402706000" +
						"301007040" +
						"720040060" +
						"004010003";
		g.parse(sudoku);
		g.print();
	    g.printVerbose();
		int lastCountPossibleValues;
		do {
			lastCountPossibleValues = g.totalCountPossibleValues();
			solver.solveNakedSingles();
			solver.solveHiddenSingles();
		} while( g.totalCountPossibleValues()  < lastCountPossibleValues );
		g.print();
		System.out.println();
		
		Grid g2 = new Grid();
		Solver solver2 = new Solver(g2);
	    g2.parse(sudoku);
	    solver2.solveBacktracking();
	    System.out.println();
	    g2.print();
	    
	    Problems problems = new Problems();
	    List<String> problemList = problems.getProblemList();
	    Iterator<String> pIter = problemList.iterator();
	    int sum = 0;
	    Grid g3 = new Grid();
	    int maxIterations = 0;
	    while(pIter.hasNext()){
	        g3.parse(pIter.next());
	        Solver solver3 = new Solver(g3);
	        //solver3.solveBacktracking();
			int lastCountPossibleValues2;
			long startSeconds = System.currentTimeMillis();
			int iterations = 0;
			do {
				lastCountPossibleValues2 = g3.totalCountPossibleValues();
				solver3.solveNakedSingles();
				solver3.solveHiddenSingles();
				solver3.solveNakedPair();
				solver3.solveHiddenPair();
				solver3.solveNakedTriplet();
				solver3.solvePointingPair();
				solver3.solveXWing();
				iterations++;
			} while( g3.totalCountPossibleValues()  < lastCountPossibleValues2 );
			if (iterations > maxIterations){
				maxIterations = iterations;
			}
	        System.out.println(g3.firstThree());
	        sum += g3.firstThree();
	        g3.print();
	    }
	    System.out.println(sum);
	    System.out.println("max iterations:" + maxIterations);
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