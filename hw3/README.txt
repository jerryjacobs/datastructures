HOMEWORK 3: DYNAMIC TETRIS ARRAYS


NAME:  Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
www.cplusplus.com
www.stackoverflow.com
Cavell Teng

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12


MISC. COMMENTS TO GRADER:  
The 4 column functions have the same algorithm:
1) Create the new heights and new data arrays
2) Run a loop to copy heights onto new heights and copy each array from data onto new data
3) Run a loop to delete the arrays in data
4) Delete data and heights completely
5) Set data and heights to new data and new heights

For the add_piece function:
'temp' is a char array that replaces the array at data[i]
'h' is the highest kicker column WITH the offset from the shape of the type
 Each 'rotation block' (if rot ==) has the same basic algorithm:
 1) determine the kicker height 'h'
 2) copy the data array onto the temp array
 3) slightly modify the temp array based on shape type
 4) replace the data array with the temp array
 5) update heights array