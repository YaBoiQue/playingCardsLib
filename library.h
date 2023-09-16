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



#ifndef PLAYINGCARDSLIB_LIBRARY_H_DECK
#define PLAYINGCARDSLIB_LIBRARY_H_DECK
class deck {
    struct node
    {
        Card card;
        node* next = nullptr;
        node* prev = nullptr;
    };
    node *headptr, *tailptr;

public:
    //De/Constructors
    explicit deck(bool fill = true);
    deck(deck& old);
    ~deck();

    //Manipulations
    void clear();
    void reset();                                       //Clears deck and fills with default values
    void shuffle(unsigned seed = 0);                    //Shuffles cards in deck
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


    //Conversion

    //Overloads
    deck& operator=(const deck& rhs);               //Sets deck equal to right hand rhs
    bool operator==(const deck& rhs);              //Checks if deck is equal to rhs
    inline friend ostream& operator<<(ostream& out, const deck& rhs)    //Export deck to ostream
    {
        size_type size = rhs.size();

        for (size_type i = 0; i < size; ++i)
        {
            out << rhs.peek(i);
        }

        return out;
    }
    friend ifstream& operator>>(ifstream& in, deck& rhs)                //Import deck from istream
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
};

#endif //PLAYINGCARDSLIB_LIBRARY_H_DECK

#endif //PLAYINGCARDSLIB_LIBRARY_H
