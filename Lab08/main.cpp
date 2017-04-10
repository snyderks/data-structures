#include <iostream>

#include "OrderedLinkedList.h"
#include "Student.h"

const short MNumberLength = 9;

enum Operation { AddItem = 0, GetItem, SeeNext,
        SeeAt, Reset, IsInList, IsEmpty, Size, PrintList, Length = PrintList + 1 };

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

/// \brief Retrieves an index from the user for use in list indexing.
/// \details Makes no guarantees about the index being valid.
/// Only ensures that value returned is a number.
/// \returns The index the user wants to access.
int getIndexFromUser();

int main() {
    OrderedLinkedList<Student>* list = new OrderedLinkedList<Student>();

    while (true) {
        switch(selectOperation()) {
            case AddItem:
                list->AddItem(getFullStudent());
                std::cout << std::endl << std::endl;
                list->PrintList();
                break;
            case GetItem: {
                Student *s = list->GetItem(getMNumber());
                if (s != nullptr) {
                    std::cout << "Retrieved student: " << std::endl << *s;
                } else {
                    std::cout << "Couldn't find that student." << std::endl;
                }
                std::cout << std::endl;
                list->PrintList();
                break;
            }
            case SeeNext: {
                Student *s = list->SeeNext();
                try {
                    if (s != nullptr) {
                        std::cout << "Retrieved student: " << std::endl << *s;
                    } else {
                        std::cout << "Reached end of list." << std::endl;
                    }
                } catch (...) {
                    std::cout << "The list is empty." << std::endl;
                }
                break;
            }
            case SeeAt: {
                try {
                    Student *s = list->SeeAt(getIndexFromUser());
                    std::cout << "Retrieved student: " << std::endl << *s;
                } catch (...) {
                    std::cout << "Index out of range." << std::endl;
                }
                break;
            }
            case Reset:
                list->Reset();
                std::cout << "Successfully reset the next position to read from." << std::endl;
                break;
            case IsInList:
                if (list->IsInList(getMNumber())) {
                    std::cout << "That student is in the list." << std::endl;
                } else {
                    std::cout << "That student is not in the list." << std::endl;
                }
                break;
            case IsEmpty:
                if (list->IsEmpty()) {
                    std::cout << "The list is empty." << std::endl;
                } else {
                    std::cout << "The list is not empty." << std::endl;
                }
                break;
            case Size: {
                int size = list->Size();
                std::cout << "The list has " << size << (size == 1 ? " item" : " items")
                          << " in it." << std::endl;
                break;
            }
            case PrintList:
                list->PrintList();
                break;
            default:
                std::cout << "Invalid selection." << std::endl;

        }
        std::cout << std::endl << "Continue? (Y/N) ";
        std::string input;
        getline(std::cin, input);
        if (input == "N" || input == "n" || input == "No" || input == "no" ||
            input == "nO" || input == "NO" || input == "Nope") {
            break;
        }

    }

    delete list;

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
              << "Please select an operation to perform on the list." << std::endl
              << "1. AddItem()" << std::endl
              << "2. GetItem()" << std::endl
              << "3. SeeNext()" << std::endl
              << "4. SeeAt()" << std::endl
              << "5. Reset()" << std::endl
              << "6. IsInList()" << std::endl
              << "7. IsEmpty()" << std::endl
              << "8. Size()" << std::endl
              << "9. PrintList()" << std::endl;
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
