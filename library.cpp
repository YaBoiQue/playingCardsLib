#include "library.h"

typedef Deck::Iterator Iterator;

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
    Suit tmpsuit = Suit(rhs);
    return tmpsuit;
}

Suit &Suit::operator=(const int &rhs)
{
    Suit tmpsuit = Suit(rhs);
    if (fromInt(rhs)) 
        return tmpsuit;
    return;
}

Suit &Suit::operator=(const char &rhs)
{
    Suit tmpsuit = Suit(rhs);
    if(fromChar) 
        return tmpsuit;
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

Card::Card(Card &&card)
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

Card &Card::operator=(Card &&rhs)
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
        out << rhs.peek(rhs.begin() + i);
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
        rhs.insert((tempCard = Card(tempInt)), rhs.end());
    }

    return in;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_CARD


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_ITERATOR
#define PLAYINGCARDSLIB_LIBRARY_CPP_ITERATOR

Card &Deck::Iterator::operator*()
{
    return _node->next->card;
}

Iterator &Deck::Iterator::operator+(int rhs)
{
    for (int i = 0; i < rhs; ++i)
    {
        _node = _node->next;
    }
}

Iterator &Deck::Iterator::operator-(int rhs)
{
    for (int i = 0; i < rhs; ++i)
    {
        _node = _node->prev;
    }
}

Deck::Iterator &Deck::Iterator::operator++()
{
    _node = _node->next;
    return *this;
}

Deck::Iterator &Deck::Iterator::operator++(int)
{
    Iterator tmp = *this;
    _node = _node->next;
    return tmp;
}

Deck::Iterator &Deck::Iterator::operator--()
{
    _node = _node->prev;
    return *this;
}

Iterator &Deck::Iterator::operator--(int)
{
    Iterator tmp = *this;
    _node = _node->prev;
    return tmp;
}

#endif


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_DECK
#define PLAYINGCARDSLIB_LIBRARY_CPP_DECK

//De/Constructors
Deck::Deck(bool fill)
{
    head = tail = new Node();

    if (fill)
        reset();
}

Deck::Deck(const Deck& old)
{
    Node *copyptr = old.head, *newnode;

    while (copyptr != nullptr)
    {
        insert(copyptr->card, end());
        copyptr = copyptr->next;
    }
}

Deck::Deck(Deck&& old)
{
    Node *copyptr = old.head, *newnode;

    while (copyptr != nullptr)
    {
        insert(copyptr->card, end());
        copyptr = copyptr->next;
    }
}

Deck::~Deck()
{
    Node *tmpptr;

    while (head != nullptr)
    {
        tmpptr = head;
        head = head->next;
        delete tmpptr;
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
        insert(Card(i), end());
}

Card &Deck::draw(Iterator& pos)
{
    Node *ptr = pos._node->next;
    Card card = Card(ptr->card);

    pos._node->next = ptr->next;
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    delete ptr;
    return card;
}

Iterator Deck::remove(Iterator pos)
{
    Node *ptr = pos._node->next;

    pos._node->next = ptr->next;
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    delete ptr;
    return pos;
}

Iterator Deck::insert(const Card &in, Iterator pos)
{
    Node *newNode = new Node(Card(in), pos._node->next, pos._node);
    if (pos._node == tail) tail = newNode;
    pos._node->next->prev = newNode;
    pos._node->next = newNode;
    return pos;
}

//Information
Deck::Iterator Deck::begin() const
{
    return Iterator(head);
}

Deck::Iterator Deck::end() const
{
    return Iterator(tail);
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

Card &Deck::peek(Iterator pos) const
{
    Card card = Card(pos._node->next->card);
    return card;
}

Iterator Deck::seek(const Card &search, Iterator start) const
{
    start = (start == nullptr) ? begin() : start;
    Iterator tmpIt = start;

    while (tmpIt._node->next != tail)
    {
        if (tmpIt._node->next->card == search)
        {
            return tmpIt;
        }
    }

    return Iterator(nullptr);
    
}

//Overloads
Deck& Deck::operator=(const Deck& rhs)
{
    Node *tmpptr = rhs.head;

    clear();

    while(tmpptr != nullptr)
    {
        insert(tmpptr->card, end());
        tmpptr = tmpptr->next;
    }

    return *this;
}

Deck &Deck::operator=(Deck &&rhs)
{
    Node *tmpptr = rhs.head;

    clear();

    while(tmpptr != nullptr)
    {
        insert(tmpptr->card, end());
        tmpptr = tmpptr->next;
    }

    return *this;
}

bool Deck::operator==(const Deck& rhs)
{
    size_type deckSize = size();
    Node *lhsptr = head;
    Node *rhsptr = rhs.head;

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
        {
            return false;
        }
        
        lhsptr = lhsptr->next;
        rhsptr = rhsptr->next;
    }

    return true;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_DECK