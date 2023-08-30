#include "framework.h"



int main() {
    char choice = 'a';


    do
    {
        //Output header
        cout << char(201) << setw(17) << setfill(char(205)) << char(187) << endl;
        cout << left << char(186) << "   Welcome!!!   " << char(186) << endl;
        cout << char(186) << " To the Library " << char(186) << endl;
        cout << char(186) << " of Card Games! " << char(186) << endl;
        cout << right << char(200) << setw(17) << char(188) << endl << endl;

        //Output games
        cout << "Games: (enter game number)\n"
            << " 1: Game of War\n"
            << " 2: Solitaire\n"
            << " 3: \n"
            << "\n"
            << " 0: Quit\n\nChoice:" << endl;

        cin >> choice;

        cout << "\n\n\n\n\n\n\n\n\n" << endl;


        if (choice == '1')
        {
            startWar();
        }
        if (choice == '2')
        {
            startSolitaire();
        }

        else if (choice == '0')
        {
            cout << "Goodbye" << endl;
        }
        else
        {
            cout << "INVALID CHOICE\n\n" << endl;
        }
    } while (choice != '0');

    return 0;
}