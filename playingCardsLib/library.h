#ifndef PLAYINGCARDSLIB_LIBRARY_H
#define PLAYINGCARDSLIB_LIBRARY_H

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

typedef  unsigned long size_type;

enum suit{
    club,
    diamond,
    heart,
    spade
};

struct card{
    int data;

    explicit card(int value=0) {
        data = value;
    }

    [[nodiscard]] int value() const{
        return data % 13;
    };
    [[nodiscard]] int suit() const{
        return data / 13;
    };

    const bool operator==(const card rhs);
    const bool operator!=(const card rhs);
};

class deck : public vector<card>{

public:
    //De/Constructors
    deck(){
        for(int i = 0; i < 52; ++i)
            .emplace_back(i);
    };
    deck(deck& old){
        this = old;
    }
    explicit deck(vector<card>& old){
        this = old;
    }
    ~deck() = default;

    //Manipulations
    void reset();                                   //Clears deck and fills with default values
    void shuffle(unsigned int seed = 0);            //Shuffles cards in deck
    deck cut(size_type spot = 0);                   //Cuts deck (shuffles without changing order)
    card draw(int pos = 0, bool reverse = false);   //Draws card from dec (removes and outputs card)
    bool remove(int pos = 0, bool reverse = false); //Removes card from deck (removes card)
    bool insert(card in, int pos = 0, bool reverse = false, bool duplicates = false);    //Inserts card into deck

    //Data
    card peek(int pos = 0, bool reverse = false);
    size_type seek (card search, size_type start = 0, bool reverse = false);

    //Conversion

    //Overloads
    const bool operator==(const deck rhs);
    friend ostream& operator<<(ostream& out, const deck& rhs);
    friend ifstream& operator>>(ifstream& in, deck& rhs);

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
    CARD::_card tempCard;

    //While cards can still be read from the file
    while (in >> tempInt)
    {
        rhs.place(tempCard.fromInt(tempInt), 0, true);
    }

    return in;
}

#endif //PLAYINGCARDSLIB_LIBRARY_H
