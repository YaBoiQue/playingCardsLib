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

#if Enable switch(suit) use case:
    // Allow switch and comparisons.
    constexpr operator Value() const { return value; }

    // Prevent usage: if(suit)
    explicit operator bool() const = delete;        
#else
    constexpr bool operator==(Suit a) const;
    constexpr bool operator!=(Suit a) const;
#endif

    constexpr bool IsBlack() const;
    constexpr bool IsRed() const;

    constexpr bool fromInt(const int& val);
    constexpr bool fromChar(const char& val);
    constexpr int  toInt()  const;
    constexpr char toChar() const; 

    friend ostream& operator<<(ostream& out, const Suit& rhs);
    Suit& operator=(const Suit& rhs);
    Suit& operator=(const int& rhs);
    Suit& operator=(const char& rhs);
    int& operator*(const int& rhs) const;

private:
    Value value;
};


class Card {
    int _rank;   //0=ace, 1=two, 2=three, 3=four, 4=five, 5=six, 6=seven, 7=eight, 8=nine, 9=ten, 10=jack, 11=queen, 12=king
    Suit _suit;  //0=club, 2=diamond, 3=heart, 4=spade

public:
    explicit Card(int value=0) {
        _rank = (value % 52) % 13;
        _suit = (value % 52) / 13;
    }
    explicit Card(int rank, Suit suit ){
        rank = rank % 13;
        _rank = rank;
        _suit = suit;
    }
    explicit Card(int rank, int suit){
        rank = rank % 13;
        suit = suit % 4;
        _rank = rank;
        _suit = suit;
    }
    explicit Card(const Card& card){
        
    }

    [[nodiscard]] int value() const{
        return _rank + (_suit * 13);
    };
    [[nodiscard]] Suit suit() const{
        return _suit;
    };
    [[nodiscard]] int rank() const{
        return _rank;
    }


    //Overloads
    inline Card& operator=(const int& rhs){
        _rank = (rhs % 52) % 13;
        _suit = (rhs % 52) / 13;
    }
    inline Card& operator=(const Card& rhs){
        _rank = rhs._rank;
        _suit = rhs._suit;
    }
    bool operator==(const Card rhs);
    bool operator!=(const Card rhs);

    //Input/Output
    inline friend ostream& operator<<(ostream& out, const Card& rhs) {
        //Output card value
        out << setfill(' ') << setw(2) << rhs.value();

        //Ouput suit
        out << rhs.suit();

        return out;
    }
};


class deck {

public:
    //De/Constructors
    explicit deck(bool fill = true);
    deck(deck& old);
    ~deck();

    //Manipulations
    void reset();                                       //Clears deck and fills with default values
    void shuffle(unsigned seed = 0);                    //Shuffles cards in deck
    bool cut(size_type spot = 0);                       //Cuts deck (shuffles without changing order)
    card draw(int pos = 0, bool reverse = false);       //Draws card from dec (removes and outputs card)
    bool remove(int pos = 0, bool reverse = false);     //Removes card from deck (removes card)
    bool insert(card in, int pos = 0, bool reverse = false, bool duplicates = false);    //Inserts card into deck

    //Data
    card peek(int pos = 0, bool reverse = false);       //View card at pos in deck
    int seek (card search, int start = 0, bool reverse = false);    //Search for card in deck. Returns card 52 if not found.

    //Conversion

    //Overloads
    deck& operator=(const deck& rhs);               //Sets deck equal to right hand rhs
    bool operator==(const deck& rhs);              //Checks if deck is equal to rhs
    friend ostream& operator<<(ostream& out, const deck& rhs);  //Export deck to ostream
    friend ifstream& operator>>(ifstream& in, deck& rhs);       //Import deck from istream

private:
};

inline ostream& operator<<(ostream& out, const deck& rhs)
{
    int size = rhs.size();

    for (int i = 0; i < size; ++i)
    {
        out << rhs.at(i) << " ";

        if ((i % 13) == 12)
            out << endl;
    }

    return out;
}

inline ifstream& operator>>(ifstream& in, deck& rhs)
{
    //Defining variables
    int tempInt;
    card tempCard;

    //While cards can still be read from the file
    while (in >> tempInt)
    {
        rhs.insert((tempCard = card(tempInt)), 0, true);
    }

    return in;
}

#endif //PLAYINGCARDSLIB_LIBRARY_H
