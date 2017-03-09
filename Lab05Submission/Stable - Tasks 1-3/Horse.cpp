//
// Created by Kristian Snyder on 2/6/17.
//

#include "Horse.h"
#include <iostream>
using namespace std;

Horse::Horse() : Animal() {
    // Shouldn't set a real breed name if one isn't passed.
    breed = "Unknown";
}
Horse::Horse(string breedName) : Animal() {
    breed = breedName;
}
Horse::Horse(string breedName, int legNum, int eyeNum) : Animal(legNum, eyeNum) {
    breed = breedName;
}

void Horse::move() {
    cout << "Walk, Trot, Canter, Gallop." << endl;
}
void Horse::eat() {
    cout << "Yummy grass." << endl;
}
