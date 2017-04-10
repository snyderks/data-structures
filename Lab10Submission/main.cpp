#include <iostream>
#include <array>
#include <sstream>
#include "Node.h"
#include "BTree.h"
#include "Student.h"


enum Operation { InsertItem = 0, FindItem, PrintTree,
    GetTreeHeight, GetTreeSize, Length = GetTreeSize + 1 };

// Get a selection from the user. Guaranteed to be valid.
Operation selectOperation();

// Get an integer from the user. Guaranteed to be an integer.
int getNumberFromUser();


int main() {
    // Code for task 2
//    BTree<int> tree = BTree<int>();
//
//    while (true) {
//        Operation op = selectOperation();
//
//        switch (op) {
//            case InsertItem: {
//                int num = getNumberFromUser();
//                if (tree.FindItem(&num) == nullptr) {
//                    tree.InsertItem(&num);
//                } else {
//                    std::cout << num << " was already in tree. Try again." << std::endl;
//                }
//                break;
//            }
//            case FindItem: {
//                int num = getNumberFromUser();
//                int* result = tree.FindItem(&num);
//                if (result != nullptr) {
//                    std::cout << "Retrieved " << *result << std::endl;
//                } else {
//                    std::cout << num <<  " was not in the tree." << std::endl;
//                }
//                break;
//            }
//            case PrintTree: {
//                std::cout << std::endl;
//                tree.PrintTree();
//                std::cout << std::endl;
//                break;
//            }
//            case GetTreeSize: {
//                std::cout << "Tree is of size " << tree.GetTreeSize() << std::endl;
//                break;
//            }
//            case GetTreeHeight: {
//                std::cout << "Tree is of height " << tree.GetTreeHeight() << std::endl;
//                break;
//            }
//            default:
//                std::cout << "Incorrect selection." << std::endl;
//                break;
//        }
//
//        std::cout << std::endl << "Continue? (Y/N) ";
//        std::string input;
//        getline(std::cin, input);
//        if (input == "N" || input == "n" || input == "No" || input == "no" ||
//            input == "nO" || input == "NO" || input == "Nope") {
//            break;
//        }
//    }
//
//    return 0;

    srand(time(NULL));
    for (int run = 0; run < 4; run++) {
        const int STUDENTS_TO_ADD = 50;

        BTree<Student> deg3tree = BTree<Student>(3);
        BTree<Student> deg4tree = BTree<Student>(4);
        BTree<Student> deg5tree = BTree<Student>(5);

        Student *students[STUDENTS_TO_ADD] = {nullptr};

        int deg3moves = 0;
        int deg4moves = 0;
        int deg5moves = 0;

        // generate students
        for (int i = 0; i < STUDENTS_TO_ADD; i++) {
            while (true) {
                std::stringstream ss;
                ss << std::setw(8) << std::setfill('0') << rand() % 100000000 + 1;
                auto mNum = ss.str();
                bool duplicate = false;
                for (int j = 0; j < STUDENTS_TO_ADD; j++) {
                    if (students[j] == nullptr) {
                        break;
                    }
                    if (students[j]->GetMNumber() == mNum) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    students[i] = new Student("M" + mNum);
                    break;
                }
            }

        }

        // add students
        for (int i = 0; i < STUDENTS_TO_ADD; i++) {
            deg3tree.InsertItem(students[i]);
            deg4tree.InsertItem(students[i]);
            deg5tree.InsertItem(students[i]);
        }

        // access students (10 times)
        const int NUM_TRIALS = 10;
        for (int trials = 0; trials < NUM_TRIALS; trials++) {
            for (int i = 0; i < STUDENTS_TO_ADD; i++) {
                Student* result;

                result = deg3tree.FindItem(students[i]);
                if (result == nullptr) {
                    std::cout << "Failed to retrieve " << *students[i] << " from deg3tree" << std::endl;
                }

                result = deg4tree.FindItem(students[i]);
                if (result == nullptr) {
                    std::cout << "Failed to retrieve " << *students[i] << " from deg4tree" << std::endl;
                }

                result = deg5tree.FindItem(students[i]);
                if (result == nullptr) {
                    std::cout << "Failed to retrieve " << *students[i] << " from deg5tree" << std::endl;
                }
            }

            deg3moves += deg3tree.GetMoves();
            deg4moves += deg4tree.GetMoves();
            deg5moves += deg5tree.GetMoves();
        }

        auto avgdeg3 = (double)deg3moves / NUM_TRIALS;
        auto avgdeg4 = (double)deg4moves  / NUM_TRIALS;
        auto avgdeg5 = (double)deg5moves  / NUM_TRIALS;

        std::cout << std::endl << "Run " << run + 1 << " (" << NUM_TRIALS << " trials)" << std::endl
                  << "-----------------------" << std::endl
                  << "Degree 3: " << avgdeg3 << " total moves, "
                  << std::setprecision(3) << avgdeg3 / STUDENTS_TO_ADD << " on average."
                  << std::endl
                  << "Degree 4: " << avgdeg4 << " total moves, "
                  << avgdeg4 / STUDENTS_TO_ADD << " on average." << std::endl
                  << "Degree 5: " << avgdeg5 << " total moves, "
                  << avgdeg5 / STUDENTS_TO_ADD << " on average." << std::endl
                  << std::endl;
    }

    return 0;
}

Operation selectOperation() {
    std::cout << std::endl
              << "Please select an operation to perform on the list." << std::endl
              << "1. InsertItem()" << std::endl
              << "2. FindItem()" << std::endl
              << "3. PrintTree()" << std::endl
              << "4. GetTreeHeight()" << std::endl
              << "5. GetTreeSize()" << std::endl;
    std::string input;
    while (true) {
        getline(std::cin, input);
        try {
            int selection = std::atoi(input.c_str());
            if (selection > 0 && selection <= Length) {
                // return between 0 and Length - 1
                return Operation(selection - 1);
            }
        } catch (...) {
            // Pass to error below
        }
        std::cout << "Invalid selection. Try again." << std::endl;
    }
}

int getNumberFromUser() {
    while (true) {
        std::cout << std::endl << "Please enter a number: " << std::endl;
        std::string input;
        getline(std::cin, input);
        try {
            return std::atoi(input.c_str());
        } catch (...) {
            std::cout << "Invalid input. Try again." << std::endl;
        }
    }

}