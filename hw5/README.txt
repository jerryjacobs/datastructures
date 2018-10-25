HOMEWORK 5: MULTI LINKED LISTS


NAME: Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
http://en.wikipedia.org/wiki/Mersenne_twister
www.stackoverflow.com
Kareem El-Faramawi


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12



TESTING & DEBUGGING STRATEGY:
Whenever I got a segfault error, I would put many points of std::cout throughout the code until I could pinpoint the exact location of the segfault and it would then be pretty obvious what I was doing wrong (most of the time I was trying to access something that shouldn’t be accessed or going too far in a loop).
Everytime I wrote something general, I often got errors on the corner cases, so I went back and made separate cases. I mostly got these kinds of errors when the pointers pointed to NULL or it pointed too far and accessed random data. The terminal always told me where the error was.
An error that I found to be funny was when I realized my iterator wasn’t actually copying the type over when I reassigned it from begin_chronological to begin_sorted. Debugging this one wasn’t too hard because I noticed that when I output the lists, it was always the same chronological list and not the sorted. I had forgotten to copy the type of the iterator over in my constructor.
In general, if I ever got an error, filling my code with std::cout << “DEBUG 1”, std::cout << “DEBUG 2”, etc all throughout my implementation really made it easy to pinpoint where the error was coming from.
Another method of debugging was always printing out the list to see clearly what was being modified in the list and making sure that was the correct modification (for example, erasing a node from the list).
Memory debugging wasn’t too bad since I only had a tiny problem with the erase function. I tried to iterate the return iterator AFTER deleting the original iterator instead of before deleting. I was trying to increment an iterator that didn’t exist. DrMemory made that pretty easy, since it told me which line the problem was on.



ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor O(1)

copy constructor O(n)

assignment operator O(n)

destructor O(n)

size O(1)

empty O(1)

clear O(n)

add O(n)

erase O(1)

begin_chronological O(1)

end_chronological O(1)

begin_sorted O(1)

end_sorted O(1)

begin_random O(n^2)


ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.

Since you can use multiple iterators of different types on the same MultiLL (for example using a chrono iterator then switching it to a sorted iterator), I kept track of iterator type consistently throughout every iterator operation. The second an iterator is constructed or copied or assigned, the type of that iterator is evaluated. The iterator carries this type throughout the entire code. Each iterator operation must be modified to account for which type of iterator it is. For example, with the increment and decrement iterators, we have if statements to check which type of iterator it is BEFORE executing the code. This allows us to increment and decrement the operator no matter what type it is since the actual type gets taken into account only when its being incremented and decrement.


EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Describe.

randomize() function when begin_random() is called
Original order notation: O(n^2)
It could be rewritten to have order O(n)


MISC. COMMENTS TO GRADER:  
Line 343 in the .h file has some code that is commented out. If you uncomment the code, the program works just as fine as it is without the code. Please read the comments in the code.
