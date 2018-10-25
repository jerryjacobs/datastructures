HOMEWORK 4: GROCERY LISTS


NAME: Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
www.stackoverflow.com
www.cplusplus.com
Cavell Teng
Kareem El-Faramawi

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8


ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command


command 'r' / add a recipe: O(r*r)

command 'a' / add ingredients to the kitchen: O(a*i)

command 'p' / print a recipe: O(r+k)

command 'm' / make a recipe: O(k*i)

command 'k' / print the contents of the kitchen: O(i)

command 's' / suggest recipes: O(r*k*i)
