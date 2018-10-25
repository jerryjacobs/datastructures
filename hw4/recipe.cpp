//recipe.cpp

#include <fstream>
#include "recipe.h"
using namespace std;

Recipe::Recipe(){
    //does nothing
}
Recipe::Recipe(string aName){
    name = aName;
}
string Recipe::getName() const{
    return name;
}
list<Ingredient> Recipe::getIngredients() const{
    return ingredients;
}
//adds the ingredient if it does not exist in list, else it increases amount of ingredient
void Recipe::addIngredient(string name, int amount){
    bool exists = false;
    for (list<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++){
        if (name == (*i).getName()){
            (*i).incAmount(amount);
            exists = true;
            break;
        }
    }
    //if ingredient not in recipe, add it
    if (exists == false){
        ingredients.push_back(Ingredient(name, amount));
    }
}
//prints the ingredients in the recipe alphabetically
void Recipe::printIngredients(ostream &ostr){
    ingredients.sort(SortByName);
    for (list<Ingredient>::const_iterator i = ingredients.begin(); i != ingredients.end(); i++){
        if ((*i).getAmount() == 1){
            ostr << "  " << (*i).getAmount() << " unit of " << (*i).getName() << endl;
        }
        else{
            ostr << "  " << (*i).getAmount() << " units of " << (*i).getName() << endl;
        }
    }
}