#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

//returns the name of the ship given the size of the ship
string name(int s){
    if (s == 1){
        return string("submarine  ");
    }
    else if (s == 2){
        return string("destroyer  ");
    }
    else if (s == 3){
        return string("cruiser    ");
    }
    else if (s == 4){
        return string("battleship ");
    }
    else if (s == 5){
        return string("carrier    ");
    }
    else if (s == 6){
        return string("cargo      ");
    }
    else{
        return string("tanker     ");
    }
}

//checks if the row and column values match the given row and column values
bool values_match(vector<int> &rows, vector<int> &cols){
    for (unsigned int i = 0; i < rows.size(); i++){
        if (rows[i] > 0){
            return false;
        }
    }
    for (unsigned int i = 0; i < cols.size(); i++){
        if (cols[i] > 0){
            return false;
        }
    }
    return true;
}

//checks if the given grid satisfies the constraints
bool constraint(vector<string> &grid, vector<string> &constraints){
    for (unsigned int i = 0; i < constraints.size(); i++){
        int r = constraints[i][0]-'0';
        int c = constraints[i][1]-'0';
        //submarine check
        if (constraints[i][2] == 'o'){
            if (grid[r][c] != '1'){
                return false;
            }
        }
        //left side check
        else if (constraints[i][2] == '<'){
            if (grid[r][c] == ' ' or grid[r][c] == 'w' or grid[r][c] == '1'){
                return false;
            }
            else if (r > 0 and !(grid[r-1][c] == ' ' or grid[r-1][c] == 'w')){
                return false;
            }
            else if (r < grid.size()-1 and !(grid[r+1][c] == ' ' or grid[r+1][c] == 'w')){
                return false;
            }
            else if (c > 0 and !(grid[r][c-1] == ' ' or grid[r][c-1] == 'w')){
                return false;
            }
        }
        //right side check
        else if (constraints[i][2] == '>'){
            if (grid[r][c] == ' ' or grid[r][c] == 'w' or grid[r][c] == '1'){
                return false;
            }
            else if (r > 0 and !(grid[r-1][c] == ' ' or grid[r-1][c] == 'w')){
                return false;
            }
            else if (r < grid.size()-1 and !(grid[r+1][c] == ' ' or grid[r+1][c] == 'w')){
                return false;
            }
            else if (c < grid[r].size()-1 and !(grid[r][c+1] == ' ' or grid[r][c+1] == 'w')){
                return false;
            }
        }
        //top side check
        else if (constraints[i][2] == '^'){
            if (grid[r][c] == ' ' or grid[r][c] == 'w' or grid[r][c] == '1'){
                return false;
            }
            else if (c > 0 and !(grid[r][c-1] == ' ' or grid[r][c-1] == 'w')){
                return false;
            }
            else if (c < grid[r].size()-1 and !(grid[r][c+1] == ' ' or grid[r][c+1] == 'w')){
                return false;
            }
            else if (r > 0 and !(grid[r-1][c] == ' ' or grid[r-1][c] == 'w')){
                return false;
            }
        }
        //bottom side check
        else if (constraints[i][2] == 'v'){
            if (grid[r][c] == ' ' or grid[r][c] == 'w' or grid[r][c] == '1'){
                return false;
            }
            else if (c > 0 and !(grid[r][c-1] == ' ' or grid[r][c-1] == 'w')){
                return false;
            }
            else if (c < grid[r].size()-1 and !(grid[r][c+1] == ' ' or grid[r][c+1] == 'w')){
                return false;
            }
            else if (r < grid.size()-1 and !(grid[r+1][c] == ' ' or grid[r+1][c] == 'w')){
                return false;
            }
        }
        //middle of ship check
        else if (constraints[i][2] == 'X'){
            if (grid[r][c] == ' ' or grid[r][c] == 'w' or grid[r][c] == '1' or grid[r][c] == '2'){
                return false;
            }
            else{
                int count = 0; //counts the number of adjacent ship cells
                if (r > 0 and !(grid[r-1][c] == ' ' or grid[r-1][c] == 'w')){
                    count++;
                }
                if (r > grid.size()-1 and !(grid[r+1][c] == ' ' or grid[r+1][c] == 'w')){
                    count++;
                }
                if (c > 0 and !(grid[r][c-1] == ' ' or grid[r][c-1] == 'w')){
                    count++;
                }
                if (c < grid[r].size()-1 and !(grid[r][c+1] == ' ' or grid[r][c+1] == 'w')){
                    count++;
                }
                if (count != 2){
                    return false;
                }
            }
        }
        //water check
        else if (constraints[i][2] == '_'){
            if (!(grid[r][c] == ' ' or grid[r][c] == 'w')){
                return false;
            }
        }
    }
    return true;
}

//checks if ship can be placed horizontally
bool check_hor(int ship, vector<int> &rows, vector<int> &cols, int r, int c, vector<string> &grid){
    //does this ship go over the row value
    if (rows[r] > 0 and ship > rows[r]){
        return false;
    }
    else if (rows[r] == 0 or cols[c] == 0){
        return false;
    }
    else{
        //are all spaces empty
        for (unsigned int h = 0; h < ship; h++){
            //square must be empty and must have room to place ship (col value)
            if (grid[r][c+h] != ' ' or cols[c+h] == 0){
                return false;
            }
        }
    }
    return true;
}

//updates current grid and updates ship solutions for horizontal placement of ship
void place_hor(int ship, vector<int> &rows, vector<int> &cols, int r, int c, vector<string> &grid, vector<string> &print_ship){
    //place ship onto grid
    for (unsigned int h = 0; h < ship; h++){
        grid[r][c+h] = '0'+ship;
        rows[r]--; //update row values (remaining ship cells left to be placed in this row)
        cols[c+h]--; //update col values (remaining ship cells left to be placed in this col)
    }
    //place water onto grid
    if (r-1 >= 0){ //top side
        for (unsigned int i = 0; i < ship; i++){
            grid[r-1][i+c] = 'w';
        }
    }
    if (r+1 < grid.size()){ //bottom side
        for (unsigned int i = 0; i < ship; i++){
            grid[r+1][i+c] = 'w';
        }
    }
    if (c + ship < grid[r].size()){ //right side
        grid[r][c + ship] = 'w';
    }
    if (c-1 >= 0){ //left side
        grid[r][c-1] = 'w';
    }
    if (r-1 >= 0 and c + ship < grid[r].size()){ //UR corner
        grid[r-1][c + ship] = 'w';
    }
    if (r+1 < grid.size() and c + ship < grid[r].size()){ //BR corner
        grid[r+1][c + ship] = 'w';
    }
    if (r+1 < grid.size() and c-1 >= 0){ //BL corner
        grid[r+1][c-1] = 'w';
    }
    if (r-1 >= 0 and c-1 >= 0){ //UL corner
        grid[r-1][c-1] = 'w';
    }
    //prepare ship to be printed
    if (ship != 1){
        string s;
        stringstream out;
        out << name(ship) << r << " " << c << " horizontal";
        s = out.str();
        print_ship.push_back(s);
    }
    else{
        string s;
        stringstream out;
        out << name(ship) << r << " " << c;
        s = out.str();
        print_ship.push_back(s);
    }
}

//checks if ship can be placed vertically
bool check_ver(int ship, vector<int> &rows, vector<int> &cols, int r, int c, vector<string> &grid){
    //does this ship go over col value
    if (cols[c] > 0 and ship > cols[c]){
        return false;
    }
    else if (rows[r] == 0 or cols[c] == 0){
        return false;
    }
    else{
        //are all spaces empty
        for (unsigned int v = 0; v < ship; v++){
            //square must be empty and must have room to place ship (row value)
            if (grid[r+v][c] != ' ' or rows[r+v] == 0){
                return false;
            }
        }
    }
    return true;
}

//updates current grid and updates ship solutions for vertical placement of ship
void place_ver(int ship, vector<int> &rows, vector<int> &cols, int r, int c, vector<string> &grid, vector<string> &print_ship){
    //place ship onto grid
    for (unsigned int v = 0; v < ship; v++){
        grid[r+v][c] = '0'+ship;
        rows[r+v]--; //update row values (remaining ship cells left to be placed in this row)
        cols[c]--; //update col values (remaining ship cells left to be placed in this col)
    }
    //place water onto grid
    if (r-1 >= 0){ //top side
        grid[r-1][c] = 'w';
    }
    if (r + ship < grid.size()){ //bottom side
        grid[r + ship][c] = 'w';
    }
    if (c+1 < grid[r].size()){ //right side
        for (unsigned int i = 0; i < ship; i++){
            grid[i+r][c+1] = 'w';
        }
    }
    if (c-1 >= 0){ //left side
        for (unsigned int i = 0; i < ship; i++){
            grid[i+r][c-1] = 'w';
        }
    }
    if (r-1 >= 0 and c+1 < grid[r].size()){ //UR corner
        grid[r-1][c+1] = 'w';
    }
    if (r + ship < grid.size() and c+1 < grid[r].size()){ //BR corner
        grid[r + ship][c+1] = 'w';
    }
    if (r + ship < grid.size() and c-1 >= 0){ //BL corner
        grid[r + ship][c-1] = 'w';
    }
    if (r-1 >= 0 and c-1 >= 0){ //UL corner
        grid[r-1][c-1] = 'w';
    }
    //prepare ship to be printed
    if (ship != 1){
        string s;
        stringstream out;
        out << name(ship) << r << " " << c << " vertical";
        s = out.str();
        print_ship.push_back(s);
    }
    else{
        string s;
        stringstream out;
        out << name(ship) << r << " " << c;
        s = out.str();
        print_ship.push_back(s);
    }
}

//determines real row solution in the case of an unknown value
vector<int> row_solution(vector<int> &rows, vector<int> &rvals){
    vector<int> temp = rvals;
    for (unsigned int i = 0; i < rows.size(); i++){
        if (rows[i] < 0){
            temp[i] = (rows[i]+1)*-1;
        }
    }
    return temp;
}

vector<int> col_solution(vector<int> &cols, vector<int> &cvals){
    vector<int> temp = cvals;
    for (unsigned int i = 0; i < cols.size(); i++){
        if (cols[i] < 0){
            temp[i] = (cols[i]+1)*-1;
        }
    }
    return temp;
}

//determines the total number of remaining ship cells can be placed
int sums(vector<int> &rows, vector<int> &cols){
    vector<int> row = rows;
    vector<int> col = cols;
    int r = 0;
    int c = 0;
    for (unsigned int i = 0; i < row.size(); i++){
        if (row[i] < 0){
            row[i] = col.size();
        }
        r += row[i];
    }
    for (unsigned int i = 0; i < col.size(); i++){
        if (col[i] < 0){
            col[i] = row.size();
        }
        c += col[i];
    }
    if (r < c){
        return r;
    }
    return c;
}

//recursively determines a solution of where to put all the ships to satisfy the grid's constraints
bool rec(vector<string> &grid, vector<int> &arows, vector<int> &acols, vector<int> &ships, int n, vector<string> &print_ship, bool find_all, vector<vector<string> > &grids, vector<vector<string> > &print_ships, vector<string> &constraints, vector<int> &rvals, vector<int> &cvals, vector<vector<int> > &print_rows, vector<vector<int> > &print_cols) {
    vector<int> rows = arows; //we don't want to change actual row values
    vector<int> cols = acols; //we don't want to change actual col values
    //base case
    if (n == 0){
        //find all solutions
        if (find_all){
            //make sure solution is unique
            bool unique = true;
            for (unsigned int i = 0; i < grids.size(); i++){
                if (grid == grids[i]){
                    unique = false;
                    break;
                }
            }
            if (unique and constraint(grid, constraints) and values_match(rows, cols)){
                //add solution to grids, print_ships, print_rows, print_cols
                grids.push_back(grid);
                print_ships.push_back(print_ship);
                print_rows.push_back(row_solution(rows, rvals));
                print_cols.push_back(col_solution(cols, cvals));
            }
            return false;
        }
        //find single solution
        else{
            if (!constraint(grid, constraints) or !values_match(rows, cols)){
                return false;
            }
            //add solution to print_rows and print_cols
            print_rows.push_back(row_solution(rows, rvals));
            print_cols.push_back(col_solution(cols, cvals));
            return true;
        }
    }
    //iterate through all possible starting points for ship
    for (int r = 0; r < grid.size(); r++){
        for (int c = 0; c < grid[r].size(); c++){
            //check if ship is unknown
            if (ships[n-1] == 0){
                for (unsigned int u = 7; u > 0; u--){
                    //check if ship can fit horizontally
                    if (u < sums(rows, cols) and c < grid[r].size() - u + 1 and check_hor(u, rows, cols, r, c, grid)){
                        //saving current state of grid incase pathway fails
                        vector<string> grid0 = grid;
                        vector<int> rows0 = rows;
                        vector<int> cols0 = cols;
                        //update grid
                        place_hor(u, rows, cols, r, c, grid, print_ship);
                        //continue if next ship can be place
                        if (rec(grid, rows, cols, ships, n-1, print_ship, find_all, grids, print_ships, constraints, rvals, cvals, print_rows, print_cols)){
                            return true;
                        }
                        //resets grid if current pathway fails
                        grid = grid0;
                        rows = rows0;
                        cols = cols0;
                        print_ship.pop_back();
                    }
                    //check if ship can fit vertically
                    if (u < sums(rows, cols) and r < grid.size() - u + 1 and check_ver(u, rows, cols, r, c, grid)){
                        //saving current state of grid incase pathway fails
                        vector<string> grid0 = grid;
                        vector<int> rows0 = rows;
                        vector<int> cols0 = cols;
                        //update grid
                        place_ver(u, rows, cols, r, c, grid, print_ship);
                        //continue if next ship can be place
                        if (rec(grid, rows, cols, ships, n-1, print_ship, find_all, grids, print_ships, constraints, rvals, cvals, print_rows, print_cols)){
                            return true;
                        }
                        //resets grid if current pathway fails
                        grid = grid0;
                        rows = rows0;
                        cols = cols0;
                        print_ship.pop_back();
                    }
                }
            }
            //ship is known
            else{
                //check if ship can fit horizontally
                if (c < grid[r].size() - ships[n-1] + 1 and check_hor(ships[n-1], rows, cols, r, c, grid)){
                    //saving current state of grid incase pathway fails
                    vector<string> grid0 = grid;
                    vector<int> rows0 = rows;
                    vector<int> cols0 = cols;
                    //update grid
                    place_hor(ships[n-1], rows, cols, r, c, grid, print_ship);
                    //continue if next ship can be place
                    if (rec(grid, rows, cols, ships, n-1, print_ship, find_all, grids, print_ships, constraints, rvals, cvals, print_rows, print_cols)){
                        return true;
                    }
                    //resets grid if current pathway fails
                    grid = grid0;
                    rows = rows0;
                    cols = cols0;
                    print_ship.pop_back();
                }
                
                //check if ship can fit vertically
                if (r < grid.size() - ships[n-1] + 1 and check_ver(ships[n-1], rows, cols, r, c, grid)){
                    //saving current state of grid incase pathway fails
                    vector<string> grid0 = grid;
                    vector<int> rows0 = rows;
                    vector<int> cols0 = cols;
                    //update grid
                    place_ver(ships[n-1], rows, cols, r, c, grid, print_ship);
                    //continue if next ship can be place
                    if (rec(grid, rows, cols, ships, n-1, print_ship, find_all, grids, print_ships, constraints, rvals, cvals, print_rows, print_cols)){
                        return true;
                    }
                    //resets grid if current pathway fails
                    grid = grid0;
                    rows = rows0;
                    cols = cols0;
                    print_ship.pop_back();
                }
            }
        }
    }
    return false;
}

//neatly displays the solution
void print_solution(vector<string> &grid, vector<int> &rows, vector<int> &cols, vector<string> &print_ship){
    //print ships
    cout << "Solution:" << endl;
    for (unsigned int i = 0; i < print_ship.size(); i++){
        cout << print_ship[i] << endl;
    }
    //clean up grid
    for (unsigned int i = 0; i < grid.size(); i++){
        for (unsigned int j = 0; j < grid[i].size(); j++){
            if (grid[i][j] == 'w'){
                grid[i][j] = ' ';
            }
        }
    }
    //print grid
    cout << "+" << string(cols.size(),'-') << "+" << endl;
    for (unsigned int i = 0; i < grid.size(); i++){
        cout << "|" << grid[i] << "|" << rows[i] << endl;
    }
    cout << "+" << string(cols.size(),'-') << "+" << endl;
    cout << " ";
    for (unsigned int i = 0; i < cols.size(); i++){
        cout << cols[i];
    }
    cout << " " << endl;
}

int main(int argc, char* argv[]){
    //check for 2 or 3 arguments
    if (argc > 3 or argc < 2){
        cerr << "Incorrect number of arguments: " << argc << endl;
        return 1;
    }
    ifstream istr(argv[1]);
    //check if can open file
    if (!istr.good()){
        cerr << "Cannot open file" << endl;
        return 1;
    }
    
    string s;
    int r, c;
    vector<int> ships;
    vector<string> constraints;
    //read board
    istr >> s;
    istr >> s;
    r = atoi(s.c_str()); //number of rows
    istr >> s;
    c = atoi(s.c_str()); //number of cols
    vector<int> rows(r); // make rows
    vector<int> cols(c); //make cols
    //read row values
    istr >> s;
    for (unsigned int i = 0; i < r; i++){
        istr >> s;
        if (s == "?"){
            rows[i] = -1;
        }
        else{
            rows[i] = atoi(s.c_str());
        }
    }
    //read column values
    istr >> s;
    for (unsigned int i = 0; i < c; i++){
        istr >> s;
        if (s == "?"){
            cols[i] = -1;
        }
        else{
            cols[i] = atoi(s.c_str());
        }
    }
    //read ships and save each ship as the length it is in a vector
    while (istr >> s){
        if (s == "submarine"){
            ships.push_back(1);
        }
        else if (s == "destroyer"){
            ships.push_back(2);
        }
        else if (s == "cruiser"){
            ships.push_back(3);
        }
        else if (s == "battleship"){
            ships.push_back(4);
        }
        else if (s == "carrier"){
            ships.push_back(5);
        }
        else if (s == "cargo"){
            ships.push_back(6);
        }
        else if (s == "tanker"){
            ships.push_back(7);
        }
        else if (s == "unknown"){
            ships.push_back(0);
        }
        else if (s == "constraint"){
            string c;
            stringstream out;
            istr >> c;
            out << c;
            istr >> c;
            out << c;
            istr >> c;
            out << c;
            c = out.str();
            constraints.push_back(c);
        }
        else{
            cerr << "Cannot identify command" << endl;
        }
    }
    sort(ships.begin(), ships.end());
    
    //make empty grid
    vector<string> grid;
    vector<string> print_ship;
    for (unsigned int i = 0; i < r; i++){
        grid.push_back(string(c,' '));
    }
    
    vector<vector<int> > print_rows; //all row solutions
    vector<vector<int> > print_cols; //all column solutions
    vector<vector<string> > grids; //all grid solutions
    vector<vector<string> > print_ships; //all print_ship solutions
    
    //find all solutions
    if (argc == 3 and argv[2] == string("find_all_solutions")){
        if (!rec(grid, rows, cols, ships, ships.size(), print_ship, true, grids, print_ships, constraints, rows, cols, print_rows, print_cols)){
            //print all solutions
            for (unsigned int i = 0; i < grids.size(); i++){
                print_solution(grids[i], print_rows[i], print_cols[i], print_ships[i]);
                cout << endl;
            }
            //print how many solutions
            if (grids.size() == 0){
                cout << "No solutions" << endl;
            }
            else{
                cout << "Found " << grids.size() << " solution(s)" << endl;
            }
        }
    }
    //find first solution
    else{
        if (rec(grid, rows, cols, ships, ships.size(), print_ship, false, grids, print_ships, constraints, rows, cols, print_rows, print_cols)){
            print_solution(grid, print_rows[0], print_cols[0], print_ship);
        }
        else{
            cout << "No solution" << endl;
        }
    }
    return 0;
}