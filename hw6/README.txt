HOMEWORK 6: BATTLESHIP RECURSION
//unknowns loop outside in main, not rec

NAME:  Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
Cavell Teng
www.stackoverflow.com
www.cplusplus.com


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 10


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
The dimensions of the board (w and h) 
The number of ships (s)
The total number of occupied cells (o) or open water (w)
The number of constraints (c)
The number of unknown sums (u) or unspecified ship types (t)
The number of solutions (n)

READING
Starts by reading data and ships from file (O(s)) and stores it. Sorts ships (O(slogs)). Makes empty grid (O(h)). Determines whether to find one or all solutions before calling recursive function(O(1)).

RECURSION
At base case, it determines if we are finding all solutions or not (O(1)). If not, it adds the grid, row, column, and ship data as a solution and ends recursion. If looking for all solutions it first checks if solution is unique before adding it. In both cases, it checks that the solution satisfies the constraints (O(c)) and that the row/col values match (O(w+h)) before adding it.

Outside of base case, it checks each cell one by one (O(w*h)) if a ship can be placed hor/ver in that cell. If the ship is unknown, it loops the recursion process 7 times for each unknown ship (O(t)).

It checks horizontal placing first, then vertical. If a ship can be placed, it saves current grid, row, and col data. It then modifies the grid and row/col data to “place” the ship onto the grid and then calls recursive function again. After the recursive call (which means current pathway failed), it revives the old grid, row, and col data.

UNKNOWN SUMS
Before adding the row and col solutions in the base case, it checks through the whole vector for any “?” (negative number in my code) and transforms it into the real value based on the grid (O(w+h)).

PRINTING
Changes grid characters to look nice (O(w*h)) before printing it.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:

- single solution -
puzzle1: 0 sec
puzzle2: 0 sec
puzzle3: 0 sec
puzzle4: 0 sec
puzzle5: 0 sec
puzzle6: 0 sec
puzzle7: 0 sec
puzzle8: 0 sec
puzzle9: 0 sec
puzzle10: 0 sec
puzzle4_unknowns: 10 min
puzzle6_unknowns: 0 sec
puzzle9_constraints: 20 sec
puzzle10_constraints: 10 min

- find_all_solutions -
puzzle1: 0 sec Found 1 solution
puzzle2: 0 sec Found 1 solution
puzzle3: 0 sec Found 1 solution
puzzle4: 0 sec Found 1 solution
puzzle5: 0 sec Found 2 solutions
puzzle6: 0 sec Found 24 solutions
puzzle7: 1 sec Found 14 solutions
puzzle8: 40 sec Found 2 solutions
puzzle9: 40 sec Found 152 solutions
puzzle6_unknowns: 0 sec Found 24 Solutions