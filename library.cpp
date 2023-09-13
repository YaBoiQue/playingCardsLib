#include "library.h"

#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_SUIT
#define PLAYINGCARDSLIB_LIBRARY_CPP_SUIT

//Information
constexpr bool Suit::IsBlack() const
{
    return ((value == club) || (value == spade));
}

constexpr bool Suit::IsRed() const
{
    return ((value == heart) || (value == diamond));
}

constexpr int Suit::toInt() const
{
    return static_cast<int>(value);
}

constexpr char Suit::toChar() const
{
    switch (value)
    {
        case club:
            return 'C';
        case diamond:
            return 'D';
        case heart:
            return 'H';
        case spade:
            return 'S';
        default:
            return 'E';
    }
}

//Manipulations
constexpr bool Suit::fromInt(const int &val)
{
    if (val > 3) { return false; }
    value = static_cast<Value>(val); 
}

constexpr bool Suit::fromChar(const char &val)
{
    switch(toupper(val)){
        case 'C':
            value = club;
            break;
        case 'D':
            value = diamond;
            break;
        case 'H':
            value = heart;
            break;
        case 'S':
            value = spade;
            break;
        default:
            return false;
    }
    return true;
}

//Overload Operators
Suit &Suit::operator=(const Suit &rhs)
{
    value = rhs.value;
    return Suit(rhs);
}

Suit &Suit::operator=(const int &rhs)
{
    if (fromInt(rhs)) 
        return Suit(rhs);
    return;
}

Suit &Suit::operator=(const char &rhs)
{
    if(fromChar) 
        return Suit(rhs);
    return;
}

int &Suit::operator*(const int &rhs) const
{
    int tmp = toInt();
    tmp = tmp * rhs;
    return tmp;    
}

constexpr bool Suit::operator==(Suit a) const
{
    return value == a.value;
}

constexpr bool Suit::operator!=(Suit a) const
{
    return value != a.value;
}

//Input/Output
ostream &operator<<(ostream &out, const Suit &rhs)
{
    out << rhs.toChar();

    return out;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_SUIT


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_DECK
#define PLAYINGCARDSLIB_LIBRARY_CPP_DECK

//De/Constructors
deck::deck(bool fill)
{
    headptr = nullptr;
    tailptr = nullptr;

    if (fill)
        reset();
}

deck::deck(deck& old)
{
    node *copyptr;
    Card tmp;

    copyptr = old.headptr;

    while (copyptr != nullptr)
    {
        tmp = copyptr->card;
        insert(tmp, 0, true, true);
        copyptr = copyptr->next;
    }
}

deck::~deck()
{
    node *tmpptr = headptr;

    while (tmpptr != nullptr)
    {
        headptr = tmpptr->next;
        delete tmpptr;
        tmpptr = headptr;
    }

    tailptr == nullptr;
}

//Manipulations
void deck::clear()
{
    node *tmpptr;
    while(headptr != nullptr)
    {
        tmpptr = headptr;
        headptr = headptr->next;
        delete tmpptr;
    }

    tailptr = nullptr;
}

void deck::reset()
{
    clear();
    for (int i = 0; i < 52; ++i)
        insert(Card(i));
}

bool deck::cut(size_type at){
    size_type tmpsize = size();
    node *tmpptr = headptr;

    if (at > tmpsize - 1)
        return false;

    srand(time(0));
    at = (at == 0) ? rand()%tmpsize : at;

    for (int i = 0; i < at; ++i)
        tmpptr = tmpptr->next;

    tailptr->next = headptr;
    headptr->prev = tailptr;
    tailptr = tmpptr->prev;
    tmpptr->prev->next = nullptr;
    headptr = tmpptr;
    tmpptr->prev = nullptr;

    return true;
}

Card& deck::draw(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    node *tmpptr = headptr;
    Card tmp;

    if (pos > tmpsize)
        return;

    pos = (reverse) ? tmpsize - pos : pos;

    for (int i = 0; i < pos; ++i)
    {
        tmpptr = tmpptr->next;
    }

    tmp = tmpptr->card;
    tmpptr->prev->next = tmpptr->next;
    tmpptr->next->prev = tmpptr->prev;

    delete tmpptr;

    return tmp;
}

bool deck::remove(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    node *tmpptr = headptr;

    if (pos > tmpsize)
        return false;

    pos = (reverse) ? tmpsize - pos : pos;
    
    for (int i = 0; i < pos; ++i)
    {
        tmpptr = tmpptr->next;
    }

    tmpptr->next->prev = tmpptr->prev;
    tmpptr->prev->next = tmpptr->next;
    delete tmpptr;

    return true;
}

bool deck::insert(const Card& in, int pos, bool reverse, bool duplicates){
    size_type tmpsize = size();
    node *tmpptr = headptr, *tmp;

    tmp = new node();

    if (tmp == nullptr)
    {
        return false;
    }

    if ( pos > tmpsize)
        return false;

    pos = (reverse) ? tmpsize - pos : pos;

    for(int i = 0; i < pos; ++i)
    {
        tmpptr = tmpptr->next;
    }

    tmp->card = in;

    if(headptr == nullptr)
    {
        headptr = tmp;
        tailptr = tmp;
        return true;
    }

    if(tmpsize == pos)
    {
        tmp->prev = tailptr;
        tailptr->next = tmp;
        tailptr = tmp;
        return true;
    }

    if(pos == 0)
    {
        tmp->next = headptr;
        headptr->prev = tmp;
        headptr = tmp;
        return true;
    }

    tmpptr->prev->next = tmp;
    tmpptr->prev = tmp;

    tmp->prev = tmpptr->prev;
    tmp->next = tmpptr;
    tmp->prev->next = tmp;
    tmp->next->prev = tmp;

    return true;
}

bool deck::insert(const Card &in, bool back)
{
    node *tmp;
    
    tmp = new node();

    if(tmp == nullptr)
        return false;

    tmp->card = in;

    if(headptr == nullptr)
    {
        headptr = tmp;
        tailptr = tmp;
        return true;
    }

    if (back)
    {
        tmp->prev = tailptr;
        tailptr->next = tmp;
        tailptr = tmp;
        return true;
    }

    tmp->next = headptr;
    headptr->prev = tmp;
    headptr = tmp;
    return true;
}

//Data
Card& deck::peek(int pos, bool reverse)const
{
    size_type tmpsize = size() - 1;
    node *tmpptr = headptr;
    Card tmp;

    if (pos > tmpsize)
        return;

    pos = (reverse) ? tmpsize - pos : pos;

    for (int i = 0; i < pos; ++i)
        tmpptr = tmpptr->next;

    tmp = tmpptr->card;

    return tmp;
}

int deck::seek(const Card& search, int start, bool reverse)const
{
    size_type tmpsize = size();
    node *tmpptr = headptr;
    Card tmpcard;

    for (size_type i = 0; i < start; ++i)
        tmpptr=tmpptr->next;

    for (size_type i = start; i < tmpsize; ++i){
        tmpcard = tmpptr->card;
        tmpptr = tmpptr->next;

        if (tmpcard == search){
            i = (reverse) ? tmpsize - 1 - i : i;
            return i;
        }
    }
    return -1;
}

size_type deck::size() const
{
    node *tmpptr = headptr;
    size_type size = 0;

    while (tmpptr != nullptr)
    {
        ++size;
        tmpptr = tmpptr->next;
    }

    return size;
}

bool deck::empty() const
{
    if (headptr == nullptr)
        return true;
    return false;
}

//Overloads
deck& deck::operator=(const deck& rhs)
{
    node *tmpptr = rhs.headptr;

    clear();

    while(tmpptr != nullptr)
    {
        insert(tmpptr->card);
        tmpptr = tmpptr->next;
    }

    return *this;
}

bool deck::operator==(const deck& rhs)
{
    size_type deckSize = size();
    node *lhsptr = headptr, *rhsptr = rhs.headptr;

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

    while(lhsptr != nullptr && rhsptr != nullptr)
    {
        if (lhsptr->card != rhsptr->card)
            return false;
        
        lhsptr = lhsptr->next;
        rhsptr = rhsptr->next;
    }

    return true;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_DECK


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_CARD
#define PLAYINGCARDSLIB_LIBRARY_CPP_CARD

Card::Card(int value)
{
    _rank = (value % 52) % 13;
    _suit = (value % 52) / 13;
}

Card::Card(int rank, Suit suit)
{
    rank = rank % 13;
    _rank = rank;
    _suit = suit;
}

Card::Card(int rank, int suit)
{
    rank = rank % 13;
    suit = suit % 4;
    _rank = rank;
    _suit = suit;
}

Card::Card(const Card &card)
{
    _rank = card._rank;
    _suit = card._suit;
}

Card::Card(const Card *card)
{
    _rank = card->_rank;
    _suit = card->_suit;
}

void Card::set(int rank, Suit suit)
{
    rank = rank % 13;
    _rank = rank;
    _suit = suit;
}

void Card::set(int rank, int suit)
{
    rank = rank % 13;
    suit = suit % 4;
    _rank = rank;
    _suit = suit;
}

int Card::value() const
{
    return _rank + (_suit * 13);
}

Suit Card::suit() const
{
    return _suit;
}

int Card::rank() const
{
    return _rank;
}

Card &Card::operator=(const int &rhs)
{
    _rank = (rhs % 52) % 13;
    _suit = (rhs % 52) / 13;

    return *this;
}

Card &Card::operator=(const Card &rhs)
{
    _rank = rhs._rank;
    _suit = rhs._suit;

    return *this;
}

bool Card::operator==(const Card &rhs)
{
    if (_suit == rhs._suit)
        if(_rank == rhs._rank)
            return true;
    return false;
}

bool Card::operator!=(const Card& rhs)
{
    if (_suit == rhs._suit)
        if(_rank == rhs._rank)
            return false;
    return true;
}

ostream &operator<<(ostream &out, const Card &rhs)
{
    //Output card value
    out << setfill(' ') << setw(2) << rhs.value();

    //Ouput suit
    out << rhs.suit();

    return out;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_CARD