//ingredient.cpp

#include <string.h>
#include <list>
#include "ingredient.h"
using namespace std;

Ingredient::Ingredient(string aName, int aAmount){
    name = aName;
    amount = aAmount;
}
string Ingredient::getName() const{
    return name;
}
int Ingredient::getAmount() const{
    return amount;
}
void Ingredient::incAmount(int n){
    amount += n;
}
void Ingredient::decAmount(int n){
    amount -= n;
}
//sort ingredients by name
bool SortByName(const Ingredient &i1, const Ingredient &i2){
    if (strcmp(i1.getName().c_str(), i2.getName().c_str()) < 0){
        return true;
    }
    else{
        return false;
    }
}
//sort ingredients first by amount, then alphabetically
bool SortByAmount(const Ingredient &i1, const Ingredient &i2){
    if (i1.getAmount() < i2.getAmount()){
        return true;
    }
    else if (i1.getAmount() > i2.getAmount()){
        return false;
    }
    else if (strcmp(i1.getName().c_str(), i2.getName().c_str()) < 0){
        return true;
    }
    else{
        return false;
    }
}


int Kitchen::count(string look){
    have.sort();
    int count = 0;
    for (list<string>::iterator j = have.begin(); j != have.end(); j++) {
        if (*j == look){
            count++;
        }
    }
    return count;
}