#pragma once
#include "framework.h"

#ifndef __WAR__H__
#define __WAR__H__

class war : protected cards {

public:
    war(bool start = true);
    war(cards deckIn, bool start = true);
    ~war();

    //Game backend functions
    bool manual();
    bool setHands();
    bool playGame();
    bool iterateGame();
    bool playRound();
    int compare(); //Positive if discard 1 is greater, negative if discard 2 is greater

    //Information functions
    bool winner(int& player);
    int numRounds();
    cards hand(bool player /*true for player 1, false for player 2*/);

    friend bool startWar();

protected:
    cards deck, hand1, hand2, disc1, disc2;
    int rounds = 0;
};

bool startWar()
{
    int winner;
    char choice;

    do
    {
        cout << char(201) << setw(10) << char(187) << endl
            << char(186) << " Welcome " << char(186) << endl
            << char(186) << " to War! " << char(186) << endl
            << char(200) << setw(10) << char(188) << endl << endl;

        cout << "How do you want to play? (enter mode number)\n"
            << " 1: test (spits out winner)\n"
            << " 2: against bot\n\n"

            << " 0: return to menu\n\nChoice: ";

        cin >> choice;

        cout << "\n\n\n\n\n\n\n\n\n" << endl;

        if (choice == '1')
        {

            war game;
            game.winner(winner);

            cout << "Player " << winner << " wins after " << game.numRounds() << " number of rounds!" << endl;
        }
        else if (choice == '2')
        {
            war game(false);
            game.manual();
        }
        else if (choice == '0')
        {
            cout << "Ok, returning to menu" << endl;
        }
        else
        {
            cout << "INVALID CHOICE" << endl;
        }

    } while (choice != '0');

    return false;
}




#endif