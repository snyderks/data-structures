//
// Created by Kristian Snyder on 2/6/17.
//

#include "Animal.h"
#include <iostream>
using namespace std;

Animal::Animal() {
    // Most animals instantiated will probably have
    // 4 legs and 2 eyes.
    legs = 4;
    eyes = 2;
}

Animal::Animal(int legNum, int eyeNum) {
    // setting attributes this way due to value checks
    // present in the setters.
    setLegs(legNum);
    setEyes(eyeNum);
}

void Animal::move() {
    // makes the move function a little more descriptive
    // about the class.
    cout << "Moves with " << legs << " legs and "
                          << eyes << " eyes." << endl;
}

void Animal::eat() {
    cout << "Yummy!" << endl;
}
