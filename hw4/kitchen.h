//kitchen.h

#ifndef kitchen_h
#define kitchen_h
#include <list>
#include "ingredient.h"
using namespace std;

class Kitchen{
private:
    list<Ingredient> ingredients;
public:
    Kitchen();
    list<Ingredient> getIngredients() const;
    void addIngredient(string aName, int aAmount);
    void printIngredients(ostream &ostr);
    void updateIngredients(list<Ingredient> &newingredients);
};

#endif