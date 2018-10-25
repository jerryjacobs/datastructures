#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <list>

// ===================================================================
// POINT CLASS
template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

// ===================================================================
// NODE CLASS
template <class number_type, class label_type>
class Node {
public:
    Node(): pt(0,0){
        for (unsigned int i = 0; i < 4; i++) { children[i] = NULL; }
    }
    Node(const label_type &label_): pt(0,0){
        for (unsigned int i = 0; i < 4; i++) { children[i] = NULL; label = label_; }
    }
    Point<number_type> pt;
    label_type label;
    Node* parent;
    Node* children[4];
};

// ===================================================================
// DEPTH ITERATOR CLASS
template <class number_type, class label_type>
class DepthIterator {
private:
    Node<number_type, label_type>* ptr;
public:
    //constructors
    DepthIterator(): ptr(NULL) {}
    DepthIterator(Node<number_type, label_type>* p): ptr(p) {}
    DepthIterator(const DepthIterator<number_type, label_type> &old): ptr(old.ptr) {}
    //operators
    DepthIterator& operator=(const DepthIterator &old) { ptr = old.ptr; return *this; }
    Point<number_type>& operator*() { return ptr->pt; }
    bool operator==(const DepthIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const DepthIterator& other) const { return ptr != other.ptr; }
    //pre increment
    DepthIterator& operator++(){
        //has a child
        if (ptr->children[0] != NULL or ptr->children[1] != NULL or ptr->children[2] != NULL or ptr->children[3] != NULL){
            for (unsigned int i = 0; i < 4; i++){
                if (ptr->children[i] != NULL){
                    ptr = ptr->children[i];
                    return *this;
                }
            }
        }
        //does not have a child
        else{
            while (ptr->parent != NULL){
                //determine current child
                int current;
                for (int i = 0; i < 4; i++){
                    if (ptr->parent->children[i] == ptr){
                        current = i;
                    }
                }
                //current node has "older" siblings
                for (int i = current+1; i < 4; i++){
                    if (ptr->parent->children[i] != NULL){
                        ptr = ptr->parent->children[i];
                        return *this;
                    }
                }
                //current node does not have "older" siblings
                ptr = ptr->parent;
            }
        }
        //at the end
        ptr = NULL;
        return *this;
    }
    //post increment
    DepthIterator operator++(int){
        DepthIterator<number_type, label_type> temp(*this);
        ++(*this);
        return temp;
    }
    //returns depth of current node
    int getDepth() const{
        Node<number_type, label_type>* p;
        p = ptr;
        int count = 0;
        while (p->parent != NULL){
            p = p->parent;
            count++;
        }
        return count;
    }
    //returns label of current node
    label_type& getLabel() const{
        return ptr->label;
    }
};

// ===================================================================
// BREADTH ITERATOR CLASS
template <class number_type, class label_type>
class BreadthIterator {
private:
    Node<number_type, label_type>* ptr;
    std::list<Node<number_type, label_type>*> q;
public:
    //constructors
    BreadthIterator(): ptr(NULL) {}
    BreadthIterator(Node<number_type, label_type>* p): ptr(p) { q.push_back(p); }
    BreadthIterator(const BreadthIterator<number_type, label_type> &old): ptr(old.ptr) { q = old.q; }
    //operators
    BreadthIterator& operator=(const BreadthIterator &old) { ptr = old.ptr; q = old.q; return *this; }
    Point<number_type>& operator*() { return ptr->pt; }
    bool operator==(const BreadthIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const BreadthIterator& other) const { return ptr != other.ptr; }
    //returns depth of current node
    int getDepth() const{
        Node<number_type, label_type>* p;
        p = ptr;
        int count = 0;
        while (p->parent != NULL){
            p = p->parent;
            count++;
        }
        return count;
    }
    //returns label of current node
    label_type& getLabel() const{
        return ptr->label;
    }
    //pre increment
    BreadthIterator& operator++(){
        //null pointer
        if (ptr == NULL) { return *this; }
        //add children, pop front
        for (unsigned int i = 0; i < 4; i++){
            if (q.front()->children[i] != NULL){
                q.push_back(q.front()->children[i]);
            }
        }
        q.pop_front();
        //determine ptr
        if (q.size() == 0){
            ptr = NULL;
        }
        else{
            ptr = q.front();
        }
        return *this;
    }
    //post increment
    BreadthIterator operator++(int){
        BreadthIterator<number_type, label_type> temp(*this);
        ++(*this);
        return temp;
    }
};

// ===================================================================
// QUAD TREE CLASS
template <class number_type, class label_type>
class QuadTree {
public:
    QuadTree(): root_(NULL), size_(0) {} //default constructor
    QuadTree(const QuadTree<number_type, label_type>& old): size_(old.size_){ //copy constructor
        root_ = this->copy_tree(old.root_, NULL); }
    ~QuadTree() { this->destroy_tree(root_); root_ = NULL; } //destroyer
    bool operator==(const QuadTree<number_type, label_type>& old) const { return (this->root_ == old.root_); } //equal operator
    bool operator!=(const QuadTree<number_type, label_type>& old) const { return (this->root_ != old.root_); } //not equal operator
    QuadTree& operator=(const QuadTree<number_type, label_type>& old){ //assignment operator
        if (&old != this){
            this->destroy_tree(root_);
            root_ = this->copy_tree(old.root_, NULL);
            size_ = old.size_;
        }
        return *this;
    }
    //use iterators
    typedef DepthIterator<number_type, label_type> iterator;
    friend class DepthIterator<number_type, label_type>;
    typedef BreadthIterator<number_type, label_type> bf_iterator;
    friend class BreadthIterator<number_type, label_type>;
    //iterators begin and end
    iterator begin() const{ return iterator(root_); }
    iterator end() const{ return iterator(NULL); }
    bf_iterator bf_begin() const{ return bf_iterator(root_); }
    bf_iterator bf_end() const{ return bf_iterator(NULL); }
    //returns number of nodes in tree
    int size() const { return size_; }
    //returns maximum depth of tree
    int height() const {
        int max = -1;
        for (iterator i = begin(); i != end(); ++i){
            if (i.getDepth() > max){
                max = i.getDepth();
            }
        }
        return max;
    }
    //find,insert,erase
    iterator find(int x, int y) { return find(x, y, root_); }
    std::pair<iterator, bool> insert(const Point<number_type>& point, const label_type& label) { return insert(point, label, root_, NULL); }
    
    //----------------------------------------------------------------
    // plot driver function
    // takes in the maximum x and y coordinates for these data points
    // the optional argument draw_lines defaults to true
    void plot(int max_x, int max_y, bool draw_lines=true) const {
        // allocate blank space for the center of the board
        std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
        // edit the board to add the point labels and draw vertical and
        // horizontal subdivisions
        plot(root_,board,0,max_x,0,max_y,draw_lines);
        // print the top border of the plot
        std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
        for (int i = 0; i <= max_y; i++) {
            // print each row of the board between vertical border bars
            std::cout << "|" << board[i] << "|" << std::endl;
        }
        // print the top border of the plot
        std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
    }
    
    // actual recursive function for plotting
    void plot(Node<number_type,label_type>* p, std::vector<std::string> &board,
              int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
        // base case, draw nothing if this node is NULL
        if (p == NULL) return;
        // check that the dimensions range of this node make sense
        assert (x_min >= 0 && x_min <= x_max);
        assert (y_min >= 0 && y_min <= y_max);
        assert (board.size() >= y_max);
        assert (board[0].size() >= x_max);
        // verify that the point stored at this node fits on the board
        assert (p->pt.y >= 0 && p->pt.y < board.size());
        assert (p->pt.x >= 0 && p->pt.x < board[0].size());
        // draw the vertical and horizontal bars extending across the
        // range of this node
        if (draw_lines) {
            for (int x = x_min; x <= x_max; x++) {
                board[p->pt.y][x] = '-';
            }
            for (int y = y_min; y <= y_max; y++) {
                board[y][p->pt.x] = '|';
            }
        }
        // draw this label
        board[p->pt.y][p->pt.x] = p->label;
        // recurse on the 4 children
        plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
        plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
        plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
        plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
    }
    
    // prints all of the tree data with a pre-order (node first, then
    // children) traversal of the tree structure
    // driver function
    void print_sideways() const { print_sideways(root_,""); }
    
    // actual recursive function
    void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
        // base case
        if (p == NULL) return;
        // print out this node
        std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
        // recurse on each of the children trees
        // increasing the indentation
        print_sideways(p->children[0],indent+"  ");
        print_sideways(p->children[1],indent+"  ");
        print_sideways(p->children[2],indent+"  ");
        print_sideways(p->children[3],indent+"  ");
    }
    //----------------------------------------------------------------
    
private:
    //variables
    Node<number_type, label_type>* root_;
    int size_;
    //copy
    Node<number_type, label_type>* copy_tree(Node<number_type, label_type>* old_root, Node<number_type, label_type>* old_parent){
        if (old_root == NULL) { return NULL; }
        Node<number_type, label_type>* answer = new Node<number_type, label_type>();
        answer->pt = old_root->pt;
        answer->label = old_root->label;
        answer->parent = old_parent;
        for (unsigned int i = 0; i < 4; i++){
            answer->children[i] = copy_tree(old_root->children[i], answer);
        }
        return answer;
    }
    //destroy
    void destroy_tree(Node<number_type, label_type>* p){
        if (p == NULL) { return; }
        for (unsigned int i = 0; i < 4; i++){
            destroy_tree(p->children[i]);
        }
        delete p;
        size_ = 0;
    }
    //find
    iterator find(int x, int y, Node<number_type, label_type>* p){
        if (p == NULL) { return iterator(NULL); }
        //determine which child to go to
        if      (x < p->pt.x and y < p->pt.y) { return find(x, y, p->children[0]); }
        else if (x > p->pt.x and y < p->pt.y) { return find(x, y, p->children[1]); }
        else if (x < p->pt.x and y > p->pt.y) { return find(x, y, p->children[2]); }
        else if (x > p->pt.x and y > p->pt.y) { return find(x, y, p->children[3]); }
        else { return iterator(p); }
    }
    //insert
    std::pair<iterator, bool> insert(const Point<number_type>& point, const label_type& label, Node<number_type, label_type>*& p, Node<number_type, label_type>* parent){
        //found spot to place node
        if (p == NULL){
            p = new Node<number_type, label_type>(label);
            p->pt = point;
            p->parent = parent;
            this->size_++;
            return std::pair<iterator, bool>(iterator(p), true);
        }
        //follow tree down
        else if (point.x < p->pt.x and point.y < p->pt.y) { return insert(point, label, p->children[0], p); }
        else if (point.x > p->pt.x and point.y < p->pt.y) { return insert(point, label, p->children[1], p); }
        else if (point.x < p->pt.x and point.y > p->pt.y) { return insert(point, label, p->children[2], p); }
        else if (point.x > p->pt.x and point.y > p->pt.y) { return insert(point, label, p->children[3], p); }
        //point already in tree
        else {
            return std::pair<iterator, bool>(iterator(p), false);
        }
    }
};

#endif