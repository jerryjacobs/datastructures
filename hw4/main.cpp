//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
#include "recipe.h"
#include "kitchen.h"
#include "ingredient.h"
using namespace std;

// Helper functions
void readRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes);
void addIngredients(istream &istr, ostream &ostr, Kitchen &kitchen);
void printRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes);
void makeRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes, Kitchen &kitchen);
void recipeSuggestions(ostream &ostr, const list<Recipe> &recipes, const Kitchen &kitchen);
bool canMakeRecipe(const list<Ingredient> &recipeitems, const list<Ingredient> &kitchenitems);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file
  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file
  ofstream ostr(argv[2]);
  if (!ostr) {
    cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);
      
    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,recipes,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else if (c == 's') {
      // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE CURRENT CONTENTS OF THE KITCHEN
      recipeSuggestions(ostr,recipes,kitchen);

    } else {
      cerr << "Unknown character: " << c << endl;
      exit(0);
    }
  }  
}
//adds ingredients to the recipe and adds recipe to list recipes
void readRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes) {
  int units;
  string name, name2;
  istr >> name;
  // build the new recipe
  Recipe r(name);
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name2;
    r.addIngredient(name2,units);
  }
  // add it to the list
    bool exists = false; //does recipe exist
    for (list<Recipe>::const_iterator i = recipes.begin(); i != recipes.end(); i++){
        if (name == (*i).getName()){
            ostr << "Recipe for " << name << " already exists" << endl;
            exists = true;
        }
    }
    if (exists == false){
        recipes.push_back(r);
        ostr << "Recipe for " << name << " added" << endl;
    }
}
//adds ingredients to the kitchen
void addIngredients(istream &istr, ostream &ostr, Kitchen &kitchen) {
  int units;
  string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }
    if (count == 1){
        ostr << count << " ingredient added to kitchen" << endl;
    }
    else{
        ostr << count << " ingredients added to kitchen" << endl;
    }
}
//prints the ingredients listed on the recipe
void printRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes) {
    string name;
    istr >> name;
    bool exists = false; //does recipe exist
    for (list<Recipe>::iterator i = recipes.begin(); i != recipes.end(); i++){
        if (name == (*i).getName()){
            ostr << "To make " << name << ", mix together:" << endl;
            //print ingredients in alphabetical order
            (*i).printIngredients(ostr);
            exists = true;
            break;
        }
    }
    if (exists == false){
        ostr << "No recipe for " << name << endl;
    }
}
//determines if recipe can be made before making it and removing the used ingredients from kitchen
void makeRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes, Kitchen &kitchen) {
    string name;
    istr >> name;
    bool exists = false; //does recipe exist
    list<Recipe>::const_iterator i;
    for (i = recipes.begin(); i != recipes.end(); i++){
        if (name == (*i).getName()){
            exists = true;
            break;
        }
    }
    if (exists == false){
        ostr << "Don't know how to make " << name << endl;
    }
    else{
        //creates temp lists to modify
        list<Ingredient> recipeitems = (*i).getIngredients();
        list<Ingredient> kitchenitems = kitchen.getIngredients();
        //check if it can make recipe with kitchen ingredients
        if(canMakeRecipe(recipeitems, kitchenitems)){
            ostr << "Made " << (*i).getName() << endl;
            //remove ingredients from kitchen
            for (list<Ingredient>::const_iterator r = recipeitems.begin(); r != recipeitems.end(); r++){
                for (list<Ingredient>::iterator k = kitchenitems.begin(); k != kitchenitems.end(); k++){
                    if ((*k).getName() == (*r).getName()){
                        (*k).decAmount((*r).getAmount()); //decrease amount of kitchen ingredient by amount of recipe ingredient
                        if ((*k).getAmount() == 0){
                            k = kitchenitems.erase(k); //remove ingredient from kitchen if amount == 0
                        }
                        break;
                    }
                }
            }
        }
        else{
            ostr << "Cannot make " << (*i).getName() << ", need to buy:" << endl;
            Recipe missing;
            //determine missing ingredients
            for (list<Ingredient>::const_iterator r = recipeitems.begin(); r != recipeitems.end(); r++){
                bool exists = false; //does kitchen have the ingredient
                for (list<Ingredient>::const_iterator k = kitchenitems.begin(); k != kitchenitems.end(); k++){
                    if ((*k).getName() == (*r).getName()){
                        if ((*k).getAmount() < (*r).getAmount()){
                            //add ingredient to missing if kitchen amount is less than recipe amount with new amount = r - k
                            missing.addIngredient((*r).getName(), (*r).getAmount() - (*k).getAmount());
                        }
                        exists = true;
                        break;
                    }
                }
                if (exists == false){ //add ingredient to missing if not in kitchen
                    missing.addIngredient((*r).getName(), (*r).getAmount());
                }
            }
            //print missing ingredients
            missing.printIngredients(ostr);
        }
        //updates real kitchen list
        kitchen.updateIngredients(kitchenitems);
    }
}
//iterates through recipe list and determines all recipes that can be made with kitchen ingredients
void recipeSuggestions(ostream &ostr, const list<Recipe> &recipes, const Kitchen &kitchen) {
    int count = 0;
    list<string> canmake; //recipes it can make
    for (list<Recipe>::const_iterator r = recipes.begin(); r != recipes.end(); r++){
        if (canMakeRecipe((*r).getIngredients(), kitchen.getIngredients())){
            canmake.push_back((*r).getName());
            count++;
        }
    }
    if (count == 0){
        ostr << "No recipes can be prepared" << endl;
    }
    else{
        if (count == 1){
            ostr << "Recipe that can be prepared:" << endl;
        }
        else{
            ostr << "Recipes that can be prepared:" << endl;
        }
        canmake.sort(); //print recipes
        for (list<string>::const_iterator i = canmake.begin(); i != canmake.end(); i++){
            ostr << "  " << *i << endl;
        }
    }
}
//returns true if items in recipe can be made with items in kitchen
bool canMakeRecipe(const list<Ingredient> &recipeitems, const list<Ingredient> &kitchenitems){
    bool canmake = true;
    for (list<Ingredient>::const_iterator r = recipeitems.begin(); r != recipeitems.end(); r++){
        //is enough of ingredient there
        bool enough = false;
        for (list<Ingredient>::const_iterator k = kitchenitems.begin(); k != kitchenitems.end(); k++){
            if ((*k).getName() == (*r).getName() and (*k).getAmount() >= (*r).getAmount()){
                enough = true;
                break;
            }
        }
        if (enough == false){
            canmake = false;
            break;
        }
    }
    if (canmake == true){
        return true;
    }
    else{
        return false;
    }
}