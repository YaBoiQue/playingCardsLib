#include "library.h"

//Manipulation
void reset(){
    clear();
    for (int i = 0, i < 52, ++i)
        .insert(card(i), i);
}
void shuffle(unsigned int seed = 0){
    seed = (seed == 0) ? chrono::system_clock::now().time_since_epoch().count() : seed;
    default_random_engine rng(seed);

    std::shuffle(.begin(), .end(), rng);
}   //Shuffles cards in deck
deck cut(size_type spot = 0);    //Cuts deck (shuffles without changing order)
card draw(int pos = 0, bool reverse = false);   //Draws card from dec (removes and outputs card)
bool remove(int pos = 0, bool reverse = false); //Removes card from deck (removes card)
bool insert(card in, int pos = 0, bool reverse = false, bool duplicates = false);    //Inserts card into deck

//Data
card peek(int pos = 0, bool reverse = false);
size_type seek (card search, size_type start = 0, bool reverse = false);



//Overloads
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