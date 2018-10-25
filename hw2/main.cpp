//
//  main.cpp
//  Homework 2
//
//  Created by Jerry Jacobs on 2/8/16.
//  Copyright © 2016 Jerry Jacobs. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include "player.h"
using namespace std;

// Parses a string that represents a set (i.e., "6-3") by breaking the
// string into two substrings and converting those strings to
// integers, which are returned via call-by-reference parameters
void parse_set(string &set, int &games_won, int &games_lost) {
    int i = set.find('-');
    games_won =  atoi(set.substr(0,i).c_str());
    games_lost = atoi(set.substr(i+1,set.size()-i-1).c_str());
}

int main(int argc, char * argv[]) {
    //checks for 3 arguments
    if (argc != 3) {
        cerr << "Needs 3 arguments" << endl << "Has " << argc << " arguments" << endl;
        return 1;
    }
    //checks input file is valid
    ifstream file(argv[1]);
    if (!file.good()) {
        cerr << "Cannot open the file" << endl;
        return 2;
    }
    
//GRABBING INFORMATION
    
    //reads input file line by line and stores data into each player in players vector
    vector<Player> players;
    string firstname1;
    string lastname1;
    string d;
    string firstname2;
    string lastname2;
    string set;
    
    file >> set; //set becomes the firstname1 after the first iteration so we do the same thing with the first iteration
    while (file >> lastname1) {
        firstname1 = set;
        file >> d;
        file >> firstname2;
        file >> lastname2;
        
        //checks if player1 is already registered in players vector
        bool playerexists = false;
        for (unsigned int i = 0; i < players.size(); i++){
            if (players[i].getFirstName() == firstname1 and players[i].getLastName() == lastname1){
                playerexists = true;
                break;
            }
        }
        //if player1 not registered, add player1 to players vector
        if (playerexists == false){
            Player p1(firstname1, lastname1);
            players.push_back(p1);
        }
        playerexists = false;
        //checks if player2 is already registered in players vector
        for (unsigned int i = 0; i < players.size(); i++){
            if (players[i].getFirstName() == firstname2 and players[i].getLastName() == lastname2){
                playerexists = true;
                break;
            }
        }
        //if player2 not registered, add player2 to players vector
        if (playerexists == false){
            Player p2(firstname2, lastname2);
            players.push_back(p2);
        }
        
        //updates matches won and lost for both players
        for (unsigned int i = 0; i < players.size(); i++){
            if (players[i].getFirstName() == firstname1 and players[i].getLastName() == lastname1){
                players[i].incMatchesWon(1);
            }
            else if (players[i].getFirstName() == firstname2 and players[i].getLastName() == lastname2){
                players[i].incMatchesLost(1);
            }
        }
        //check if its a set, and keep interpretting sets until it becomes firstname1 of next match
        while(file >> set){
            if (isdigit(set[0])){
                int games_won;
                int games_lost;
                parse_set(set, games_won, games_lost);
                
                //updates games won and lost for both players along with sets and flawless sets
                for (unsigned int i = 0; i < players.size(); i++){
                    if (players[i].getFirstName() == firstname1 and players[i].getLastName() == lastname1){
                        players[i].incGamesWon(games_won);
                        players[i].incGamesLost(games_lost);
                        players[i].incSets(1);
                        if (games_lost == 0){
                            players[i].incFlawSets(1);
                        }
                    }
                    else if (players[i].getFirstName() == firstname2 and players[i].getLastName() == lastname2){
                        players[i].incGamesWon(games_lost);
                        players[i].incGamesLost(games_won);
                        players[i].incSets(1);
                    }
                }
            }
            else{
                break;
            }
        }
    }
    
//COMPUTING INFORMATION
    
    //creates file contatining computed statistics
    ofstream output;
    output.open(argv[2]);
    
    //Determine longest name to prepare for formatting
    unsigned int n = 0;
    for (unsigned int i = 0; i < players.size(); i++){
        string fullname = players[i].getFirstName() + " " + players[i].getLastName();
        if (fullname.size() > n){
            n = fullname.size();
        }
    }
    //Sorts match statistics
    sort(players.begin(), players.end(), SortByMatches);
    output << "MATCH STATISTICS" << endl;
    output << left << setw(n+2) << "Player" << "  W    L   percentage" << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        output << left << setw(n+2) << players[i].getFirstName() + " " + players[i].getLastName() << right << setw(3) << players[i].getMatchesWon() << right << setw(5) << players[i].getMatchesLost() << right << setw(13) << setprecision(3) << fixed << players[i].getPercMatches() << endl;
    }
    //Sorts game statistics
    sort(players.begin(), players.end(), SortByGames);
    output << endl << "GAME STATISTICS" << endl;
    output << left << setw(n+2) << "Player" << "  W    L   percentage" << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        output << left << setw(n+2) << players[i].getFirstName() + " " + players[i].getLastName() << right << setw(3) << players[i].getGamesWon() << right << setw(5) << players[i].getGamesLost() << right << setw(13) << setprecision(3) << fixed << players[i].getPercGames() << endl;
    }
    //Sorts flawless set statistics
    sort(players.begin(), players.end(), SortByFlawSets);
    output << endl << "FLAWLESS SET STATISTICS" << endl;
    output << left << setw(n+2) << "Player" << "FlawSets   percentage" << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        output << left << setw(n+2) << players[i].getFirstName() + " " + players[i].getLastName() << right << setw(8) << players[i].getFlawSets() << right << setw(13) << setprecision(3) << fixed << players[i].getPercFlawSets() << endl;
    }
    
    output.close();
    return 0;
}