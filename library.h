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
    explicit Card(int value=0);
    explicit Card(int rank, Suit suit );
    explicit Card(int rank, int suit);
    explicit Card(const Card& card);
    explicit Card(const Card *card);

    //Manipulation
    void set(int rank, Suit suit);
    void set(int rank, int suit);

    //Information
    [[nodiscard]] int value() const;
    [[nodiscard]] Suit suit() const;
    [[nodiscard]] int rank() const;


    //Overloads
    Card& operator=(const int& rhs);
    Card& operator=(const Card& rhs);
    bool operator==(const Card& rhs);
    bool operator!=(const Card& rhs);

    //Input/Output
    friend ostream& operator<<(ostream& out, const Card& rhs);
};
#endif //PLAYINGCARDSLIB_LIBRARY_H_CARD



#ifndef PLAYINGCARDSLIB_LIBRARY_H_NODE
#define PLAYINGCARDSLIB_LIBRARY_H_NODE

struct Node
{
    Card card;
    Node* next = nullptr;
    Node* prev = nullptr;

};

#endif //PLAYINGCARDSLIB_LIBRARY_H_NODE



#ifndef PLAYINGCARDSLIB_LIBRARY_H_ITERATOR
#define PLAYINGCARDSLIB_LIBRARY_H_ITERATOR

class Iterator {
    friend class Deck;
    Node *_node;
public:
    //De/Constructors
    Iterator(Node *node=nullptr): _node(node){}

    //Operator Overloads
    Card& operator*() {return _node->card;}
    Iterator& operator++()
    {
        _node = _node->next;
        return *this;
    }
    Iterator& operator--()
    {
        _node = _node->prev;
        return *this;
    }
    friend bool operator==(const Iterator& lhs, const Iterator& rhs)
    {
        return lhs._node == rhs._node;
    }
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
    {
        return lhs._node != rhs._node;
    }
};

#endif //PLAYINGCARDSLIB_LIBRARY_H_ITERATOR



#ifndef PLAYINGCARDSLIB_LIBRARY_H_DECK
#define PLAYINGCARDSLIB_LIBRARY_H_DECK
class Deck {
public:

    //De/Constructors
    explicit Deck(bool fill = true);
    Deck(Deck& old);
    ~Deck();

    //Manipulations
    void clear();
    void reset();                                       //Clears deck and fills with default values
    void shuffle(unsigned seed);                    //Shuffles cards in deck
    bool cut(size_type spot = 0);                       //Cuts deck (shuffles without changing order)
    Card& draw(int pos = 0, bool reverse = false);       //Draws card from dec (removes and outputs card)
    bool remove(int pos = 0, bool reverse = false);     //Removes card from deck (removes card)
    bool insert(const Card& in, int pos, bool reverse = false, bool duplicates = false);    //Inserts card into deck
    bool insert(const Card& in, bool back = true);

    //Information
    Card& peek(int pos = 0, bool reverse = false)const;       //View card at pos in deck
    int seek(const Card& search, int start = 0, bool reverse = false)const;    //Search for card in deck. Returns card 52 if not found.
    [[nodiscard]]size_type size()const;
    [[nodiscard]]bool empty()const;

    //Overloads
    Deck& operator=(const Deck& rhs);               //Sets deck equal to right hand rhs
    bool operator==(const Deck& rhs);              //Checks if deck is equal to rhs
    inline friend ostream& operator<<(ostream& out, const Deck& rhs);    //Export deck to ostream
    friend ifstream& operator>>(ifstream& in, Deck& rhs);                //Import deck from istream

private:
    Iterator head, tail;
};

#endif //PLAYINGCARDSLIB_LIBRARY_H_DECK

#endif //PLAYINGCARDSLIB_LIBRARY_H
