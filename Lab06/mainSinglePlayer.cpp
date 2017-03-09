#include <iostream>
#include "Stack.h"
using namespace std;

// exception class for an impossible or illegal move by the player.
class InvalidMove {};

// invoke moving the disk between two stacks.
template <class T>
void moveDisk(Stack<T>* from, Stack<T>* to);

// get the height of the tower from the user.
int getStackHeight();

// get the stacks to move from and to from the user.
// returns an array: [from, to]
int* getSelections();

// determine if the player has finished the game.
bool done(Stack<int>* stacks[3]);

// print the game state.
void printStacks(Stack<int>* stacks[3]);

// main loop of the game.
int main() {
    cout << endl << "Welcome to Towers of Hanoi - Single Player" << endl << endl;

    int height = getStackHeight();

    // the array of stacks to use
    Stack<int>* stacks[3] = {new Stack<int>(height), new Stack<int>(height), new Stack<int>(height)};

    for (int i = height; i > 0; i--) {
        stacks[0]->push(new int(i));
    }

    // check if the player is done at the *start* of their turn
    while (!done(stacks)) {
        try {
            // determine what move the player wants to make
            int *selections = getSelections();
            moveDisk(stacks[selections[0]-1], stacks[selections[1]-1]);
            printStacks(stacks);
        } catch (...) {
            // doesn't display current state if the move is invalid
            // since it hasn't changed
            cout << "You can't make that move. Try another!" << endl;
        }
    }

    cout << "You win!";

    for (int i = 0; i < 3; i++) {
        delete stacks[i];
    }
    return 0;
}

/////////////////////////////
/// UI and helper functions
/////////////////////////////

template <class T>
void moveDisk(Stack<T>* from, Stack<T>* to) {
    // make sure there's a disk to move and a space to move it to
    // avoids having a disk to move, but no space available in the
    // destination stack, removing the disk and placing the player
    // in an unwinnable state.
    if (from->length() == 0 || to->isFull()) {
        throw InvalidMove();
    }
    try {
        // make sure the disk to move is smaller than the top on the target
        // short-circuits to avoid an exception if the target has no disks
        if (to->length() == 0 || *from->top() < *to->top()) {
            // execute the move
            to->push(from->pop());
        } else {
            throw InvalidMove();
        }
    } catch (...) {
        // any issues with the stacks count as an invalid move
        throw InvalidMove();
    }
}

int* getSelections() {
    // get first number
    int from = 0;
    string input = "";
    // number must be in this range
    while (from < 1 || from > 3) {
        cout << "Enter the stack to move from (1-3): ";
        // get the input and attempt to convert to a number.
        getline(cin, input);
        try {
            from = stoi(input);
        } catch (...) {
            cout << "Invalid input. Try again." << endl;
        }
    }

    int to = 0;
    // number also cannot be the previous number
    while (to < 1 || to > 3 || to == from) {
        cout << "Enter a different stack to move to (1-3): ";
        // get the input and attempt to convert to a number.
        getline(cin, input);
        try {
            to = stoi(input);
            if (to == from) {
                // make sure the user knows the input is invalid
                cout << "Invalid input. Try again." << endl;
            }
        } catch (...) {
            cout << "Invalid input. Try again." << endl;
        }
    }
    cout << endl;
    return new int[2] {from, to};
}

int getStackHeight() {
    int height = 0;
    string input = "";
    // number must be greater than 0
    while (height <= 0) {
        cout << "Enter the height of the tower: ";
        // get the input and attempt to convert to a number.
        getline(cin, input);
        try {
            height = stoi(input);
        } catch (...) {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return height;
}

bool done(Stack<int>* stacks[3]) {
    if (stacks[1]->isFull() || stacks[2]->isFull()) {
        return true;
    } else {
        return false;
    }
}

void printStacks(Stack<int>* stacks[3]) {
    for (int i = 0; i < 3; i++) {
        cout << "Stack " << i+1 << ":" << endl;
        print(stacks[i]);
        cout << endl;
    }
}