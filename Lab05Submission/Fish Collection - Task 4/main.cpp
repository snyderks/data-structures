#include "AnimalCollection.h"
#include "Fish.h"
#include <iostream>
using namespace std;

int main() {
    AnimalCollection<Fish> collection;

    // infinite run loop, break out when done
    while (true) {
        cout << "Press 1 to add a fish to the collection." << endl
             << "Press 2 remove a fish from the collection." << endl
             << "Press 3 see how many fish are currently in the collection." << endl
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
        Fish *animal;

        // used in case for adding an animal
        int fins;

        switch (resp) {
            // switch between the options above
            case 1:
                cout << "How many fins? ";
                cin >> fins;
                try {
                    collection.addAnimal(new Fish(fins));
                } catch (FullCollection ex) {
                    cout << "AnimalCollection is full. Couldn't add the fish." << endl;
                }
                break;
            case 2:
                try {
                    animal = collection.removeAnimal();
                    cout << "You removed a fish with " << animal->getFins() << " fins." << endl;
                    delete animal;
                } catch (EmptyCollection ex) {
                    cout << "AnimalCollection is empty. Couldn't get a fish." << endl;
                }
                break;
            case 3:
                cout << collection.getAnimalsCaredFor() << endl;
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