//
// Created by Kristian Snyder on 2/6/17.
//

#include "Fish.h"
#include <iostream>
using namespace std;

Fish::Fish() : Animal() {
    // don't assume there are fins.
    fins = 0;
}
Fish::Fish(int fins) : Animal() {
    // setting attributes this way due to value checks
    // present in the setters.
    setFins(fins);
}
Fish::Fish(int fins, int legNum, int eyeNum) : Animal(legNum, eyeNum) {
    // setting attributes this way due to value checks
    // present in the setters.
    setFins(fins);
}

void Fish::move() {
    cout << "Just keep swimming." << endl;
}

void Fish::eat() {
    cout << "Yummy Fish Food." << endl;
}