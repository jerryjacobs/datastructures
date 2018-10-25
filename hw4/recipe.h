//recipe.h

#ifndef recipe_h
#define recipe_h
#include <list>
#include "ingredient.h"
using namespace std;

class Recipe{
private:
    string name;
    list<Ingredient> ingredients;
public:
    Recipe();
    Recipe(string aName);
    string getName() const;
    list<Ingredient> getIngredients() const;
    void addIngredient(string name, int amount);
    void printIngredients(ostream &ostr);
};

#endif