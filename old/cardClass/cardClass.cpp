#include "framework.h"
#include "cardClass.h"


cards::cards( bool fill )
{
    if (fill)
        reset();

    return;
}

cards::~cards()
{
}

bool cards::reset()
{
    //Defining variables
    card tempCard;

    //If cleared correctly
    if (clear())
    {
        //Fill with entire set of cards
        for (int i = 0; i < DECK_SIZE; ++i)  
        {
            if (!place(tempCard.fromInt(i)))
                return false;
        }

        return true;
    }
    return false;
}

bool cards::clear()
{
    vector::clear();

    if (!empty())
        return false;

    return true;
}

bool cards::place(CARD::_card cardIn, int pos, bool reverse)
{
    //Defining variables
    int initSize = size();



    if (empty())
    {
        insert(begin(), cardIn);
        if (empty())
            return false;
        return true;
    }

    if (pos > initSize)
    {
        push_back(cardIn);

        if (initSize == size())
            return false;
        return true;
    }

    if (reverse)
        pos = initSize - pos;

    insert(begin() + pos, cardIn);

    if (initSize == size())
        return false;
    return true;
}

CARD::_card cards::draw(int pos, bool reverse)
{
    //Defining variables
    int initSize = size();
    int cardPos = pos;
    CARD::_card tempCard;

    if (empty())
        return CARD::_card();

    if (pos > size())
    {
        if (reverse)
        {
            tempCard = front();
            erase(begin());
        }
        else
        {
            tempCard = back();
            erase(end());
        }

        return tempCard;
    }

    if (reverse)
    {
        cardPos = size() - pos;
    }

    tempCard = at(cardPos);

    erase(begin() + cardPos);

    return tempCard;
}


bool cards::shuffle()
{
    //Defining variables
    cards temp = *this;
    card tempCard;
    vector<bool> track;
    int num = size();
    int i, to, numUsed = 0;

    srand(int(time(0)));

    //Check if empty
    if (empty())
        return true;

    track.resize(num);

    //Randomize cards for each card in deck
    for (i = 0; i < num; ++i)
    {
        to = rand() % (num - int(i));

        tempCard = at(i);
        at(i) = at(to);
        at(to) = tempCard;
    }


    return true;
}


const CARD::_card cards::peek(int pos, bool reverse)
{
    int cardPos = pos;

    if (pos > size())
        return CARD::_card();

    if (reverse)
        cardPos = size() - pos;

    return at(cardPos);
}

const int cards::seek(CARD::_card card, bool reverse)
{
    int deckSize = size();

    if (empty())
        return -1;

    for (int i = 0; i < deckSize; ++i)
    {
        if (at(i) == card)
        {
            if (reverse)
                return (deckSize - i);
            return i;
        }
    }

    return -1;
}

const bool cards::empty()
{
    if (size() == 0)
        return true;
    return false;
}

const int cards::size() const
{
    return int(vector::size());
}

const bool cards::operator==(cards rhs)
{
    int deckSize = size();

    if (empty())
    {
        if (rhs.empty())
            return true;
        return false;
    }
    else if (rhs.empty())
        return false;

    if (deckSize != rhs.size())
        return false;

    for (int i = 0; i < deckSize; ++i)
        if (at(i) != rhs.at(i))
            return false;

    return true;
}