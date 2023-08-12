#include <iostream>
#include <stdlib.h>
#include "Card.h"

using namespace std;

#define SIZE_OF_TABLE_HAND 20 // Max capacity of both the dealer and the player's cards combined

int main()
{
    try
    {

        system("Color 0C");
        cout << "\n\n\e[1mWelcome to Evan's Blackjack" << endl;
        cout << "\e[0mNote: Ace always counts for one because I don't wanna code it :/ " << endl;

        while (true)
        {
            bool has_busted = false;
            string input = "";
            cout << "Play hand? (y/n): ";
            cin >> input;
            if (input == "n")
            {
                // When leaving the game, I'm creating a new goodybe card to utilize its parent class's built in "goodbye method"
                Card *goodbye_card = new Card();
                goodbye_card->say_goodbye();
                cout << "Closing game" << endl;
                return 0;
            }
            else if (input != "y")
            {
                cout << "Gimme a real input bro :/" << endl;
                continue;
            }

            Card cards_on_table[SIZE_OF_TABLE_HAND];

            int player_card_count = 0, player_card_total = 0;
            int dealer_card_count = 0, dealer_card_total = 0;
            // Deal initial cards
            cards_on_table[player_card_count++] = *Card::generate_random_card(cards_on_table, SIZE_OF_TABLE_HAND);
            cards_on_table[player_card_count++] = *Card::generate_random_card(cards_on_table, SIZE_OF_TABLE_HAND);
            player_card_total += (cards_on_table[0].get_value() + cards_on_table[1].get_value());

            cards_on_table[SIZE_OF_TABLE_HAND / 2 + dealer_card_count++] = *Card::generate_random_card(cards_on_table, SIZE_OF_TABLE_HAND);
            dealer_card_total += (cards_on_table[SIZE_OF_TABLE_HAND / 2].get_value());

            cout << "\nYou are dealt the " << cards_on_table[0].to_string() << " and the " << cards_on_table[1].to_string() << ". TOTAL: " << player_card_total << endl;
            cout << "The dealer is dealt the " << cards_on_table[SIZE_OF_TABLE_HAND / 2].to_string() << ". TOTAL: " << dealer_card_total << "\n"
                 << endl;

            while (true)
            {
                cout << "Would you like to hit or stand (h/s): ";
                cin >> input;
                if (input == "s")
                    break;
                else if (input != "h")
                {
                    cout << "Gimme a real input bro :/" << endl;
                    continue;
                }

                cards_on_table[player_card_count++] = *Card::generate_random_card(cards_on_table, SIZE_OF_TABLE_HAND);
                player_card_total += cards_on_table[player_card_count - 1].get_value();
                cout << "You pulled the " << cards_on_table[player_card_count - 1].to_string() << ". TOTAL: " << player_card_total << endl;

                if (player_card_total > 21)
                {
                    cout << "BUST" << endl;
                    has_busted = true;
                    break;
                }
            }

            cout << "\n\n";
            while (true && !has_busted)
            {
                if (dealer_card_total > 21)
                {
                    cout << "\e[1mYou win!\n\n\e[0m"
                         << endl;
                    break;
                }
                if (dealer_card_total > player_card_total)
                {
                    cout << "\e[1mYou lose!\n\n\e[0m"
                         << endl;
                    break;
                }
                cards_on_table[(SIZE_OF_TABLE_HAND / 2) + dealer_card_count++] = *Card::generate_random_card(cards_on_table, SIZE_OF_TABLE_HAND);
                dealer_card_total += cards_on_table[(SIZE_OF_TABLE_HAND / 2) + dealer_card_count - 1].get_value();
                cout << "Dealer pulled the " << cards_on_table[(SIZE_OF_TABLE_HAND / 2) + dealer_card_count - 1].to_string() << ". TOTAL: " << dealer_card_total << endl;
            }
        }
    }
    catch (const std::exception &)
    {
        cout << "Error, closing game" << endl;
        return 1;
    }

    return 0;
}
