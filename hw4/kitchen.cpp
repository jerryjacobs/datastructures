//kitchen.cpp

#include <fstream>
#include "kitchen.h"
using namespace std;

Kitchen::Kitchen(){
    //does nothing
}
list<Ingredient> Kitchen::getIngredients() const{
    return ingredients;
}
//adds the ingredient if it does not exist in list, else it increases amount of ingredient
void Kitchen::addIngredient(string aName, int aAmount){
    bool exists = false;
    for (list<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++){
        if (aName == (*i).getName()){
            (*i).incAmount(aAmount);
            exists = true;
            break;
        }
    }
    //if ingredient not in kitchen, add it
    if (exists == false){
        ingredients.push_back(Ingredient(aName, aAmount));
    }
}
//prints the ingredients in the kitchen by amount, then alphabetically
void Kitchen::printIngredients(ostream &ostr){
    ingredients.sort(SortByAmount);
    ostr << "In the kitchen:" << endl;
    for (list<Ingredient>::const_iterator i = ingredients.begin(); i != ingredients.end(); i++){
        if ((*i).getAmount() == 1){
            ostr << "  " << (*i).getAmount() << " unit of " << (*i).getName() << endl;
        }
        else{
            ostr << "  " << (*i).getAmount() << " units of " << (*i).getName() << endl;
        }
    }
}
void Kitchen::updateIngredients(list<Ingredient> &newingredients){
    ingredients.clear();
    ingredients = newingredients;
}