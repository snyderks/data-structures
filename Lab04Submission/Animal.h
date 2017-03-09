//
// Created by Kristian Snyder on 2/6/17.
//

#ifndef LAB04_ANIMAL_H
#define LAB04_ANIMAL_H
#include <string>
using namespace std;

class Animal {
private:
    // available through getters and setters only.
    int legs;
    int eyes;
public:
    Animal();
    Animal(int legNum, int eyeNum);

    // all getters and setters are freely available.
    // they should not be overridden.
    int getLegs() const {
        return legs;
    }

    void setLegs(int l) {
        // can't have negative legs
        if (l < 0) {
            legs = 0;
        } else {
            legs = l;
        }
    }

    int getEyes() const {
        return eyes;
    }

    void setEyes(int e) {
        // can't have negative eyes
        if (e < 0) {
            eyes = 0;
        }
        else {
            eyes = e;
        }
    }

    // publicly available to derived classes
    // will be overridden
    virtual void move();

    // available if not overridden
    void eat();
};


#endif //LAB04_ANIMAL_H
