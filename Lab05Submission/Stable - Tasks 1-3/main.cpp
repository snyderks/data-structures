#include "Stable.h"
#include "Horse.h"
#include <iostream>
using namespace std;

int main() {
    Stable<Horse> stable;

    // infinite run loop, break out when done
    while (true) {
        cout << "Press 1 to add a horse to the stable." << endl
             << "Press 2 remove a horse from the stable." << endl
             << "Press 3 see how many horses are currently in the stable." << endl
             << "Press 4 to quit." << endl;
        int resp = 0;
        // infinite user input loop, break out when response is valid
        while (true) {
            cin >> resp;
            if (resp >= 1 && resp <= 5) {
                break;
            } else {
                cout << "Please enter a number between 1 and 4: ";
            }
        }
        bool quit = false;

        // used in case for removing an animal
        Horse *animal;

        // used in case for adding an animal
        string breed;

        switch (resp) {
            case 1:
                cout << "What kind of horse? ";
                cin >> breed;
                try {
                    stable.addAnimal(new Horse(breed));
                } catch (FullStable ex) {
                    cout << "Stable is full. Couldn't add the horse." << endl;
                }
                break;
            case 2:
                try {
                    animal = stable.removeAnimal();
                    cout << "You removed a " << animal->getBreed() << endl;
                } catch (EmptyStable ex) {
                    cout << "Stable is empty. Couldn't get a horse." << endl;
                }
                break;
            case 3:
                cout << stable.getAnimalsCaredFor() << endl;
                break;
            case 4:
                quit = true;
                break;
        }

        if (quit) {
            break;
        } else {
            cout << endl;
        }

    }


    return 0;
}