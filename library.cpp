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

inline ostream &operator<<(ostream &out, const Deck &rhs)
{
    size_type size = rhs.size();

    for (size_type i = 0; i < size; ++i)
    {
        out << rhs.peek(i);
    }

    return out;
}

ifstream &operator>>(ifstream &in, Deck &rhs)
{
    //Defining variables
    int tempInt;
    Card tempCard;

    //While cards can still be read from the file
    while (in >> tempInt)
    {
        rhs.insert((tempCard = Card(tempInt)), 0, true);
    }

    return in;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_CARD


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_DECK
#define PLAYINGCARDSLIB_LIBRARY_CPP_DECK

//De/Constructors
Deck::Deck(bool fill)
{
    head = NULL;
    tail = NULL;

    if (fill)
        reset();
}

Deck::Deck(Deck& old)
{
    Iterator copy;
    Card tmp;

    copy = old.head;

    while (copy != NULL)
    {
        tmp = copy._node->card;
        insert(tmp, 0, true, true);
        ++copy;
    }
}

Deck::~Deck()
{
    Node *tmpptr = head;

    while (tmpptr != nullptr)
    {
        head = tmpptr->next;
        delete tmpptr;
        tmpptr = head;
    }

    tail == nullptr;
}

//Manipulations
void Deck::clear()
{
    Node *tmpptr;
    while(head != nullptr)
    {
        tmpptr = head;
        head = head->next;
        delete tmpptr;
    }

    tail = nullptr;
}

void Deck::reset()
{
    clear();
    for (int i = 0; i < 52; ++i)
        insert(Card(i));
}

void Deck::shuffle(unsigned seed)
{
    Node *slowptr = head, *fastptr = head;

    while (fastptr != nullptr)
    {

    }
}



bool Deck::cut(size_type at){
    size_type tmpsize = size();
    Node *tmpptr = head;

    if (at > tmpsize - 1)
        return false;

    srand(time(0));
    at = (at == 0) ? rand()%tmpsize : at;

    for (int i = 0; i < at; ++i)
        tmpptr = tmpptr->next;

    tail->next = head;
    head->prev = tail;
    tail = tmpptr->prev;
    tmpptr->prev->next = nullptr;
    head = tmpptr;
    tmpptr->prev = nullptr;

    return true;
}

Card& Deck::draw(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    Node *tmpptr = head;
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

bool Deck::remove(int pos, bool reverse){
    size_type tmpsize = size() - 1;
    Node *tmpptr = head;

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

    Node* tmp = head;
    tmp++;
}

bool Deck::insert(const Card& in, int pos, bool reverse, bool duplicates){
    size_type tmpsize = size();
    Node *tmpptr = head, *tmp;

    tmp = new Node();

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

    if(head == nullptr)
    {
        head = tmp;
        tail = tmp;
        return true;
    }

    if(tmpsize == pos)
    {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        return true;
    }

    if(pos == 0)
    {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
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

bool Deck::insert(const Card &in, bool back)
{
    Node *tmp;
    
    tmp = new Node();

    if(tmp == nullptr)
        return false;

    tmp->card = in;

    if(head == nullptr)
    {
        head = tmp;
        tail = tmp;
        return true;
    }

    if (back)
    {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        return true;
    }

    tmp->next = head;
    head->prev = tmp;
    head = tmp;
    return true;
}

//Data
Card& Deck::peek(int pos, bool reverse)const
{
    size_type tmpsize = size() - 1;
    Node *tmpptr = head;
    Card tmp;

    if (pos > tmpsize)
        return;

    pos = (reverse) ? tmpsize - pos : pos;

    for (int i = 0; i < pos; ++i)
        tmpptr = tmpptr->next;

    tmp = tmpptr->card;

    return tmp;
}

int Deck::seek(const Card& search, int start, bool reverse)const
{
    size_type tmpsize = size();
    Node *tmpptr = head;
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

size_type Deck::size() const
{
    Node *tmpptr = head;
    size_type size = 0;

    while (tmpptr != nullptr)
    {
        ++size;
        tmpptr = tmpptr->next;
    }

    return size;
}

bool Deck::empty() const
{
    if (head == nullptr)
        return true;
    return false;
}

//Overloads
Deck& Deck::operator=(const Deck& rhs)
{
    Node *tmpptr = rhs.head;

    clear();

    while(tmpptr != nullptr)
    {
        insert(tmpptr->card);
        tmpptr = tmpptr->next;
    }

    return *this;
}

bool Deck::operator==(const Deck& rhs)
{
    size_type deckSize = size();
    Node *lhsptr = head, *rhsptr = rhs.head;

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

