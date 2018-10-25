#include <string>
using namespace std;

class Player{
public:
    Player();
    Player(string first, string last);
    //Accessors
    string getFirstName() const;
    string getLastName() const;
    int getMatchesWon() const;
    int getMatchesLost() const;
    int getGamesWon() const;
    int getGamesLost() const;
    float getPercMatches() const;
    float getPercGames() const;
    int getSets() const;
    int getFlawSets() const;
    float getPercFlawSets() const;
    //Modifiers
    void incMatchesWon(int x);
    void incMatchesLost(int x);
    void incGamesWon(int x);
    void incGamesLost(int x);
    void incSets(int x);
    void incFlawSets(int x);
    //Member variables
private:
    string firstname;
    string lastname;
    int matcheswon;
    int matcheslost;
    int gameswon;
    int gameslost;
    int sets;
    int flawsets;
};

bool SortByMatches(const Player &p1, const Player &p2);
bool SortByGames(const Player &p1, const Player &p2);
bool SortByFlawSets(const Player &p1, const Player &p2);