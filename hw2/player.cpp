#include <iostream>
#include <string>
#include <string.h>
#include "player.h"
using namespace std;

Player::Player(){
    firstname = "";
    lastname = "";
    matcheswon = 0;
    matcheslost = 0;
    gameswon = 0;
    gameslost = 0;
    sets = 0;
    flawsets = 0;
}
Player::Player(string first, string last){
    firstname = first;
    lastname = last;
    matcheswon = 0;
    matcheslost = 0;
    gameswon = 0;
    gameslost = 0;
    sets = 0;
    flawsets = 0;
}

string Player::getFirstName() const{
    return firstname;
}
string Player::getLastName() const{
    return lastname;
}
int Player::getMatchesWon() const{
    return matcheswon;
}
int Player::getMatchesLost() const{
    return matcheslost;
}
int Player::getGamesWon() const{
    return gameswon;
}
int Player::getGamesLost() const{
    return gameslost;
}
float Player::getPercMatches() const{
    return (float)matcheswon/(matcheswon + matcheslost);
}
float Player::getPercGames() const{
    return (float)gameswon/(gameswon + gameslost);
}
int Player::getSets() const{
    return sets;
}
int Player::getFlawSets() const{
    return flawsets;
}
float Player::getPercFlawSets() const{
    return (float)flawsets/sets;
}
void Player::incMatchesWon(int x){
    matcheswon += x;
}
void Player::incMatchesLost(int x){
    matcheslost += x;
}
void Player::incGamesWon(int x){
    gameswon += x;
}
void Player::incGamesLost(int x){
    gameslost += x;
}
void Player::incSets(int x){
    sets += x;
}
void Player::incFlawSets(int x){
    flawsets += x;
}
bool SortByMatches(const Player &p1, const Player &p2){
    if (p1.getPercMatches() > p2.getPercMatches()){
        return true;
    }
    else if (p1.getPercMatches() < p2.getPercMatches()){
        return false;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) < 0){
        return true;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) > 0){
        return false;
    }
    else if (strcmp(p1.getFirstName().c_str(),p2.getFirstName().c_str()) < 0){
        return true;
    }
    else{
        return false;
    }
}
bool SortByGames(const Player &p1, const Player &p2){
    if (p1.getPercGames() > p2.getPercGames()){
        return true;
    }
    else if (p1.getPercGames() < p2.getPercGames()){
        return false;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) < 0){
        return true;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) > 0){
        return false;
    }
    else if (strcmp(p1.getFirstName().c_str(),p2.getFirstName().c_str()) < 0){
        return true;
    }
    else{
        return false;
    }
}
bool SortByFlawSets(const Player &p1, const Player &p2){
    if (p1.getPercFlawSets() > p2.getPercFlawSets()){
        return true;
    }
    else if (p1.getPercFlawSets() < p2.getPercFlawSets()){
        return false;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) < 0){
        return true;
    }
    else if (strcmp(p1.getLastName().c_str(),p2.getLastName().c_str()) > 0){
        return false;
    }
    else if (strcmp(p1.getFirstName().c_str(),p2.getFirstName().c_str()) < 0){
        return true;
    }
    else{
        return false;
    }
}