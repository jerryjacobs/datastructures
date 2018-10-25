// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"

void ProvidedTests();
void StudentTests();


// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
    if (a.size() != b.size()) return false;
    typename std::list<T>::const_iterator a_itr = a.begin();
    typename std::list<T>::const_iterator b_itr = b.begin();
    while (a_itr != a.end()) {
        if (*a_itr != *b_itr) return false;
        a_itr++;
        b_itr++;
    }
    return true;
}



// ================================================================================
// This program stress tests the templated MultiLL container class


int main() {
    ProvidedTests();
    StudentTests();
}


// ================================================================================
// ================================================================================

void ProvidedTests() {
    
    std::cout << "Begin ProvidedTests..." << std::endl;
    
    // The test data (stored in STL lists)
    std::list<std::string> songs;
    songs.push_back("hound dog");
    songs.push_back("poker face");
    songs.push_back("brown eyed girl");
    songs.push_back("let it be");
    songs.push_back("walk like an egyptian");
    songs.push_back("man in the mirror");
    songs.push_back("stairway to heaven");
    songs.push_back("dancing in the street");
    songs.push_back("every breath you take");
    songs.push_back("hotel california");
    // the same data, sorted!
    std::list<std::string> sorted_songs(songs);
    sorted_songs.sort();
    
    
    // create an empty multi-linked list and fill it with the test data
    MultiLL<std::string> my_list;
    for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
        my_list.add(*itr);
    }
    assert (songs.size() == my_list.size());
    
    
    
    // -------------------
    // iterator tests
    
    // test the chronological iterator (forwards)
    std::cout << "chronological order" << std::endl;
    std::list<std::string> chrono_order;
    MultiLL<std::string>::iterator itr = my_list.begin_chronological();
    while (itr != my_list.end_chronological()) {
        std::cout << "  " << *itr << std::endl;
        chrono_order.push_back(*itr);
        itr++;
    }
    std::cout << std::endl;
    assert (same(songs,chrono_order));
    
    
    // test the sorted order iterator (forwards)
    std::cout << "sorted order" << std::endl;
    std::list<std::string> sorted_order;
    itr = my_list.begin_sorted();
    while (itr != my_list.end_sorted()) {
        std::cout << "  " << *itr << std::endl;
        sorted_order.push_back(*itr);
        itr++;
    }
    std::cout << std::endl;
    assert (same(sorted_songs,sorted_order));
    

    // test the random order iterator
    std::cout << "random order" << std::endl;
    std::list<std::string> random_order;
    itr = my_list.begin_random();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
        std::cout << "  " << *itr << std::endl;
        random_order.push_back(*itr);
    }
    std::cout << std::endl;
    // loop through the elements a second time (the order should be the same!)
    std::list<std::string>::iterator itr2 = random_order.begin();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
        // verify that the elements repeat the order
        assert (*itr == *itr2);
    }
    std::list<std::string> random_order_check(random_order);
    random_order_check.sort();
    // verify that all of the elements appeared in the initial loop
    assert (same(sorted_songs,random_order_check));
    
    
    // test the re-randomization by creating a new random iterator
    std::cout << "random order 2" << std::endl;
    std::list<std::string> random_order2;
    itr = my_list.begin_random();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
        std::cout << "  " << *itr << std::endl;
        random_order2.push_back(*itr);
    }
    std::cout << std::endl;
    // with over 3 million different possible permutations of 10
    // elements, it is highly unlikely they will be the same!
    assert (!same(random_order,random_order2));
    

    
    // -------------------
    // erase tests
    
    // erase the first element inserted
    itr = my_list.begin_chronological();
    assert (*itr == "hound dog");
    itr = my_list.erase(itr);
    assert (*itr == "poker face");
    assert (my_list.size() == 9);
    std::cout << "erased: hound dog" << std::endl;
    
    // erase the second to last element in sorted order
    itr = my_list.begin_sorted();
    for (int i = 0; i < 7; i++) { itr++; }
    assert (*itr == "stairway to heaven");
    itr = my_list.erase(itr);
    assert (*itr == "walk like an egyptian");
    assert (my_list.size() == 8);
    std::cout << "erased: stairway to heaven" << std::endl;
    
    // erase the third element in the random order
    itr = my_list.begin_random();
    itr++;
    itr++;
    std::string tmp = *itr;
    // note that the return value of erase with a random iterator is undefined
    my_list.erase(itr);
    std::cout << "erased: " << tmp << std::endl;
    assert (my_list.size() == 7);
    assert (!my_list.empty());
   
    my_list.clear();
    assert (my_list.empty());
    assert (my_list.size() == 0);
    std::cout << "cleared the whole list!" << std::endl << std::endl;
    
    std::cout << "Finished ProvidedTests." << std::endl;
}

// ================================================================================
// ================================================================================

void StudentTests() {
    
    std::cout << "Begin StudentTests..." << std::endl;
    
    // ---------------------------
    // ADD YOUR OWN TEST CASES BELOW
    // be sure to test:
    //   copy constructor
    //   assignment operator
    //   destructor
    //   all corner cases of erase
    //   decrement operator for the chronological & sorted iterators
    //   pre vs. post increment & decrement operations for iterators
    //   MultiLL containing types other than std::string
    //   anything else that is necessary
    
    //TEST DATA
    std::list<std::string> songs;
    songs.push_back("hound dog");
    songs.push_back("poker face");
    songs.push_back("brown eyed girl");
    songs.push_back("let it be");
    songs.push_back("walk like an egyptian");
    songs.push_back("man in the mirror");
    songs.push_back("stairway to heaven");
    songs.push_back("dancing in the street");
    songs.push_back("every breath you take");
    songs.push_back("hotel california");
    //sorted STL list
    std::list<std::string> sorted_songs(songs);
    sorted_songs.sort();
    // create an empty multi-linked list and fill it with the test data
    MultiLL<std::string> my_list;
    for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
        my_list.add(*itr);
    }
    assert (songs.size() == my_list.size());
    // create an empty multi-linked list and fill it with the test data backwards
    MultiLL<std::string> assign_list;
    for (std::list<std::string>::reverse_iterator ritr = songs.rbegin(); ritr != songs.rend(); ritr++) {
        assign_list.add(*ritr);
    }
    assert (songs.size() == assign_list.size());

    
    //TEST COPY CONSTRUCTOR
    std::cout << std::endl << "TEST COPY CONSTRUCTOR" << std::endl;
    MultiLL<std::string> copy_list(my_list);
    //test if size was copied
    assert (copy_list.size() == my_list.size());
    std::cout << "#passed copy test: size" << std::endl;
    //test if the chronological pointers were copied
    std::list<std::string> chrono_order;
    MultiLL<std::string>::iterator itr = copy_list.begin_chronological();
    while (itr != copy_list.end_chronological()) {
        chrono_order.push_back(*itr);
        itr++;
    }
    assert (same(songs,chrono_order));
    std::cout << "#passed copy test: chrono" << std::endl;
    //test if the sorted pointers were copied
    std::list<std::string> sorted_order;
    itr = copy_list.begin_sorted();
    while (itr != copy_list.end_sorted()) {
        sorted_order.push_back(*itr);
        itr++;
    }
    assert (same(sorted_songs,sorted_order));
    std::cout << "#passed copy test: sorted" << std::endl;
    
    
    //TEST ASSIGNMENT OPERATOR
    std::cout << std::endl << "TEST ASSIGNMENT OPERATOR" << std::endl;
    assign_list = my_list;
    //test if size was reassigned
    assert (assign_list.size() == my_list.size());
    std::cout << "#passed assign test: size" << std::endl;
    //test if the chronological pointers were destroyed and reassigned
    std::list<std::string> chrono_order2;
    itr = assign_list.begin_chronological();
    while (itr != assign_list.end_chronological()) {
        chrono_order2.push_back(*itr);
        itr++;
    }
    assert (same(songs,chrono_order2));
    std::cout << "#passed assign test: chrono" << std::endl;
    //test if the sorted pointers were destroyed and reassigned
    std::list<std::string> sorted_order2;
    itr = assign_list.begin_sorted();
    while (itr != assign_list.end_sorted()) {
        sorted_order2.push_back(*itr);
        itr++;
    }
    assert (same(sorted_songs,sorted_order2));
    std::cout << "#passed assign test: sorted" << std::endl;
    
    
    //TEST DESTRUCTOR
    std::cout << std::endl << "TEST DESTRUCTOR" << std::endl;
    MultiLL<std::string> *d = new MultiLL<std::string>(my_list); //allocate memory on heap as a copy of my_list
    assert ((*d).size() > 0); //make sure copied list exists
    delete d; //completely remove the list itself
    //checked drmemory to make sure no memory leaks
    //without 'delete p;' we do have a memory leak
    //with 'delete p;' we do not have a memory leak
    std::cout << "#passed destructor test: delete" << std::endl;
    MultiLL<std::string> *c = new MultiLL<std::string>(my_list); //allocate memory on heap as a copy of my_list
    assert ((*c).size() > 0); //make sure copied list exists
    (*c).clear(); //should only remove the nodes in the list, but keep the list
    assert((*c).size() == 0);
    assert((*c).empty() == true); //testing empty function
    delete c; //completely removes the empty list
    std::cout << "#passed destructor test: clear" << std::endl;
    
    
    //TEST POST INCREMENT AND DECREMENT OPERATOR
    std::cout << std::endl << "TEST POST INCREMENT AND DECREMENT OPERATOR" << std::endl;
    // test the chronological decrement operator
    MultiLL<std::string>::iterator post = my_list.begin_chronological();
    assert (*post == "hound dog");
    post++;
    assert (*post == "poker face");
    post--;
    assert (*post == "hound dog");
    std::cout << "#passed post test: chrono" << std::endl;
    // test the sorted decrement operator
    post = my_list.begin_sorted();
    assert (*post == "brown eyed girl");
    post++;
    assert (*post == "dancing in the street");
    post--;
    assert (*post == "brown eyed girl");
    std::cout << "#passed post test: sorted" << std::endl;
    
    
    //TEST PRE INCREMENT AND DECREMENT OPERATOR
    std::cout << std::endl << "TEST PRE INCREMENT AND DECREMENT OPERATOR" << std::endl;
    // test the chronological decrement operator
    MultiLL<std::string>::iterator pre = my_list.begin_chronological();
    assert (*pre == "hound dog");
    ++pre;
    assert (*pre == "poker face");
    --pre;
    assert (*pre == "hound dog");
    std::cout << "#passed pre test: chrono" << std::endl;
    // test the sorted decrement operator
    pre = my_list.begin_sorted();
    assert (*pre == "brown eyed girl");
    ++pre;
    assert (*pre == "dancing in the street");
    --pre;
    assert (*pre == "brown eyed girl");
    std::cout << "#passed pre test: sorted" << std::endl;
    
    
    //TEST OTHER TYPES
    std::cout << std::endl << "TEST OTHER TYPES" << std::endl;
    //testing type int
    MultiLL<int> type1;
    type1.add(0);
    type1.add(10);
    type1.add(-5);
    MultiLL<int>::iterator i1 = type1.begin_chronological();
    assert (*i1 == 0); i1++;
    assert (*i1 == 10); i1++;
    assert (*i1 == -5);
    i1 = type1.begin_sorted();
    assert (*i1 == -5); i1++;
    assert (*i1 == 0); i1++;
    assert (*i1 == 10);
    i1 = type1.erase(i1);
    assert (type1.size() == 2);
    std::cout << "#passed type test: int" << std::endl;
    //testing type int
    MultiLL<float> type2;
    type2.add(0.0);
    type2.add(10.0);
    type2.add(-5.0);
    MultiLL<float>::iterator i2 = type2.begin_chronological();
    assert (*i2 == 0.0); i2++;
    assert (*i2 == 10.0); i2++;
    assert (*i2 == -5.0);
    i2 = type2.begin_sorted();
    assert (*i2 == -5.0); i2++;
    assert (*i2 == 0.0); i2++;
    assert (*i2 == 10.0);
    i2 = type2.erase(i2);
    assert (type2.size() == 2);
    std::cout << "#passed type test: float" << std::endl;
    
    
    //TEST ERASE CORNER CASES
    std::cout << std::endl << "TEST ERASE CORNER CASES" << std::endl;
    //erase the first chrono node
    std::cout << "Contents before erasing: " << std::endl;
    itr = my_list.begin_chronological();
    for ( ; itr != my_list.end_chronological(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    itr = my_list.begin_chronological();
    assert (*itr == "hound dog");
    itr = my_list.erase(itr);
    assert (*itr == "poker face");
    std::cout << "After erasing first node: " << std::endl;
    itr = my_list.begin_chronological();
    for ( ; itr != my_list.end_chronological(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    assert (my_list.size() == 9);
    std::cout << "#passed erase test: first chrono" << std::endl;
    // erase the last chrono node
    itr = my_list.begin_chronological();
    for (int i = 0; i < 8; i++) { itr++; }
    assert (*itr == "hotel california");
    itr = my_list.erase(itr);
    std::cout << "After erasing last node: " << std::endl;
    itr = my_list.begin_chronological();
    for ( ; itr != my_list.end_chronological(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    assert (my_list.size() == 8);
    std::cout << "#passed erase test: last chrono" << std::endl;
    //erase the first sorted node
    std::cout << "Contents before erasing: " << std::endl;
    itr = my_list.begin_sorted();
    for ( ; itr != my_list.end_sorted(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    itr = my_list.begin_sorted();
    assert (*itr == "brown eyed girl");
    itr = my_list.erase(itr);
    assert (*itr == "dancing in the street");
    std::cout << "After erasing first node: " << std::endl;
    itr = my_list.begin_sorted();
    for ( ; itr != my_list.end_sorted(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    assert (my_list.size() == 7);
    std::cout << "#passed erase test: first sorted" << std::endl;
    // erase the last sorted node
    itr = my_list.begin_sorted();
    for (int i = 0; i < 6; i++) { itr++; }
    assert (*itr == "walk like an egyptian");
    itr = my_list.erase(itr);
    std::cout << "After erasing last node: " << std::endl;
    itr = my_list.begin_sorted();
    for ( ; itr != my_list.end_sorted(); itr++){
        std::cout << "  " << *itr << std::endl;
    }
    assert (my_list.size() == 6);
    std::cout << "#passed erase test: last sorted" << std::endl;
    
    
    
    std::cout << std::endl << "Finished StudentTests." << std::endl;
}

// ================================================================================