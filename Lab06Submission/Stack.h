//
// Created by Kristian Snyder on 2/20/17.
//

#ifndef LAB06_STACK_H
#define LAB06_STACK_H

#include <iostream>
#if TWOPLAYER
#include "Disk.h"
#endif
using namespace std;

template <class T>
class Stack {

private:
    T** stack;
    // next open location
    unsigned next;
    unsigned maxLength = 0;

public:
    class EmptyStackException {};
    class FullStackException {};

    Stack(unsigned arraySize);
    ~Stack();

    // Add a pointer to the top of the stack
    // Parameters:
    // item - the item to be put on the top of the stack
    //
    // Returns void
    void push(T* item);

    // Get a pointer from the top of the stack and remove it.
    // Returns a pointer of type T.
    T* pop();

    // Get the pointer of the object at the top of the stack without removal.
    // Returns a pointer of type T.
    T* top();

    // get the number of items in the stack
    int length();

    // check if the stack is full
    bool isFull();

    // empty the stack of all contents
    // Returns void
    void empty();

    // prints the contents of an int stack to the screen.
    friend void print(Stack<int>* stack);

    // using Disks bloats the resulting binary and requires implementation even if it isn't used,
    // so this prevents that if it isn't necessary.
#if TWOPLAYER
    friend void print(Stack<Disk>* stack);

    // determines if the contents of a stack contain all of a player's disks.
    friend bool stackContainsAllDisksOfPlayer(Stack<Disk>* stack, int playerNumber, int disks);
#endif
};

template <class T>
Stack<T>::Stack(unsigned arraySize) {
    stack = new T*[arraySize];
    for (int i = 0; i < arraySize; i++) {
        stack[i] = nullptr;
    }
    next = 0;
    maxLength = arraySize;
}



template <class T>
Stack<T>::~Stack() {
    delete[] stack;
    stack = nullptr;
}

template <class T>
void Stack<T>::push(T* item) {
    if (next == maxLength) {
        cout << "Failed to push.";
        throw FullStackException();
    }
    stack[next] = item;
    next++;
}

template <class T>
T* Stack<T>::pop() {
    if (next == 0) {
        throw EmptyStackException();
    }
    next--;
    return stack[next];
}

template <class T>
T* Stack<T>::top() {
    if (next == 0) {
        throw EmptyStackException();
    }
    return stack[next-1];
}

template <class T>
int Stack<T>::length() {
    return next;
}

template <class T>
bool Stack<T>::isFull() {
    return next == maxLength;
}

template <class T>
void Stack<T>::empty() {
    // iterate through array and delete each element
    // don't eliminate the array entirely since we still want to use it
    for (int i = 0; i < maxLength; i++) {
        if (stack[i] != nullptr) {
            delete stack[i];
            stack[i] = nullptr;
        }
    }
}

void print(Stack<int>* stack) {
    // we want to print all plates centered correctly,
    // so the width is always an odd number.
    // doubling the width of the maximum plate + 1
    // gives enough space for all the others to occupy
    // the odd widths in between.
    int maxWidth = stack->maxLength * 2 + 1;
    for (int i = stack->maxLength-1; i >= 0; i--) {
        if (i < stack->next) {
            int width = *(stack->stack[i]);
            // always makes the width odd so it centers on the pole
            width = width * 2 + 1;
            for (int j = 0; j < (maxWidth - width) / 2; j++) {
                // print spaces to left of plate
                cout << " ";
            }
            for (int j = 0; j < width; j++) {
                // print plate
                cout << "-";
            }
            for (int j = 0; j < (maxWidth - width) / 2; j++) {
                // print spaces to right of plate;
                cout << " ";
            }
        } else {
            for (int j = 0; j < maxWidth; j++) {
                if (j == maxWidth / 2) {
                    // print pole in middle
                    cout << "|";
                } else {
                    // print spaces to left or right of pole
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

#if TWOPLAYER
void print(Stack<Disk>* stack) {
    // we want to print all plates centered correctly,
    // so the width is always an odd number.
    // doubling the width of the maximum plate + 1
    // gives enough space for all the others to occupy
    // the odd widths in between.
    int maxWidth = stack->maxLength * 2 + 1;
    for (int i = stack->maxLength-1; i >= 0; i--) {
        if (i < stack->next) {
            int width = stack->stack[i]->getValue();
            // always makes the width odd so it centers on the pole
            width = width * 2 + 1;
            for (int j = 0; j < (maxWidth - width) / 2; j++) {
                // print spaces to left of plate
                cout << " ";
            }
            for (int j = 0; j < width; j++) {
                // print plate
                cout << "-";
            }
            for (int j = 0; j < (maxWidth - width) / 2; j++) {
                // print spaces to right of plate;
                cout << " ";
            }
            // print whose disk it is
            cout << " Player " << stack->stack[i]->getPlayerNumber() + 1;
        } else {
            for (int j = 0; j < maxWidth; j++) {
                if (j == maxWidth / 2) {
                    // print pole in middle
                    cout << "|";
                } else {
                    // print spaces to left or right of pole
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}
#endif


#endif //LAB06_STACK_H
