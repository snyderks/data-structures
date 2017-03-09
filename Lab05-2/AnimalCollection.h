//
// Created by Kristian Snyder on 2/16/17.
//

#ifndef LAB05_STABLE_H
#define LAB05_STABLE_H

#include <cstdlib>
using namespace std;

// maximum size of array in instances of AnimalCollection
const unsigned MAX_ANIMALS = 10;

// Exception thrown when addAnimal is called with a full array
class FullCollection{};
// Exception thrown when removeAnimal is called with an empty array
class EmptyCollection{};


template <class T> class AnimalCollection {
private:
    // all animals in collection are same type
    // this array is implemented as a stack, LIFO.
    T *animals[MAX_ANIMALS];
    // number of animals currently in collection
    // also gives the next empty index to add an animal to
    unsigned animalsCaredFor;
public:
    AnimalCollection();
    ~AnimalCollection();
    unsigned getAnimalsCaredFor() const {
        return animalsCaredFor;
    }

    // AnimalCollection::addAnimal
    // Adds an animal to the AnimalCollection.
    // The animal added must be of the type that the class was initialized with.
    void addAnimal(T *animal);

    // AnimalCollection::removeAnimal
    // Returns the most recently added animal to the stable and deletes it.
    T* removeAnimal();
};

template <class T> AnimalCollection<T>::AnimalCollection() {
    animalsCaredFor = 0;
    for (int i = 0; i < MAX_ANIMALS; i++) {
        animals[i] = NULL;
    }
}

template <class T> AnimalCollection<T>::~AnimalCollection() {
    for (int i = 0; i < MAX_ANIMALS; i++) {
        if (animals[i] != NULL) {
            delete animals[i];
        }
    }
}

template <class T> void AnimalCollection<T>::addAnimal(T *animal) {
    if (animalsCaredFor == MAX_ANIMALS) {
        FullCollection ex;
        throw ex;
    }
    // add the animal in the next free spot
    animals[animalsCaredFor] = animal;

    // increment counter to point to next free spot and recognize that an animal was added
    animalsCaredFor++;
}

template <class T> T* AnimalCollection<T>::removeAnimal() {
    if (animalsCaredFor == 0) {
        EmptyCollection ex;
        throw ex;
    }

    // decrement counter to point to spot animal was last added
    animalsCaredFor--;

    // get most recently added animal
    T* temp = animals[animalsCaredFor];

    // zero out the spot it occupied
    animals[animalsCaredFor] = NULL;

    return temp;
}

#endif //LAB05_STABLE_H
