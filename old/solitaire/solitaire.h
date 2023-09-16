#pragma once

#include "framework.h"

#ifndef __SOLITAIRE__H__
#define __SOLITAIRE__H__

class solitaire : protected cards {
    class foundationClass:public cards {
        CARD::suits suit;

    public:
        //Con/Deconstructors
        foundationClass(char value = 'n') {
            suit = CARD::fromChar(value);
        }
        ~foundationClass() {}

        //Information
        inline bool valid(int num, bool reverse = false) {
            int temp = peek().val;

            //If order is reversed
            if (reverse) {
                for (int i = 1; i < num; ++i) {
                    if (peek(i).val != (temp - 1)) {
                        return false;
                    }
                }
            }
            //Order is foreword
            else {
                for (int i = 1; i < num; ++i) {
                    if (peek(i).val != (temp + 1)) {
                        return false;
                    }
                }
            }
        }

        //Modifications
        inline bool modSuit(CARD::suits value) { 
            suit = value; 
            return true;
        }
        inline bool place(CARD::_card cardIn, int pos = 0, bool reverse = false) { 
            if (cardIn.suit == suit)
                return cards::place(cardIn, pos, reverse);
            return false;
        }
        inline bool move(foundationClass dest, int num) {
            stack<card> temp;
            if (valid(num)) {
                for (int i = 0; i < num; ++i) {
                    temp.push(draw());
                }
                if (dest.peek().val == (temp.top().val + 1)) {
                    while (!temp.empty()) {
                        dest.place(temp.top());
                        temp.pop();
                    }
                }
                return true;
            }
            return false;
        }
    };
    class tableauClass:public cards {
    public:
        //Con/Deconstructors
        tableauClass() {};
        ~tableauClass() {};
    };

    tableauClass tableau[7];
    foundationClass foundation[4];
    cards discard;
    cards moving;

public:
    //Con/Deconstructors
    solitaire(cards deck) { 
        foundation[0].modSuit(CARD::suits::club);
        foundation[1].modSuit(CARD::suits::diamond);
        foundation[2].modSuit(CARD::suits::heart);
        foundation[3].modSuit(CARD::suits::spade);
    };
    solitaire(bool prepare = false);
    ~solitaire();

    //Game Format functions
    bool prepare();
    bool checkValues();
    bool checkColors();
    bool checkStack();


    //Manipulation Functions
    bool clear(bool prepare = false);
    bool setTableau();
    bool discard();
    bool moveCard(bool checkStack = true, bool checkPlacement = true);
    bool moveStack(int pos, bool checkStack = true, bool checkPlacement = true);

    //Information Functions




    friend bool startSolitaire();
};

bool startSolitaire() {
    return true;
}





#endif