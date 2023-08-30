#pragma once

#ifndef __CARDFRAMEWORK__H__
#define __CARDFRAMEWORK__H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

#ifndef __CARD__
#define __CARD__

namespace CARD
{
    //Defining variables
    enum class suits { club, diamond, heart, spade }; //Lowest to highest value

    //converting to a suit
    inline suits fromInt(const int val) 
    {
        return static_cast<suits>(val);
    }
    inline suits fromChar(const char val)
    {
        if (val == toupper('C'))
            return suits::club;
        if (val == toupper('D'))
            return suits::diamond;
        if (val == toupper('H'))
            return suits::heart;
        if (val == toupper('S'))
            return suits::spade;
        return suits();
    }
    
    //card structure
    struct _card
    {   //Defining variables
        int val; //value from 1 to 13, 1 being ace, and 13 being king
        suits suit;

        //constructors
        inline _card(int value = 0)
        {
            val = (value % 52) % 13;
            suit = static_cast<suits>((value % 52) / 13);
        }
        inline _card(int value, suits suitVal)
        {
            val = value;
            suit = suitVal;
        }

        //conversions
        inline _card fromInt(const int input)
        {
            //Calculate card value and suit from input number and return
            val = (input % 52) % 13;
            suit = static_cast<suits>((input % 52) / 13);
            return *this;
        }
        inline operator int() const
        {
            return (val + (static_cast<int>(suit) * 13));
        }

        //Input/Output
        inline friend ostream& operator<<(ostream& out, const _card& rhs) {
            //Output card value
            out << setfill(' ') << setw(2) << rhs.val;

            //Ouput suit
            if (rhs.suit == suits::club)
                out << "C";
            else if (rhs.suit == suits::diamond)
                out << "D";
            else if (rhs.suit == suits::heart)
                out << "H";
            else if (rhs.suit == suits::spade)
                out << "S";

            return out;
        }
        inline friend istream& operator>>(istream& in, _card& rhs) {
            //Defining variables
            int tempInt;

            //Read in values
            in >> tempInt;
            rhs.fromInt(tempInt);

            return in;
        }
    };
}


#endif
#endif