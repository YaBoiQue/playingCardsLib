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

enum class suits{ club, diamond, heart, spade }; //Lowest to Highest Value

inline suits fromInt(const int val){
    return static_cast<suits>(val);
}

inline suits fromChar(const char val){
    if (val == toupper('C'))
        return suits::club;
    if (val == toupper('D'))
        return suits::diamond;
    if (val == toupper('H'))
        return suits::heart;
    if (val == toupper('S'))
        return suits::spade;
    return suits();
}

inline ostream& operator<<(ostream& out, const suits& rhs){
    if (rhs == suits::club)
        out << "C";
    else if (rhs == suits::diamond)
        out << "D";
    else if (rhs == suits::heart)
        out << "H";
    else if (rhs == suits::spade)
        out << "S";
}

struct card{
    int data;

    explicit card(int value=0) {
        data = (value % 52);
    }

    [[nodiscard]] int value() const{
        return (data % 52) % 13;
    };
    [[nodiscard]] suits suit() const{
        return static_cast<suits>((data % 52) / 13);
    };


    //Overloads
    inline card& operator=(const int& rhs){
        data = rhs;
    }

    inline card& operator=(const card& rhs){
        data = rhs.data;
    }

    //Input/Output
    inline friend ostream& operator<<(ostream& out, const card& rhs) {
        //Output card value
        out << setfill(' ') << setw(2) << rhs.value();

        //Ouput suit
        out << rhs.suit();

        return out;
    }
    inline friend istream& operator>>(istream& in, card& rhs) {
        //Defining variables
        int tempInt;

        //Read in values
        in >> rhs.data;

        return in;
    }


    bool operator==(const card rhs);
    bool operator!=(const card rhs);
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
