#include <iostream>
#include "OrderedList.h"
#include "OrderedListReverseSearch.h"
#include "OrderedListOpenSpaces.h"

// gives extra space to list with open spaces
const int ARRAY_LENGTH = 10;

// number of trials to run
const int NUM_RUNS = 100;

const int MAX_INT = 50;
const int MIN_INT = 1;

const int INSERTION = 1;
const int DELETION = 0;

const int MAX_INSERTIONS = 30;
const int MAX_DELETIONS = 25;
const int MAX_OPERATIONS = MAX_INSERTIONS + MAX_DELETIONS;

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    OrderedList<int> *normal = new OrderedList<int>(ARRAY_LENGTH);
    OrderedListReverseSearch<int> *reverseSearch = new OrderedListReverseSearch<int>(ARRAY_LENGTH);
    OrderedListOpenSpaces<int> *openSpaces = new OrderedListOpenSpaces<int>(ARRAY_LENGTH);

    // using the ordered list to track what's been inserted
    OrderedList<int> *added = new OrderedList<int>(MAX_INSERTIONS);

    // count operations for each
    int normalOps, reverseOps, openOps = 0;

    for (int j = 0; j < NUM_RUNS; j++) {
        int insertions = 0;
        int deletions = 0;
        for (int i = 0; i < MAX_OPERATIONS; i++) {
            int selection = -1;
            if (insertions == MAX_INSERTIONS) {
                selection = DELETION;
            } else if (deletions == MAX_DELETIONS) {
                selection = INSERTION;
            } else {
                // choose between 0 and 1
                selection = rand() % 2;
            }

            if (selection == INSERTION) {
                // in range of MIN_INT to MAX_INT
                int *to_insert = new int(rand() % MAX_INT + MIN_INT);

                added->AddItem(to_insert); // should crash if this fails.

                cout << "Inserting " << *to_insert << endl;

                try {
                    normal->AddItem(to_insert);
                } catch (...) {
                    cout << "Failed to insert into OrderedList." << endl;
                }

                try {
                    reverseSearch->AddItem(to_insert);
                } catch (...) {
                    cout << "Failed to insert into OrderedListReverseSearch." << endl;
                }

                try {
                    openSpaces->AddItem(to_insert);
                } catch (...) {
                    cout << "Failed to insert into OrderedListOpenSpaces." << endl;
                }

                insertions++;
            } else {
                int *to_delete;

                if (insertions == 0 || added->Length() == 0) {
                    // never going to retrieve this successfully
                    to_delete = new int(rand() % MAX_INT + MIN_INT);
                } else {
                    // make sure what we're retrieving exists
                    to_delete = added->RemoveItem(rand() % added->Length());
                }

                cout << "Attempting to delete " << *to_delete << endl;

                try {
                    normal->RemoveItem(to_delete);
                } catch (...) {
                    cout << "Failed to delete from OrderedList." << endl;
                }

                try {
                    reverseSearch->RemoveItem(to_delete);
                } catch (...) {
                    cout << "Failed to delete from OrderedListReverseSearch." << endl;
                }

                try {
                    openSpaces->RemoveItem(to_delete);
                } catch (...) {
                    cout << "Failed to delete from OrderedListOpenSpaces." << endl;
                }

                deletions++;
            }

            cout << "OrderedList: ";
            normal->PrintList();

            cout << "OrderedListReverseSearch: ";
            reverseSearch->PrintList();

            cout << "OrderedListOpenSpaces: ";
            openSpaces->PrintList();

            cout << endl;
        }

        // add the operations to the counters
        normalOps += normal->GetOperationsAndReset();
        reverseOps += reverseSearch->GetOperationsAndReset();
        openOps += openSpaces->GetOperationsAndReset();

        // empty the lists
        normal->MakeEmpty();
        reverseSearch->MakeEmpty();
        openSpaces->MakeEmpty();
        added->MakeEmpty();

    }

    cout << "\t\t\t\t\t\t\tTotal operations\t\tAverage operations" << endl;
    cout << "OrderedList:\t\t\t\t\t" << normalOps << "\t\t\t\t\t\t" << normalOps / NUM_RUNS << endl;
    cout << "OrderedListReverseSearch:\t\t" << reverseOps << "\t\t\t\t\t\t" << reverseOps / NUM_RUNS << endl;
    cout << "OrderedListOpenSpaces:\t\t\t" << openOps << "\t\t\t\t\t\t" << openOps / NUM_RUNS << endl;
}