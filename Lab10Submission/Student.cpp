//
// Created by Kristian Snyder
//

#include "Student.h"

Student::Student(std::string firstName, std::string lastName,
                 std::string mNumber, date birthday, double gpa) {
    FirstName = firstName;
    LastName = lastName;
    MNumber = mNumber;
    Birthday = birthday;
    GPA = gpa;
}

Student::Student(std::string mNumber) {
    MNumber = mNumber;
    FirstName = "";
    LastName = "";
}

std::string Student::GetName() const {
    return FirstName + " " + LastName;
}

std::string Student::GetMNumber() const {
    return MNumber;
}

int Student::GetAge() const {
    time_t nowRaw = time(nullptr);
    tm* now = localtime(&nowRaw);

    int years = now->tm_year - (Birthday.year - 1900);
    // check for negative age based on current clock
    if (years < 0) {
        return 0;
    }

    // tm uses 0-indexed months
    if (now->tm_mon + 1 >= Birthday.month) {
        if (now->tm_mon + 1 == Birthday.month) {
            // not 0-indexed days, though.
            if (now->tm_mday >= Birthday.day) {
                return years;
            } else {
                return years - 1;
            }
        }
        return years;
    }
    return years - 1;
}

bool Student::operator>(const Student& rhs) const {
    return atoi(GetMNumber().substr(1).c_str()) > atoi(rhs.GetMNumber().substr(1).c_str());
}

bool Student::operator<(const Student& rhs) const {
    // negate whatever > gives
    return !(*this > rhs);
}

bool Student::operator<=(const Student& rhs) const {
    return *this < rhs || *this == rhs;
}

bool Student::operator>=(const Student& rhs) const {
    return *this > rhs || *this == rhs;
}

bool Student::operator==(const Student& rhs) const {
    return GetMNumber() == rhs.GetMNumber();
}

bool Student::operator!=(const Student& rhs) const {
    return !(*this == rhs);
}

Student::operator std::string() const {
    return GetMNumber();
}

std::ostream &operator<<(std::ostream& stream, const Student& student) {
    if (student.FirstName == "" || student.LastName == "") {
        stream << "Student M# (other values not set): " << student.GetMNumber() << std::endl;
    } else {
        stream << "Student: " << student.GetName() << std::endl
               << "M Number: " << student.GetMNumber() << std::endl
               << "GPA: ";
        if (student.GPA > 0) {
            stream << std::setprecision(2) << student.GPA;
        } else {
            stream << "None";
        }
        stream << std::endl << "Birthday: " << student.Birthday.year << "/"
               << student.Birthday.month << "/" << student.Birthday.day << std::endl
               << "Age: " << student.GetAge();
    }
    return stream;
}