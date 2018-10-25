//ingredient.h

#ifndef ingredient_h
#define ingredient_h
#include <string>
using namespace std;

class Ingredient{
private:
    string name;
    int amount;
public:
    Ingredient(string name, int amount);
    string getName() const;
    int getAmount() const;
    void incAmount(int n);
    void decAmount(int n);
};

bool SortByName(const Ingredient &i1, const Ingredient &i2);
bool SortByAmount(const Ingredient &i1, const Ingredient &i2);

#endif