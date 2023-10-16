#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "deck_lib.h"
#include <iostream>

using namespace std;

/*****************SUIT******************/
//Constructors
TEST_CASE("constructor (uninitialized)")
{
    Suit suit{};

    REQUIRE(suit == Suit());
}

TEST_CASE("constructor (initialized)")
{
    Suit suit = Suit(Suit::club);
    REQUIRE(suit.value() == Suit::club);

    suit = Suit(Suit::diamond);
    REQUIRE(suit.value() == Suit::diamond);

    suit = Suit(Suit::heart);
    REQUIRE(suit.value() == Suit::heart);

    suit = Suit(Suit::spade);
    REQUIRE(suit.value() == Suit::spade);
}

TEST_CASE("constructor (from int)")
{
    Suit suit = Suit(0);
    REQUIRE(suit.value() == Suit::club);

    suit = Suit(1);
    REQUIRE(suit.value() == Suit::diamond);

    suit = Suit(2);
    REQUIRE(suit.value() == Suit::heart);

    suit = Suit(3);
    REQUIRE(suit.value() == Suit::spade);

    suit = Suit(4);
    REQUIRE(suit.value() == Suit::club);
}

TEST_CASE("constructor (from char)")
{
    Suit suit = Suit('c');
    REQUIRE(suit.value() == Suit::club);

    suit = Suit('d');
    REQUIRE(suit.value() == Suit::diamond);

    suit = Suit('h');
    REQUIRE(suit.value() == Suit::heart);

    suit = Suit('s');
    REQUIRE(suit.value() == Suit::spade);

    suit = Suit('t');
    REQUIRE(suit == Suit());
}

//Information
TEST_CASE("color detection")
{
    Suit suit = Suit('c');
    REQUIRE(suit.isBlack());
    REQUIRE(!suit.isRed());

    suit = Suit('d');
    REQUIRE(!suit.isBlack());
    REQUIRE(suit.isRed());

    suit = Suit('s');
    REQUIRE(suit.isBlack());
    REQUIRE(!suit.isRed());

    suit = Suit('h');
    REQUIRE(!suit.isBlack());
    REQUIRE(suit.isRed());
}

TEST_CASE("conversions from suit")
{
    Suit suit = Suit('c');
    REQUIRE(suit.toInt() == 0);
    REQUIRE(suit.toChar() == 'C');
    REQUIRE(suit.value() == Suit::club);

    suit = Suit('d');
    REQUIRE(suit.toInt() == 1);
    REQUIRE(suit.toChar() == 'D');
    REQUIRE(suit.value() == Suit::diamond);

    suit = Suit('s');
    REQUIRE(suit.toInt() == 3);
    REQUIRE(suit.toChar() == 'S');
    REQUIRE(suit.value() == Suit::spade);

    suit = Suit('h');
    REQUIRE(suit.toInt() == 2);
    REQUIRE(suit.toChar() == 'H');
    REQUIRE(suit.value() == Suit::heart);
}

//Manipulations
TEST_CASE("conversion to suit")
{
    Suit suit = Suit();

    suit.fromInt(0);
    REQUIRE(suit.value() == Suit::club);

    suit.fromChar('c');
    REQUIRE(suit.value() == Suit::club);

    suit.fromInt(1);
    REQUIRE(suit.value() == Suit::diamond);

    suit.fromChar('d');
    REQUIRE(suit.value() == Suit::diamond);

    suit.fromInt(2);
    REQUIRE(suit.value() == Suit::heart);

    suit.fromChar('h');
    REQUIRE(suit.value() == Suit::heart);

    suit.fromInt(3);
    REQUIRE(suit.value() == Suit::spade);

    suit.fromChar('s');
    REQUIRE(suit.value() == Suit::spade);
}

//Operator Overloads
TEST_CASE("operator= suit")
{
    Suit suit1 = Suit('d'), suit2 = Suit('s');

    suit1 = suit2;

    REQUIRE(suit1 == suit2);
    REQUIRE(suit1.value() == Suit::spade);
}

TEST_CASE("operator= int")
{
    Suit suit1 = Suit('d');
    int suit2 = 3;

    suit1 = suit2;

    REQUIRE(suit1.toInt() == suit2);
    REQUIRE(suit1.value() == Suit::spade);
}

TEST_CASE("operator= char")
{
    Suit suit1 = Suit('d');
    char suit2 = 's';

    suit1 = suit2;

    REQUIRE(suit1.toChar() == suit2);
    REQUIRE(suit1.value() == Suit::spade);
}

TEST_CASE("operator* int")
{
    Suit suit = Suit('d');
    int val = 11;

    val = suit * val;

    REQUIRE(val == 22);
}

TEST_CASE("inequalities")
{
    Suit suit1 = Suit('d'), suit2 = Suit('s');

    REQUIRE(suit1 != suit2);
    REQUIRE(!(suit1 == suit2));
}


/*****************CARD******************/






/*****************NODE******************/





/***************ITERATOR****************/





/*****************DECK******************/