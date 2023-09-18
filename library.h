#ifndef PLAYINGCARDSLIB_LIBRARY_H
#define PLAYINGCARDSLIB_LIBRARY_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>
#include <fstream>

using namespace std;

typedef  unsigned long size_type;


#ifndef PLAYINGCARDSLIB_LIBRARY_H_SUIT
#define PLAYINGCARDSLIB_LIBRARY_H_SUIT

class Suit
{
public:
    enum Value : uint8_t
    {
        club,
        diamond,
        heart,
        spade
    };

    //De/Constructors
    Suit() = default;
    constexpr Suit(const Value& aSuit) : value(aSuit){};
    constexpr Suit(const int& val) : value(static_cast<Value>(val)){};
    constexpr Suit(const char& val) : value(Suit::club) {fromChar(val);};

    //Information
    constexpr bool IsBlack() const;
    constexpr bool IsRed() const;
    constexpr int  toInt()  const;
    constexpr char toChar() const; 

    //Manipulation
    constexpr bool fromInt(const int& val);
    constexpr bool fromChar(const char& val);

    //Operator overloads
    Suit& operator=(const Suit& rhs);
    Suit& operator=(const int& rhs);
    Suit& operator=(const char& rhs);
    int&  operator*(const int& rhs) const;

    //input/output
    friend ostream& operator<<(ostream& out, const Suit& rhs);

#if Enable switch(suit) use case:
    // Allow switch and comparisons.
    constexpr operator Value() const { return value; }

    // Prevent usage: if(suit)
    explicit operator bool() const = delete;        
#else
    constexpr bool operator==(Suit a) const;
    constexpr bool operator!=(Suit a) const;
#endif

private:
    Value value;
};

#endif //PLAYINGCARDSLIB_LIBRARY_H_SUIT



#ifndef PLAYINGCARDSLIB_LIBRARY_H_CARD
#define PLAYINGCARDSLIB_LIBRARY_H_CARD

class Card {
    int _rank;   //0=ace, 1=two, 2=three, 3=four, 4=five, 5=six, 6=seven, 7=eight, 8=nine, 9=ten, 10=jack, 11=queen, 12=king
    Suit _suit;  //0=club, 2=diamond, 3=heart, 4=spade

public:
    //De/Constructors
    explicit Card(int value=0) : _rank(value % 13), _suit(value / 13) {}
    explicit Card(int rank, Suit suit ) : _rank(rank), _suit(suit) {}
    explicit Card(int rank, int suit) : _rank(rank), _suit(suit) {}
    explicit Card(Card &&card) : _rank(card._rank), _suit(card._suit) {}
    explicit Card(const Card& card) : _rank(card._rank), _suit(card._suit) {}
    explicit Card(const Card *card) : _rank(card->_rank), _suit(card->_suit) {}

    //Manipulation
    void set(int rank, Suit suit);
    void set(int rank, int suit);

    //Information
    constexpr int value() const;
    constexpr Suit suit() const;
    constexpr int rank() const;


    //Overloads
    Card& operator=(const int& rhs);
    Card& operator=(const Card& rhs);
    Card& operator=(Card&& rhs);
    bool operator==(const Card& rhs);
    bool operator!=(const Card& rhs);

    //Input/Output
    friend ostream& operator<<(ostream& out, const Card& rhs);
};
#endif //PLAYINGCARDSLIB_LIBRARY_H_CARD



#ifndef PLAYINGCARDSLIB_LIBRARY_H_NODE
#define PLAYINGCARDSLIB_LIBRARY_H_NODE

class Node
{
public:
    Card card;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node() : next(nullptr), prev(nullptr) {};
    Node(const Card item, Node *nptr = nullptr, Node *pptr = nullptr) :
        card(item), next(nptr), prev(pptr) {}
};

#endif //PLAYINGCARDSLIB_LIBRARY_H_NODE



#ifndef PLAYINGCARDSLIB_LIBRARY_H_DECK
#define PLAYINGCARDSLIB_LIBRARY_H_DECK
class Deck {
    Node *head, *tail;

public:

    #ifndef PLAYINGCARDSLIB_LIBRARY_H_DECK_ITERATOR
    #define PLAYINGCARDSLIB_LIBRARY_H_DECK_ITERATOR

    class Iterator {
        friend class Deck;
        Node *_node;
        //De/Constructors
        Iterator(Node *node=nullptr): _node(node){}
    public:
        Iterator() : _node(nullptr) {}

        //Operator Overloads
        Card& operator*();
        Iterator& operator+(int rhs);
        Iterator& operator-(int rhs);
        Iterator& operator++();
        Iterator& operator++(int);
        Iterator& operator--();
        Iterator& operator--(int);

        inline friend bool operator==(const Iterator& lhs, const Iterator& rhs)
        {
            if (rhs._node->card == lhs._node->card)
            {
                return true;
            }
            return false;
        }
        inline friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
        {
            if (rhs._node->card == lhs._node->card)
            {
                return false;
            }
            return true;
        }
    };

    #endif //PLAYINGCARDSLIB_LIBRARY_H_DECK_ITERATOR

    //De/Constructors
    Deck() {head = tail = new Node();};
    explicit Deck(bool fill);
    Deck(const Deck& other) = delete;
    Deck(Deck&& other) = delete;
    ~Deck();

    //Manipulations
    void clear();
    void reset();                                       //Clears deck and fills with default values
    void shuffle(unsigned seed);                    //Shuffles cards in deck
    Iterator cut(Iterator pos = Iterator(nullptr));
    Card& draw(Iterator &pos);
    Iterator remove(Iterator pos);
    Iterator insert(const Card& in, Iterator pos);

    //Information
    constexpr Iterator begin()const;
    constexpr Iterator end()const;
    constexpr size_type size()const;
    constexpr bool empty()const;
    Card& peek(Iterator pos = Iterator(nullptr))const;
    Iterator seek(const Card& search, Iterator start = Iterator(nullptr))const;

    //Overloads
    Deck& operator=(const Deck& rhs);               //Sets deck equal to right hand rhs
    Deck& operator=(Deck&& rhs);
    bool operator==(const Deck& rhs);              //Checks if deck is equal to rhs
    inline friend ostream& operator<<(ostream& out, const Deck& rhs);    //Export deck to ostream
    friend ifstream& operator>>(ifstream& in, Deck& rhs);                //Import deck from istream

};

#endif //PLAYINGCARDSLIB_LIBRARY_H_DECK

#endif //PLAYINGCARDSLIB_LIBRARY_H
