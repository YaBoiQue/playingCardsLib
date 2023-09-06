#include "library.h"

deck::deck(bool fill){
    if (fill)
        reset();
    
    return;
}

deck::deck(deck& old){
    size_type size = old.size();
    clear();
    for (size_type i = 0; i < size; ++i)
        insert(old.peek(i), i);
}

deck::~deck() = default;

//Manipulation
void deck::reset(){
    clear();
    for (int i = 0; i < 52; ++i)
        insert(card(i), i);
}


void deck::shuffle(unsigned seed){
    seed = (seed == 0) ? chrono::system_clock::now().time_since_epoch().count() : seed;
    default_random_engine rng(seed);

    std::shuffle(begin(), end(), rng);
}


bool deck::cut(size_type at){
    size_type tmpsize = size();

    if (at > tmpsize - 1)
        return false;

    srand(time(0));
    at = (at == 0) ? rand()%tmpsize : at;

    for (size_type i = 0; i < at; ++i)
        insert(draw(), tmpsize-1);

    return true;
}


card deck::draw(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    if (pos > tmpsize)
        return card(52);

    pos = (reverse) ? tmpsize - pos : pos;

    card tmp = peek(pos);
    remove(pos);
    return tmp;
}


bool deck::remove(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    if (pos > tmpsize)
        return false;

    pos = (reverse) ? tmpsize - pos : pos;
    
    erase(begin() + pos);
    return true;
}


bool deck::insert(card in, int pos, bool reverse, bool duplicates){
    size_type tmpsize = size();

    if ( pos > tmpsize)
        return false;

    pos = (reverse) ? tmpsize - pos : pos;

    vector::insert(begin() + pos, in);

    return true;
}



//Data
card deck::peek(int pos, bool reverse){
    size_type tmpsize = size() - 1;

    if (pos > tmpsize)
        return card(52);

    pos = (reverse) ? tmpsize - pos : pos;

    return at(pos);
}

int deck::seek(card search, int start, bool reverse)
{
    size_type tmpsize = size();

    for (size_type i = start; i < tmpsize; ++i){
        if (at(i) == search){
            i = (reverse) ? tmpsize - 1 - i : i;
            return i;
        }
    }
    return -1;
}

const deck deck::operator=(const deck rhs)
{
    clear();

    for (size_type i = 0; i < rhs.size(); ++i)
        insert(rhs.at(i), i);

    return false;
}

// Overloads
const bool deck::operator==(deck rhs)
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