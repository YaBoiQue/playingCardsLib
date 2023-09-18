#include "library.h"

typedef Deck::Iterator Iterator;

#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_SUIT
#define PLAYINGCARDSLIB_LIBRARY_CPP_SUIT

//Information
constexpr bool Suit::IsBlack() const
{
    //Return true if club or spade
    return ((value == club) || (value == spade));
}

constexpr bool Suit::IsRed() const
{
    //Return true if heart or diamond
    return ((value == heart) || (value == diamond));
}

constexpr int Suit::toInt() const
{
    //Returns integer value of suit
    return static_cast<int>(value);
}

constexpr char Suit::toChar() const
{
    //Returns character value of suit
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
    //Sets suit value from int
    if (val > 3) { return false; }
    value = static_cast<Value>(val); 
}

constexpr bool Suit::fromChar(const char &val)
{
    //Sets suit value from character
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
    //Set value equal to rhs
    value = rhs.value;

    //Return suit
    Suit tmpsuit = Suit(rhs);
    return tmpsuit;
}

Suit &Suit::operator=(const int &rhs)
{
    //Convert integer to suit
    Suit tmpsuit = Suit(rhs);

    //Set suit
    if (fromInt(rhs)) 
        return tmpsuit;
    return;
}

Suit &Suit::operator=(const char &rhs)
{
    //Convert character to suit
    Suit tmpsuit = Suit(rhs);

    //Set suit
    if(fromChar(rhs)) 
        return tmpsuit;
    return;
}

int &Suit::operator*(const int &rhs) const
{
    //Convert current suit to integer
    int tmp = toInt();

    //Multiply for result and return
    tmp = tmp * rhs;
    return tmp;    
}

constexpr bool Suit::operator==(Suit a) const
{
    //Return if values are equal
    return value == a.value;
}

constexpr bool Suit::operator!=(Suit a) const
{
    //Return if values are inequal
    return value != a.value;
}

//Input/Output
ostream &operator<<(ostream &out, const Suit &rhs)
{
    //Output suit as character
    out << rhs.toChar();

    //Return output stream
    return out;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_SUIT


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_CARD
#define PLAYINGCARDSLIB_LIBRARY_CPP_CARD

Card::Card(int value)
{
    //Set rank and suit (rank 0-12, suit 0-3)
    _rank = (value % 52) % 13;
    _suit = (value % 52) / 13;
}

Card::Card(int rank, Suit suit)
{
    //Set rank and suit
    rank = rank % 13;
    _rank = rank;
    _suit = suit;
}

Card::Card(int rank, int suit)
{
    //Set rank and suit
    rank = rank % 13;
    suit = suit % 4;
    _rank = rank;
    _suit = suit;
}

Card::Card(const Card &card)
{
    //Set rank and suit
    _rank = card._rank;
    _suit = card._suit;
}

Card::Card(Card &&card)
{
    //Set rank and suit
    _rank = card._rank;
    _suit = card._suit;
}

Card::Card(const Card *card)
{
    //Set rank and suit
    _rank = card->_rank;
    _suit = card->_suit;
}

void Card::set(int rank, Suit suit)
{
    //Set rank and suit
    rank = rank % 13;
    _rank = rank;
    _suit = suit;
}

void Card::set(int rank, int suit)
{
    //Set rank and suit
    rank = rank % 13;
    suit = suit % 4;
    _rank = rank;
    _suit = suit;
}

int Card::value() const
{
    //Return calculated card value
    return _rank + (_suit * 13);
}

Suit Card::suit() const
{
    //Return card suit
    return _suit;
}

int Card::rank() const
{
    //Return card rank
    return _rank;
}

Card &Card::operator=(const int &rhs)
{
    //Set rank and suit
    _rank = (rhs % 52) % 13;
    _suit = (rhs % 52) / 13;

    //Return card
    Card card = Card(*this);
    return card;
}

Card &Card::operator=(const Card &rhs)
{
    //Set rank and suit
    _rank = rhs._rank;
    _suit = rhs._suit;

    //Return card
    Card card = Card(*this);
    return card;
}

Card &Card::operator=(Card &&rhs)
{
    //Set rank and suit
    _rank = rhs._rank;
    _suit = rhs._suit;

    //Return card
    Card card = Card(*this);
    return card;
}

bool Card::operator==(const Card &rhs)
{
    //If suits are equal
    if (_suit == rhs._suit)
        //If ranks are equal
        if(_rank == rhs._rank)
            //Return true
            return true;
    //else return false
    return false;
}

bool Card::operator!=(const Card& rhs)
{
    //If suits are equal
    if (_suit == rhs._suit)
        //If ranks are equal
        if(_rank == rhs._rank)
            //Return false
            return false;
    //else return true
    return true;
}

ostream &operator<<(ostream &out, const Card &rhs)
{
    //Output card value
    out << setfill(' ') << setw(2) << rhs.value();

    //Ouput suit
    out << rhs.suit();

    //Return output stream
    return out;
}

inline ostream &operator<<(ostream &out, const Deck &rhs)
{
    //Get begining iterator
    Iterator tmpIt = rhs.begin();

    //While not at the end iterator
    while(tmpIt != rhs.end())
    {
        //Output card at iterator
        out << *tmpIt++;
    }

    //Return output stream
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
        //Insert card into deck
        rhs.insert((tempCard = Card(tempInt)), rhs.end());
    }

    //Return input stream
    return in;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_CARD


#ifndef PLAYINGCARDSLIB_LIBRARY_CPP_ITERATOR
#define PLAYINGCARDSLIB_LIBRARY_CPP_ITERATOR

Card &Deck::Iterator::operator*()
{
    //Return card value
    return _node->next->card;
}

Iterator &Deck::Iterator::operator+(int rhs)
{
    //Increment iterator by rhs
    for (int i = 0; i < rhs; ++i)
    {
        _node = _node->next;
    }
}

Iterator &Deck::Iterator::operator-(int rhs)
{
    //Decrement iterator by rhs
    for (int i = 0; i < rhs; ++i)
    {
        _node = _node->prev;
    }
}

Deck::Iterator &Deck::Iterator::operator++()
{
    //Prefix increment iterator
    _node = _node->next;
    return *this;
}

Deck::Iterator &Deck::Iterator::operator++(int)
{
    //Prefix increment iterator
    Iterator tmp = *this;
    _node = _node->next;
    return tmp;
}

Deck::Iterator &Deck::Iterator::operator--()
{
    //Postfix decrement iterator
    _node = _node->prev;
    return *this;
}

Iterator &Deck::Iterator::operator--(int)
{
    //Postfix decrement iterator
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
    //Set head and tail as null
    head = tail = new Node();

    //If fill is true then add cards
    if (fill)
        reset();
}

Deck::Deck(const Deck& old)
{
    //Defining variables
    Node *copyptr = old.head, *newnode;

    //While ptr isn't null
    while (copyptr != nullptr)
    {
        //Copy card from old deck to new
        insert(copyptr->card, end());
        copyptr = copyptr->next;
    }
}

Deck::Deck(Deck&& old)
{
    //Defining variables
    Node *copyptr = old.head, *newnode;

    //While ptr isn't null
    while (copyptr != nullptr)
    {
        //Copy card from old deck to new
        insert(copyptr->card, end());
        copyptr = copyptr->next;
    }
}

Deck::~Deck()
{
    //Defining variables
    Node *tmpptr;

    //While head isn't null
    while (head != nullptr)
    {
        //Set tmpptr to head and increment head
        tmpptr = head;
        head = head->next;
        //Delete tmpptr
        delete tmpptr;
    }

    //Set tail to null
    tail == nullptr;
}

//Manipulations
void Deck::clear()
{
    //Defining variables
    Node *tmpptr;

    //While head isn't null
    while(head != nullptr)
    {
        //Set tmpptr to head and increment head
        tmpptr = head;
        head = head->next;
        //Delete tmpptr
        delete tmpptr;
    }

    //Set tail to null
    tail = nullptr;
}

void Deck::reset()
{
    //Clear the deck of cards
    clear();

    //Fill the deck with cards ascending
    for (int i = 0; i < 52; ++i)
        insert(Card(i), end());
}

Card &Deck::draw(Iterator& pos)
{
    //Defining variables
    Node *ptr = pos._node->next;
    Card card = Card(ptr->card);

    //Ghost node
    pos._node->next = ptr->next;
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    //Delete node and return card
    delete ptr;
    return card;
}

Iterator Deck::remove(Iterator pos)
{
    //Defining variables
    Node *ptr = pos._node->next;

    //Ghost node
    pos._node->next = ptr->next;
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    //Delete node and return iterator
    delete ptr;
    return pos;
}

Iterator Deck::insert(const Card &in, Iterator pos)
{
    //Defining variables
    Node *newNode = new Node(Card(in), pos._node->next, pos._node);

    //If at tail then set tail
    if (pos._node == tail) tail = newNode;

    //Insert node
    pos._node->next->prev = newNode;
    pos._node->next = newNode;

    //Return iterator to node
    return pos;
}

//Information
Deck::Iterator Deck::begin() const
{
    //Return iterator to
    return Iterator(head);
}

Deck::Iterator Deck::end() const
{
    //Return iterator to tail
    return Iterator(tail);
}

size_type Deck::size() const
{
    //Defining variables
    Node *tmpptr = head;
    size_type size = 0;

    //While tmpptr isn't null
    while (tmpptr != nullptr)
    {
        //Increment size and ptr
        ++size;
        tmpptr = tmpptr->next;
    }

    //Return size
    return size;
}

bool Deck::empty() const
{
    //If head is null return true
    if (head == nullptr)
        return true;

    //Else return false
    return false;
}

Card &Deck::peek(Iterator pos) const
{
    //Return card at iterator
    return *pos;
}

Iterator Deck::seek(const Card &card, Iterator start) const
{
    //If start is set keep it else set with begin
    start = (start == nullptr) ? begin() : start;
    Iterator tmpIt = start;

    //While not at the tail
    while (tmpIt._node->next != tail)
    {
        //If search is found
        if (tmpIt._node->next->card == card)
        {
            //Return iterator to card
            return tmpIt;
        }
    }

    //Else return null iterator
    return Iterator(nullptr);
}

//Overloads
Deck& Deck::operator=(const Deck& rhs)
{
    //Defining variables
    Node *tmpptr = rhs.head;

    //Clear lhs deck
    clear();

    //While not at end of rhs
    while(tmpptr != nullptr)
    {
        //Insert card into lhs
        insert(tmpptr->card, end());
        tmpptr = tmpptr->next;
    }

    //Return lhs
    return *this;
}

Deck &Deck::operator=(Deck &&rhs)
{
    //Defining variables
    Node *tmpptr = rhs.head;

    //Clear lhs deck
    clear();

    //While not at end of rhs
    while(tmpptr != nullptr)
    {
        //Insert card into lhs
        insert(tmpptr->card, end());
        tmpptr = tmpptr->next;
    }

    //Return lhs
    return *this;
}

bool Deck::operator==(const Deck& rhs)
{
    //Defining variables
    size_type deckSize = size();
    Node *lhsptr = head;
    Node *rhsptr = rhs.head;

    //If both are empty return true
    if (empty())
    {
        if (rhs.empty())
            return true;
        return false;
    }
    //Else if one is empty return false
    if (rhs.empty())
        return false;

    //If sizes are different return false
    if (deckSize != rhs.size())
        return false;

    //While neither side is at the end
    while(lhsptr != nullptr && rhsptr != nullptr)
    {
        //If cards are not equal return false
        if (lhsptr->card != rhsptr->card)
        {
            return false;
        }
        
        //Else increment and repeat
        lhsptr = lhsptr->next;
        rhsptr = rhsptr->next;
    }

    //Return true
    return true;
}

#endif //PLAYINGCARDSLIB_LIBRARY_CPP_DECK