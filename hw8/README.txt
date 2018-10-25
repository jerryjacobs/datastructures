HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
www.cplusplus.com
Kareem El-Faramawi


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed (beyond the space allocated for the existing tree structure).
You may assume that the tree is reasonably well balanced for all operations.
n = the number of elements in the tree


size()
  running time: 1
  memory usage: 1

insert() - searches down the tree  (log base 4)
  running time: log n
  memory usage: 1

find() - simply searches through tree just like insert (log base 4)
  running time: log n
  memory usage: 1

height() - searches through entire tree and compares depth
  running time: n
  memory usage: 1

begin()
  running time: 1
  memory usage: 1

end()
  running time: 1
  memory usage: 1

bf_begin()
  running time: 1
  memory usage: 1

bf_end()
  running time: 1
  memory usage: 1

operator++() - worst case could have to go to other side of tree
  running time: n
  memory usage: 1

operator*()
  running time: 1
  memory usage: 1

getLabel()
  running time: 1
  memory usage: 1

getDepth() - works like a reverse search (goes back to top)
  running time: log n
  memory usage: 1

copy constructor
  running time: n
  memory usage: n

assignment operator - n if you include copy in the assignment operator
  running time: 1
  memory usage: 1

destructor
  running time: n
  memory usage: 1
