//
// Created by Kristian Snyder on 2/6/17.
//

#ifndef LAB04_FISH_H
#define LAB04_FISH_H
#include "Animal.h"


class Fish : public Animal {
private:
    int fins;
public:
    Fish();
    Fish(int fins);
    Fish(int fins, int legNum, int eyeNum);

    void setFins(int f) {
        // can't have negative fins
        if (f < 0) {
            fins = 0;
        } else {
            fins = f;
        }
    }
    int getFins() {
        return fins;
    }

    // each function call to instances of Fish
    // will call the implementation
    // defined in Fish.cpp
    // Only difference is that instances pointed to by
    // Animal pointers will call Animal's move(),
    // as move() is virtual.
    void move();
    void eat();
};


#endif //LAB04_FISH_H
