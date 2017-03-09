#include <iostream>
#define TWOPLAYER true
#include "Stack.h"
#include "Disk.h"
using namespace std;

// identifiers for each player
const int Player2 = 1;
const int Player1 = 0;
// flag to say no one has won
const int NoWinner = -1;

////////////////////////////////
// Helper function definitions
////////////////////////////////

// exception class for an impossible or illegal move by the player.
class InvalidMove {};

// invoke moving the disk between two stacks.
// takes a player to make sure they can move the disk they want.
void moveDisk(Stack<Disk>* from, Stack<Disk>* to, int player);

// determines if a player has a valid move to make given a
// game state.
bool canMakeMove(Stack<Disk>* stacks[3], int player);

// get the height of the tower from the user.
int getStackHeight();

// get the stacks to move from and to from the user.
// returns an array: [from, to]
int* getSelections();

// determine if the player has finished the game.
// NoWinner means no player has won.
int done(Stack<Disk>* stacks[3], int disksPerPlayer);

// print the game state.
void printStacks(Stack<Disk>* stacks[3]);

///////////////////////////////////
// End helper function definitions
///////////////////////////////////

// main loop of the game.
int main() {
    cout << endl << "Welcome to Towers of Hanoi - Two Player" << endl
         << "The first player to get all of their disks to the opposite tower wins." << endl;

    int height = getStackHeight();

    // for the two-player game, the max height is doubled.
    // this allows for more creative play and fewer stalemates.

    // the array of stacks to use
    Stack<Disk>* stacks[3] = {new Stack<Disk>(height * 2), new Stack<Disk>(height * 2), new Stack<Disk>(height * 2)};

    for (int i = height; i > 0; i--) {
        // add player 1's disks to left, player 2's to right
        stacks[0]->push(new Disk(i, Player1));
        stacks[2]->push(new Disk(i, Player2));
    }

    int winner = NoWinner;
    int currentPlayer = Player1;

    // check if the player is done at the *start* of their turn
    while (winner == NoWinner) {
        cout << "Player " << currentPlayer + 1 << "'s turn." << endl;
        if (canMakeMove(stacks, currentPlayer)) {
            try {
                // determine what move the player wants to make
                int *selections = getSelections();
                moveDisk(stacks[selections[0] - 1], stacks[selections[1] - 1], currentPlayer);
                printStacks(stacks);
                // switch players
                currentPlayer = !currentPlayer;
            } catch (...) {
                // doesn't display current state if the move is invalid
                // since it hasn't changed
                cout << "You can't make that move. Try another!" << endl;
            }

            // check if someone has won
            winner = done(stacks, height);
        } else {
            cout << "You cannot make a legal move. Play passes to next player." << endl;
            // switch players
            currentPlayer = !currentPlayer;
        }
    }

    cout << "Player " << winner + 1 << " has won!";

    for (int i = 0; i < 3; i++) {
        delete stacks[i];
    }
    return 0;
}

/////////////////////////////
/// UI and helper functions
/////////////////////////////

void moveDisk(Stack<Disk>* from, Stack<Disk>* to, int player) {
    // make sure there's a disk to move and a space to move it to
    // avoids having a disk to move, but no space available in the
    // destination stack, removing the disk and placing the player
    // in an unwinnable state.
    // also check whether the top of the stack they wish to move from
    // is their disk.
    if (from->length() == 0 || to->isFull() || from->top()->getPlayerNumber() != player) {
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

bool canMakeMove(Stack<Disk>* stacks[3], int player) {
    // check if the player has a disk to move,
    // and then check if they can move it to another spot.
    for (int i = 0; i < 3; i++) {
        // disk is theirs
        if (stacks[i]->length() > 0 && stacks[i]->top()->getPlayerNumber() == player) {
            for (int j = 0; j < 3; j++) {
                // destination is valid and also a different stack
                if (j != i && (stacks[j]->length() == 0 || *stacks[i]->top() < *stacks[j]->top())) {
                    return true;
                }
            }
        }
    }
    return false;
    // at this point, the player has disks to move .
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

int done(Stack<Disk>* stacks[3], int disksPerPlayer) {
    if (stackContainsAllDisksOfPlayer(stacks[0], Player2, disksPerPlayer) ||
            stackContainsAllDisksOfPlayer(stacks[1], Player2, disksPerPlayer)) {
        return Player2;
    } else if (stackContainsAllDisksOfPlayer(stacks[2], Player1, disksPerPlayer) ||
            stackContainsAllDisksOfPlayer(stacks[1], Player1, disksPerPlayer)) {
        return Player1;
    } else {
        return NoWinner;
    }
}

bool stackContainsAllDisksOfPlayer(Stack<Disk>* stack, int playerNumber, int disks) {
    int disksFromPlayer = 0;
    if (stack->length() < disks) {
        return false;
    } else {
        for (int i = 0; i < stack->length(); i++) {
            // check if any disks aren't from the player passed in
            if (stack->stack[i]->getPlayerNumber() == playerNumber) {
                disksFromPlayer++;
            }
        }
    }
    // stack contains all the player's disks
    return disksFromPlayer == disks;
}

void printStacks(Stack<Disk>* stacks[3]) {
    for (int i = 0; i < 3; i++) {
        cout << "Stack " << i+1 << ":" << endl;
        print(stacks[i]);
        cout << endl;
    }
}