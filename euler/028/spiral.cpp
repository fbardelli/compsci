/*Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

5x5 = 25

2,2     3,2     3,3     2,3     1,3     1,2     1,1     2,1     3,1
4,1     4,2     4,3     4,4     3,4     2,4     1,4     0,4     0,3     0,2     0,1     0,0     1,0     2,0     3,0     4,0
It can be verified that the sum of the numbers on the diagonals is 101.

(at center)
right 1 (passed center/diagonal x-1)
down 1 (at a digonal)
left 2 (at a diagonal)
up 2   (at a diagonal)
right 3 (passed a diagonal x-1) 
down 3  (at a diagonal)
left 4  (at a diagonal)
up 4    (at a diagonal)
right 4 (or 5 if we continue passing a diagonal x-1)
down 5  (at a diagonal)
left 6  (at a diagonal)
up 6    (at a diagonal)

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/
