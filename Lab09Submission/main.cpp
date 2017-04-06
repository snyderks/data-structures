#include <iostream>
#include <sstream>
#include "HashTable.h"
#include "Student.h"
#include "ChainedHashTable.h"

const short MNumberLength = 9;

enum Operation { AddItem = 0, RemoveItem, GetItem, PrintTable, Length = PrintTable + 1 };

// UI helper functions

// Input

/// \brief Retrieves an MNumber from a user.
/// \returns A student with only an MNumber.
Student* getMNumber();

/// \brief Gets a first name for a student.
/// \returns A first name. No guarantees for its content.
std::string getFirstName();

/// \brief Gets a last name for a student.
/// \returns A last name. No guarantees for its content.
std::string getLastName();

/// \brief Gets a GPA for a student.
/// \returns 0 if the user declined to enter one, otherwise a GPA.
double getGPA();

/// \brief Gets a birthday for a student.
/// \returns The date of the student's birthday.
date getBirthday();

/// \brief Retrieves a full student from a user.
/// \returns A fully populated student (GPA may optionally not be valid)
Student* getFullStudent();

/// \brief Allows the user to select an option to perform on the linked list.
/// \returns Their selection
Operation selectOperation();

int main() {
    // Code for Tasks 3 and 4t
//    auto linearTable = ChainedHashTable<Student>(100);
//
//    while (true) {
//        switch (selectOperation()) {
//            case AddItem:
//                linearTable.AddItem(getFullStudent());
//                std::cout << std::endl << std::endl;
//                linearTable.PrintTable();
//                break;
//            case RemoveItem: {
//                Student *s = linearTable.RemoveItem(getMNumber());
//                if (s != nullptr) {
//                    std::cout << "Retrieved student: " << std::endl << *s;
//                } else {
//                    std::cout << "Couldn't find that student." << std::endl;
//                }
//                std::cout << std::endl;
//                linearTable.PrintTable();
//                break;
//            }
//            case GetItem: {
//                Student *s = linearTable.GetItem(getMNumber());
//                try {
//                    if (s != nullptr) {
//                        std::cout << "Retrieved student: " << std::endl << *s;
//                    } else {
//                        std::cout << "Reached end of list." << std::endl;
//                    }
//                } catch (...) {
//                    std::cout << "The list is empty." << std::endl;
//                }
//                break;
//            }
//            case PrintTable:
//                linearTable.PrintTable();
//                break;
//            default:
//                std::cout << "Invalid selection." << std::endl;
//
//        }
//        std::cout << std::endl << "Continue? (Y/N) ";
//        std::string input;
//        getline(std::cin, input);
//        if (input == "N" || input == "n" || input == "No" || input == "no" ||
//            input == "nO" || input == "NO" || input == "Nope") {
//            break;
//        }
//    }

    const int TABLE_SIZES[4] = {100, 150, 200, 250};
    srand(time(NULL));
    for (int run = 0; run < 4; run++) {
        const int STUDENTS_TO_ADD = 50;
        const int TABLE_SIZE = TABLE_SIZES[run];

        auto chainTable = ChainedHashTable<Student>(TABLE_SIZE);
        auto linearTable = HashTable<Student>(TABLE_SIZE);

        Student *students[STUDENTS_TO_ADD] = {nullptr};

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
            chainTable.AddItem(students[i]);
            linearTable.AddItem(students[i]);
        }

        // access students (10 times)
        const int NUM_TRIALS = 10;
        int linearAccesses = 0;
        int chainAccesses = 0;
        for (int trials = 0; trials < NUM_TRIALS; trials++) {
            for (int i = 0; i < STUDENTS_TO_ADD; i++) {
                chainTable.GetItem(students[i]);
                linearTable.GetItem(students[i]);
            }

            linearAccesses += linearTable.getChecks();
            chainAccesses += chainTable.getChecks();
        }

        auto avgLinear = (double)linearAccesses / NUM_TRIALS;
        auto avgChain =  (double)chainAccesses  / NUM_TRIALS;

        std::cout << std::endl << "-----------------------" << std::endl
                  << "Run " << run + 1 << " (" << NUM_TRIALS << " trials)" << std::endl
                  << "Array Size: " << TABLE_SIZE << std::endl
                  << "Linear Probing: " << avgLinear << " total checks, "
                  << std::setprecision(3) << avgLinear / STUDENTS_TO_ADD << " on average."
                  << std::endl
                  << "Chaining: " << avgChain << " total checks, "
                  << avgChain / STUDENTS_TO_ADD << " on average." << std::endl
                  << std::endl;
    }

    return 0;
}

Student* getMNumber() {
    while (true) {
        std::cout << std::endl << "Please enter an M# for the student: "
                  << "(Must start with M and then contain 8 digits)" << std::endl;
        std::string input;
        getline(std::cin, input);

        if (input.length() == MNumberLength && input[0] == 'M') {
            bool valid = true;
            for (int i = 1; i < MNumberLength; i++) {
                if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return new Student(input);
            }
        }
        std::cout << "The M# you entered was invalid. Please try again." << std::endl;
    }
}

std::string getFirstName() {
    std::cout << std::endl << "Please enter a first name: ";
    std::string input;
    getline(std::cin, input);
    return input;
}

std::string getLastName() {
    std::cout << std::endl << "Please enter a last name: ";
    std::string input;
    getline(std::cin, input);
    return input;
}

double getGPA() {
    while (true) {
        std::cout << std::endl << "Please enter a GPA (enter to skip): ";
        std::string input;
        getline(std::cin, input);
        if (input.length() == 0) {
            return 0.0;
        }
        try {
            double gpa = std::atof(input.c_str());
            return gpa;
        } catch (...) {
            std::cout << "Invalid GPA. Try again." << std::endl;
        }
    }
}

date getBirthday() {
    while (true) {
        std::cout << std::endl << "Enter a birthday (format YYYY/MM/DD): ";
        std::string input;
        getline(std::cin, input);
        // YYYY/MM/DD is 10 characters
        if (input.length() == 10 && input[4] == '/' && input[7] == '/') {
            try {
                int year = std::atoi(input.substr(0, 4).c_str());
                // year must be AD
                if (year < 0) {
                    throw;
                }

                int month = std::atoi(input.substr(5, 2).c_str());
                // month must be between 1 and 12
                if (month < 1 || month > 12) {
                    throw;
                }

                int day = std::atoi(input.substr(8).c_str());
                // only checking basic day logic
                if (day < 1 || day > 31) {
                    throw;
                }
                date retval = {(unsigned)year, (unsigned)month, (unsigned)day};
                return retval;
            } catch (...) {
                // Pass below to error
            }
        }
        std::cout << "Invalid format. Try again." << std::endl;
    }
}

Student* getFullStudent() {
    // first have them enter the M# then use it for the rest of the flow
    Student* student = getMNumber();

    return new Student(getFirstName(), getLastName(),
                       student->GetMNumber(), getBirthday(), getGPA());
}

Operation selectOperation() {
    std::cout << std::endl
              << "Please select an operation to perform on the table." << std::endl
              << "1. AddItem()" << std::endl
              << "2. RemoveItem()" << std::endl
              << "3. GetItem()" << std::endl
              << "4. PrintTable()" << std::endl;
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