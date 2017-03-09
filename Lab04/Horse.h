//
// Created by Kristian Snyder on 2/6/17.
//

#ifndef LAB04_HORSE_H
#define LAB04_HORSE_H
#include "Animal.h"

class Horse : public Animal {
private:
    string breed;
public:
    Horse();
    Horse(string breedName);
    Horse(string breedName, int legNum, int eyeNum);

    void setBreed(string b) {
        breed = b;
    }
    string getBreed() {
        return breed;
    }
    // each function call to instances of Horse
    // will call the implementation
    // defined in Horse.cpp
    // Only difference is that instances pointed to by
    // Animal pointers will call Animal's move(),
    // as move() is virtual.
    void move();
    void eat();
};


#endif //LAB04_HORSE_H
