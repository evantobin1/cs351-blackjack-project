#include "Card.h"

const string Card::CARD_NUMBERS[] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
const int Card::CARD_VALUES[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const string Card::CARD_FACES[] = {"heart", "diamond", "spade", "club"};

Card::Card()
{
    number = "";
    face = "";
};

Card::Card(string number, string face)
{
    this->number = number;
    this->face = face;
    if (!validate_card(number, face))
        throw std::invalid_argument("this is not a valid card");
};

int Card::get_value()
{
    for (int i = 0; i < (sizeof(CARD_NUMBERS) / sizeof(string)); i++)
    {
        if (CARD_NUMBERS[i] == number)
            return CARD_VALUES[i];
    }
    return -1;
}

Card *Card::generate_random_card(Card used_cards[], int size_of_table)
{
    srand(time(0));
    string random_card_number;
    string random_card_face;

    // Keep generating a random card until you find one that isn't already in the hand
    bool is_unique_card = false;
    while (!is_unique_card)
    {
        is_unique_card = true;
        random_card_number = CARD_NUMBERS[(int)(rand()) % (sizeof(CARD_NUMBERS) / sizeof(string))];
        random_card_face = CARD_FACES[(int)(rand()) % (sizeof(CARD_FACES) / sizeof(string))];

        for (int i = 0; i < (size_of_table); i++)
        {
            if (used_cards[i].number == random_card_number && used_cards[i].face == random_card_face)
                is_unique_card = false;
        }
    }

    return new Card(random_card_number, random_card_face);
};

bool Card::validate_card(string number, string face)
{
    bool isNumberValidated = false;
    bool isFaceValidated = false;
    for (int i = 0; i < sizeof(CARD_NUMBERS) / sizeof(string); i++)
    {
        if (number == CARD_NUMBERS[i])
        {
            isNumberValidated = true;
            break;
        }
    }
    for (int i = 0; i < sizeof(CARD_NUMBERS) / sizeof(string); i++)
    {
        if (face == CARD_FACES[i])
        {
            isFaceValidated = true;
            break;
        }
    }
    return isNumberValidated && isFaceValidated;
};

string Card::to_string()
{
    if (number == "" && face == "")
        return "Blank Card";
    return ("\e[1m" + number + " of " + face + "s\e[0m");
};