#include <iostream>
#include "Fish.h"
#include "Horse.h"
using namespace std;


void callMoveEat(Animal *animal) {
    animal->move();
    animal->eat();
}

int main() {
    bool repeat = true;

    while (repeat) {
        // initialize choice to an invalid selection
        int choice = -1;
        // ranges of choices are 1-5, so choice has to be within that.
        while (choice < 1 || choice > 5) {
            cout << "Select a class to create:" << endl
                 << "1: Animal" << endl
                 << "2: Fish" << endl
                 << "3: Horse" << endl
                 << "4: Fish as an Animal" << endl
                 << "5: Horse as an Animal" << endl;
            cin >> choice;
        }

        // Based on the input, instantiate one of the following:
        // (and then call callMoveEat() with the pointer to the instance)
        switch (choice) {
            case 1: {
                // An animal
                Animal* animal = new Animal;
                callMoveEat(animal);
                break;
            }
            case 2: {
                // A fish
                Fish *fish = new Fish;
                callMoveEat(fish);
                break;
            }
            case 3: {
                // A horse
                Horse *horse = new Horse;
                callMoveEat(horse);
                break;
            }
            case 4: {
                // A Fish acting as an Animal
                Animal *fishAnimal = new Fish;
                callMoveEat(fishAnimal);
                break;
            }
            case 5: {
                // A Horse acting as an Animal
                Animal *horseAnimal = new Horse;
                callMoveEat(horseAnimal);
                break;
            }
        }

        string repeatStr;

        cout << "Want to continue? (Y/N) ";
        cin >> repeatStr;

        // Matching on many ways to say no
        if (repeatStr == "N" || repeatStr == "n" ||
            repeatStr == "no" || repeatStr == "NO" ||
            repeatStr == "No") {
            repeat = false;
        }
    }
}