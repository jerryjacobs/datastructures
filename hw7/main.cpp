
// main.cpp
// Jerry Jacobs
// 8/31/2016

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    //variables
    string filename;
    string genome = "";
    int k; //size of kmer
    vector<string> queries; //queries to find
    vector<int> queries_m; //mismatches allowed of queries
    bool use_vector = false; //EXTRACREDIT
    bool use_map = true; //EXTRACREDIT
    //read commands
    string s;
    while (cin >> s){
        if (s == "genome"){
            cin >> s;
            filename = s;
        }
        else if (s == "kmer"){
            cin >> s;
            k = atoi(s.c_str());
        }
        else if (s == "query"){
            cin >> s;
            int m = atoi(s.c_str()); //number of allowed mismatches
            queries_m.push_back(m);
            cin >> s;
            queries.push_back(s);
        }
        else if (s == "quit"){
            break;
        }
        else if (s ==  "vector"){ //EXTRACREDIT: new command
            use_vector = true;
            use_map = false;
        }
    }
    //create genome
    ifstream istr(filename.c_str());
    string line;
    while (istr >> line){
        genome += line;
    }
    
    ///////////////////////// REGULAR HOMEWORK /////////////////////////
    
    if (use_map){
        map<const string, vector<int> > kmers; //kmers in genome
        //create genome map of kmers
        for (unsigned int p = 0; p < genome.size() - k + 1; p++){
            string s = genome.substr(p,k); //kmer
            kmers[s].push_back(p);
        }
        //search through all queries
        for (unsigned int q = 0; q < queries.size(); q++){
            string query = queries[q];
            string kmer = query.substr(0,k); //first k letters of query
            int m = queries_m[q]; //allowed mismatches
            cout << "Query: " << query << endl;
            
            //find seed in kmer indexes
            if (kmers.find(kmer) != kmers.end()){
                bool found = false;
                //search through all positions of matching seed
                for (unsigned int i = 0; i < kmers[kmer].size(); i++){
                    int start = kmers[kmer][i]; //start position
                    int mismatches = 0;
                    string match = ""; //rebuilding query match from scratch
                    
                    //loop through genome and build query until mismatches too high
                    unsigned int p;
                    for (p = start; p < query.size() + start; p++){
                        if (mismatches == m and genome[p] != query[p-start]){ //exceeds mismatches
                            break;
                        }
                        else{ //add letter to match
                            match += genome[p];
                            if (genome[p] != query[p-start]){ //found mismatch
                                mismatches++;
                            }
                        }
                    }
                    if (p == query.size() + start){ //completed building match
                        found = true;
                        cout << start << " " << mismatches << " " << match << endl;
                    }
                }
                if (!found){
                    cout << "No Match" << endl;
                }
            }
            else{ //could not find seed
                cout << "No Match" << endl;
            }
        }
    }
    
    ///////////////////////// EXTRA CREDIT /////////////////////////
    
    else if (use_vector){
        vector<string> kmers; //kmer string
        vector<int> kmers_p; //kmer position in genome
        //create genome vector of kmers
        for (unsigned int p = 0; p < genome.size() - k + 1; p++){
            string s = genome.substr(p,k); //kmer
            kmers.push_back(s);
            kmers_p.push_back(p);
        }
        //search through all queries
        for (unsigned int q = 0; q < queries.size(); q++){
            string query = queries[q];
            string kmer = query.substr(0,k); //first k letters of query
            int m = queries_m[q]; //allowed mismatches
            cout << "Query: " << query << endl;
            
            bool found = false;
            //find seed in kmer indexes
            for (unsigned int i = 0; i < kmers.size(); i++){
                if (kmers[i] == kmer){
                    int start = kmers_p[i]; //start position
                    int mismatches = 0;
                    string match = ""; //rebuilding query match from scratch
                    
                    //loop through genome and build query until mismatches too high
                    unsigned int p;
                    for(p = start; p < query.size() + start; p++){
                        if (mismatches == m and genome[p] != query[p-start]){ //exceeds mismatches
                            break;
                        }
                        else{ //add letter to match
                            match += genome[p];
                            if (genome[p] != query[p-start]){ //found mismatch
                                mismatches++;
                            }
                        }
                    }
                    if (p == query.size() + start){ //completed building match
                        found = true;
                        cout << start << " " << mismatches << " " << match << endl;
                    }
                }
            }
            if (!found){
                cout << "No Match" << endl;
            }
        }
    }
    return 0;
}