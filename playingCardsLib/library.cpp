#include "library.h"

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
};

class deck{
    vector<card> cards; //Front = bottom, Back = top

public:
    //De/Constructors
    deck(){
        for(int i = 0; i < 52; ++i)
            cards.emplace_back(i);
    };
    deck(deck& old){
        cards = old.cards;
    }
    explicit deck(vector<card>& old){
        cards = old;
    }
    ~deck() = default;

    //Manipulations
    void shuffle(){
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine rng(seed);

        std::shuffle(cards.begin(), cards.end(), rng);
    }
    deck cut(size_type spot = 0){
        spot = (spot == 0) ? cards.size()/2:spot;
        vector<card> tmp;

        for (size_type i = 0; i < spot; ++i){
            tmp.emplace(tmp.front(), cards.)
        }

    }
    card dtop(){
        card tmp = cards.at(cards.size());
        cards.pop_back();
        return tmp;
    }
    card dbottom(){
        card tmp = cards.at(0);
        cards.erase(cards.begin());
        return tmp;
    }
    card dmid(int pos){
        card tmp = cards.at(pos);
        cards.erase(cards.begin() + pos);
        return tmp;
    }
    bool ptop(card insert){
        cards.emplace_back(insert);
        return true;
    }
    bool pbottom(card insert){
        cards.emplace(cards.begin(), insert);
        return true;
    }
    bool pmid(card insert, int pos){
        cards.emplace(cards.begin()+pos, insert);
        return true;
    }

    //Data
    size_type size(){
        return cards.size();
    }
    card top(){
        return cards.at(cards.size());
    }
    card bottom(){
        return cards.at(0);
    }
    card mid(int pos){
        return cards.at(pos);
    }



private:
};
