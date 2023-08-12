#include <iostream>
#include <cstdlib>
#include <time.h>
#include "CardParent.cpp"

using namespace std;

class Card : public CardParent
{
private:
    static const string CARD_NUMBERS[];
    static const string CARD_FACES[];
    static const int CARD_VALUES[];
    bool validate_card(string number, string face);

public:
    string number;
    string face;
    Card();
    Card(string number, string face);
    int get_value();
    static Card *generate_random_card(Card used_cards[], int size_of_table);
    string to_string();
};