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

deck& deck::operator=(const deck& rhs)
{
    clear();

    for (size_type i = 0; i < rhs.size(); ++i)
        insert(rhs.at(i), i);

}

// Overloads
bool deck::operator==(const deck& rhs)
{
    size_type deckSize = size();

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

bool card::operator==(const card rhs) {
    return 0;
}

constexpr bool Suit::operator==(Suit a) const
{
    return value == a.value;
}

constexpr bool Suit::operator!=(Suit a) const
{
    return value != a.value;
}

constexpr bool Suit::IsBlack() const
{
    return (value == club) || (value == spade);
}

constexpr bool Suit::IsRed() const
{
    return (value == heart) || (value == diamond);
}

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

ostream &operator<<(ostream &out, const Suit &rhs)
{
    out << rhs.toChar();

    return out;
}

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

bool Card::operator==(const Card rhs)
{
    if (_suit == rhs._suit)
        if(_rank == rhs._rank)
            return true;
    return false;
}

bool Card::operator!=(const Card rhs)
{
    if (_suit == rhs._suit)
        if(_rank == rhs._rank)
            return false;
    return true;
}
