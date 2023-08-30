#pragma once

#include "framework.h"

#ifndef __CARD__H__
#define __CARD__H__

const int DECK_SIZE = 52;

class cards : protected vector<CARD::_card>
{


public:
    typedef CARD::_card card;

    //Con/Deconstructors
    cards ( bool fill = false );
    ~cards ( );

    //Manipulation                    //Fill deck with missing cards
    bool reset ( );                     //Reset to default
    bool clear ( );                     //Clear deck
    bool place (CARD::_card cardIn, int pos = 0, bool reverse = false );            //Insert card on front
    CARD::_card draw ( int pos = 0, bool reverse = false );                       //Remove front item
    bool shuffle ( );                   //Randomizes cards in deck, current iteration is biased

    //Information
    const CARD::_card peek(int pos = 0, bool reverse = false);
    const int seek (CARD::_card card, bool reverse = false );
    const bool empty();
    const int size() const;

    //Conversion


    //Operator Overloads
    const bool operator==( const cards rhs );
    friend ostream& operator<<( ostream& out, const cards& rhs);
    friend ifstream& operator>>(ifstream& in, cards& rhs);
    friend bool operator==( const CARD::_card lhs, const CARD::_card rhs );
    friend bool operator!=( const CARD::_card lhs, const CARD::_card rhs );
    

protected:
};

inline ostream& operator<<(ostream& out, const cards& rhs)
{
    int size = rhs.size();

    for (int i = 0; i < size; ++i)
    {
        out << rhs.at(i) << " ";

        if ((i % 13) == 12)
            out << endl;
    }

    return out;
}

inline ifstream& operator>>(ifstream& in, cards& rhs)
{
    //Defining variables
    int tempInt;
    CARD::_card tempCard;

    //While cards can still be read from the file
    while (in >> tempInt)
    {
        rhs.place(tempCard.fromInt(tempInt), 0, true);
    }

    return in;
}

inline bool operator==(const CARD::_card lhs, const CARD::_card rhs)
{
    if (lhs.suit == rhs.suit && lhs.val == rhs.val)
        return true;
    return false;
}

inline bool operator!=(const CARD::_card lhs, const CARD::_card rhs)
{
    if (lhs.suit == rhs.suit && lhs.val == rhs.val)
        return false;
    return true;
}


#endif