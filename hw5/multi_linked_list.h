#ifndef MultiLL_h_
#define MultiLL_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include "mtrand.h"

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), sorted_prev(NULL), random_next(NULL) {}
  Node(const T& v) : value(v), chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), sorted_prev(NULL) {}

    // REPRESENTATION
    T value;
    Node<T>* chrono_next;
    Node<T>* chrono_prev;
    Node<T>* sorted_next;
    Node<T>* sorted_prev;
    Node<T>* random_next;
};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator() : ptr(NULL), type(0) {}
  list_iterator(Node<T>* p, int t) : ptr(p), type(t) {}
  list_iterator(const list_iterator<T>& old) : ptr(old.ptr), type(old.type) {}
  list_iterator<T>& operator=(const list_iterator<T>& old) {
      ptr = old.ptr; type = old.type; return *this; }
  ~list_iterator() {}

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr->value; }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
      if (type == 0){
          ptr = ptr->chrono_next;
      }
      else if (type == 1){
          ptr = ptr->sorted_next;
      }
      else if (type == 2){
          ptr = ptr->random_next;
      }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
      if (type == 0){
          ptr = ptr->chrono_next;
      }
      else if (type == 1){
          ptr = ptr->sorted_next;
      }
      else if (type == 2){
          ptr = ptr->random_next;
      }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
      if (type == 0){
          ptr = ptr->chrono_prev;
      }
      else if (type == 1){
          ptr = ptr->sorted_prev;
      }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
      if (type == 0){
          ptr = ptr->chrono_prev;
      }
      else if (type == 1){
          ptr = ptr->sorted_prev;
      }
    return temp;
  }
  // the MultiLL class needs access to the private ptr member variable
  friend class MultiLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr == r.ptr; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr != r.ptr; }

private:
  // REPRESENTATION
  Node<T>* ptr;    // ptr to node in the list
  int type; // 0 = chrono, 1 = sorted, 2 = random
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class MultiLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  MultiLL() : chrono_head(NULL), chrono_tail(NULL), sorted_head(NULL), sorted_tail(NULL), random_head(NULL), size_(0) {}
  MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
  MultiLL& operator= (const MultiLL<T>& old);
  ~MultiLL() { this->destroy_list(); }

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return chrono_head == NULL; }
  void clear() { this->destroy_list(); }

  // modify the linked list structure
  void add(const T& v); //adds a node to the MultiLL
  void randomize(); //randomizes the random pointers in the MultiLL

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator begin_chronological() { return iterator(chrono_head, 0); }
  iterator end_chronological() { return iterator(NULL, 0); }
  iterator begin_sorted() { return iterator(sorted_head, 1); }
  iterator end_sorted() { return iterator(NULL, 1); }
  iterator begin_random() { randomize(); return iterator(random_head, 2); }

private:
  // private helper functions
  void copy_list(const MultiLL<T>& old);
  void destroy_list();

  //REPRESENTATION
    Node<T>* chrono_head;
    Node<T>* chrono_tail;
    Node<T>* sorted_head;
    Node<T>* sorted_tail;
    Node<T>* random_head;
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION

//creates a new node with value v and adds it to the MultiLL
template <class T>
void MultiLL<T>::add(const T& v){
    //creates new node and increases size by 1
    Node<T>* q = new Node<T>(v);
    size_++;
    
//////////// CHRONO SECTION ////////////
    
    //previous node must point to new node
    if (chrono_tail != NULL){
        (*chrono_tail).chrono_next = q;
    }
    //updates the chrono pointers for current node
    (*q).chrono_next = NULL;
    (*q).chrono_prev = chrono_tail;
    //sets the new tail to point to current node
    chrono_tail = q;
    //only have to change the head if MultiLL was empty
    if (empty()){
        chrono_head = q;
    }
    
//////////// SORTED SECTION ////////////
    
    //if MultiLL is empty, simply add node
    if (sorted_head == NULL){
        (*q).sorted_next = NULL;
        (*q).sorted_prev = NULL;
        sorted_head = q;
        sorted_tail = q;
    }
    else{
        bool inserted = false;
        //determine where to insert the node
        for (MultiLL<T>::iterator i = begin_sorted(); i != end_sorted(); i++){
            //loop until correct position for current node is found
            if (v < (*i)){
                if ((*(i.ptr)).sorted_prev != NULL){ //if not first node
                    //set previous node to point forward to current node
                    (*((*(i.ptr)).sorted_prev)).sorted_next = q;
                    //current node points back to previous node
                    (*q).sorted_prev = (*(i.ptr)).sorted_prev;
                }
                else{ //if first node
                    sorted_head = q;
                    (*q).sorted_prev = NULL;
                }
                //current node points forward to next node
                (*q).sorted_next = i.ptr;
                //next node points back to current node
                (*(i.ptr)).sorted_prev = q;
                inserted = true;
                break;
            }
        }
        //if node doesnt come before any in the list, add to end
        if (inserted == false){
            //last node points to current node
            (*sorted_tail).sorted_next = q;
            //current node points to last node
            (*q).sorted_prev = sorted_tail;
            sorted_tail = q;
        }
    }
}

//reassigns the random pointers for each node in the MultiLL
template <class T>
void MultiLL<T>::randomize(){
    static MTRand_int32 mtrand_autoseed(time(NULL)); //initialize a new set of random data
    bool* placed = new bool[size_]; //keeps track of which nodes have already been assignd random pointers
    for (unsigned int i = 0; i < size_; i++){
        placed[i] = false; //false means node hasnt been assigned random pointers, true means it has
    }
    
    int rand; //random number that will represent the index of the node to assign random pointers to
    int count = 0; //counts how many nodes have been assigned random pointers
    Node<T>* p; //last node that was placed in the loop
    
    while (count < size_){
        rand = mtrand_autoseed() % (size_); // create new random index
        if (placed[rand] == true) { continue; } //check if the random node is already placed
        Node<T>* q = chrono_head;
        
        //find the node we want to place
        for (unsigned int i = 0; i < size_; i++){
            if (i == rand){ //located the randomly chosen node
                //check if random node is the first to be placed
                if (count == 0){
                    random_head = q; //head points to starting node
                }
                //check if random node is last to be placed
                else if (count == size_-1){
                    (*q).random_next = random_head; //point back to start
                    (*p).random_next = q; //previous node points to current node
                }
                //node is not a corner case
                else{
                    (*p).random_next = q; //previous node points to current node
                }
                placed[i] = true;
                count++;
                break;
            }
            q = (*q).chrono_next; //go to next node in chronological list
        }
        p = q; //setting up "last node" for next iteration
    }
    delete [] placed;
}

template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (MultiLL<T>& left, MultiLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename MultiLL<T>::iterator left_itr = left.begin();
  typename MultiLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}
template <class T>
bool operator!= (MultiLL<T>& left, MultiLL<T>& right){ return !(left==right); }

//removes the node that the itr is pointing to from the MultiLL
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
    Node<T>* q = itr.ptr;
    //if only one node in list
    if (size_ == 1){
        chrono_head = NULL;
        chrono_tail = NULL;
        sorted_head = NULL;
        sorted_tail = NULL;
        random_head = NULL;
    }
    //multiple nodes in list
    else{
        
//////////// CHRONO SECTION ////////////
        
        //if first in chrono list
        if (chrono_head == q){
            chrono_head = (*q).chrono_next; //head points to next node
            (*((*q).chrono_next)).chrono_prev = NULL; //next node poitns back to NULL
        }
        //if last in chrono list
        else if (chrono_tail == q){
            chrono_tail = (*q).chrono_prev; //tail points to prev node
            (*((*q).chrono_prev)).chrono_next = NULL; //prev node points to NULL
        }
        //inbetween two nodes
        else{
            (*((*q).chrono_prev)).chrono_next = (*q).chrono_next; //prev node points to next node
            (*((*q).chrono_next)).chrono_prev = (*q).chrono_prev; //next node points back to prev node
        }
        
//////////// SORTED SECTION ////////////
        
        //if first in sorted list
        if (sorted_head == q){
            sorted_head = (*q).sorted_next; //head points to next node
            (*((*q).sorted_next)).sorted_prev = NULL; //next node poitns back to NULL
        }
        //if last in sorted list
        else if (sorted_tail == q){
            sorted_tail = (*q).sorted_prev; //tail points to prev node
            (*((*q).sorted_prev)).sorted_next = NULL; //prev node points to NULL
        }
        //inbetween two nodes
        else{
            (*((*q).sorted_prev)).sorted_next = (*q).sorted_next; //prev node points to next node
            (*((*q).sorted_next)).sorted_prev = (*q).sorted_prev; //next node points back to prev node
        }
        
//////////// RANDOM SECTION ////////////
//This section of the erase code is redundant since the random pointers will be rearranged anyways
//when a random iterator is called. This portion of the erase function has O(n), while the rest
//has O(1). Removing this section of the erase function increases the speed and doesn't result in errors.
//Feel free to uncomment it and try it out yourself, but it doesn't have any purpose. Random pointers
//don't need to be updated since they get reassigned from scratch every time a random pointer is called.

        /*
        //make sure randomize() function has been called at least once
        if (random_head != NULL){
            if (random_head == q){ //if first in random list
                random_head = (*q).random_next; //head poitns to next node
            }
            else{
                //loop until we find prev node
                Node<T>* p = q;
                //loop around the list until we get to 1 before the current node (prev node)
                for (unsigned int i = 0; i < size_-1; i++){
                    p = (*p).random_next;
                }
                (*p).random_next = (*q).random_next; //prev node points to next node
            }
        }
        */
        
    }
    //delete current node, decrease size, return iterator pointing to next node
    iterator ret(itr);
    ret++;
    delete itr.ptr;
    size_--;
    return ret;
}

//copies all nodes from old list to new list (including iterators associated with each node)
template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>& old) {
    size_ = old.size_;
    //if list is empty
    if (size_ == 0){
        chrono_head = NULL;
        chrono_tail = NULL;
        sorted_head = NULL;
        sorted_tail = NULL;
        random_head = NULL;
    }
    else{
//////////// CHRONO SECTION ////////////
        chrono_head = new Node<T>((*(old.chrono_head)).value); //first node copied
        chrono_tail = chrono_head; //tail will change, unless size = 1
        Node<T>* q = (*(old.chrono_head)).chrono_next; //next node to be copied
        while (q != NULL){
            (*chrono_tail).chrono_next = new Node<T>((*q).value); //current node points to next node
            (*((*chrono_tail).chrono_next)).chrono_prev = chrono_tail; //next node points back to current node
            chrono_tail = (*chrono_tail).chrono_next; //update tail pointer to last node added
            q = (*q).chrono_next; //move to next node in old list
        }
//////////// SORTED SECTION ////////////
        sorted_head = old.sorted_head; //copy head
        sorted_tail = old.sorted_tail; //copy tail
        Node<T>* p = chrono_head; //new list's pointer
        q = old.chrono_head; //old list's pointer
        while ((*q).chrono_next != NULL){
            (*p).sorted_next = (*q).sorted_next; //copy next pointer
            (*p).sorted_prev = (*q).sorted_prev; //copy prev pointer
            p = (*p).chrono_next; //move to next node in new list
            q = (*q).chrono_next; //move to next node in old list
        }
//////////// RANDOM SECTION ////////////
        random_head = old.random_head; //copy head
        p = chrono_head; //new list's pointer
        q = old.chrono_head; //old list's pointer
        while ((*q).chrono_next != NULL){
            (*p).random_next = (*q).random_next; //copy next pointer
            p = (*p).chrono_next; //move to next node in new list
            q = (*q).chrono_next; //move to next node in old list
        }
        (*p).random_next = (*q).random_next; //last node wasn't in loop
    }
}

template <class T>
void MultiLL<T>::destroy_list() {
    Node<T>* next;
    while (size_ != 0){
        next = (*chrono_head).chrono_next; //q points to next node to be deleted
        delete chrono_head; //delete current node (aka head node)
        chrono_head = next; //head now points to next node
        size_--;
    }
}

#endif
