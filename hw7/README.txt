HOMEWORK 7: MINIBLAST


NAME:  Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
None


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  2


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
Reads in the commands from the command line and stores data. Saves the queries in a vector<string> and the corresponding query mismatch numbers in a vector<int>.
Creates 1 long string that contains the entire genome by repeated concatenation.
Creates map of genome using kmer indexes by shifting 1 letter at a time per kmer. The map has a second value of vector<int> since 1 kmer can have multiple locations.
Searches through all the queries and for each query it determines if a the beginning of the query exists in the kmer map. If it does then a second loop is nested that searches through all locations of matching beginning kmer (the vector<int> from map). Inside this loop, it builds the query from scratch (via looping through genome) directly from the genome string until it is either complete or there are too many mismatches.


ORDER NOTATION:
L - length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)
s - number of lines in genome

Create genome string: O(s)
Create genome map of kmers: O(L)
1st loop, search through queries: O(LlogL)
2nd loop, search through locations of kmer: O(LlogL*p)
3rd loop, rebuild query from scratch: O(LlogL*p*q)


How much memory will the map data structure require (order notation for memory use)?

O(l)

What is the order notation for performance (running time) of each of
the commands?

Reading in data only:
genome: O(s)
kmer: O(1)
query: O(1)
quit: O(1)


EXTRA CREDIT
Added a new command ‘vector’. If vector is called (before the quit command), a boolean is turned on to use vectors instead of maps. Using a vector forces us to loop through vector instead of random access that we did could in a map.

Table:
		use_map		use_vector
input_small	0 sec		0 sec
input_medium	1 sec		1 sec
input_large	1 sec		1 sec
input_larger	1 sec		2 sec

Takes same amount of time to build kmer index and genome. Takes slightly longer to find query matches because the vector has to sort through each element and check for matching O(n) whereas the map method gets to random access it O(logn).