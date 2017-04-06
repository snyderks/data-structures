//
// Created by Kristian Snyder
//

#ifndef LAB08_STUDENT_H
#define LAB08_STUDENT_H

#include <string>
#include <iostream>
#include <iomanip>

/// \struct date: provides a basic YMD type for storing dates.
/// Does not manipulate the date or validate it.
struct date {
    /// \property year: the year of the date
    unsigned year;
    /// \property month: the month of the date
    unsigned month;
    /// \property date: the day of the date
    unsigned day;
};

class Student {
private:
    std::string FirstName;
    std::string LastName;
    std::string MNumber;
    double GPA;
    date Birthday;

public:
    /// \brief Constructor for student
    /// \param firstName the first name of the student
    /// \param lastName the last name of the student
    /// \param mNumber the M Number for the student
    /// \param birthday the student's birthday
    /// \param gpa the student's GPA
    Student(std::string firstName, std::string lastName,
            std::string mNumber, date birthday, double gpa = 0.0);

    /// \brief Constructor for student meeting requirements for comparison
    /// \param mNumber the M Number for the student
    Student(std::string mNumber);

    /// \brief Gets the full name of the student
    /// \returns the full name of the student
    std::string GetName() const;

    /// \brief Gets the M Number for the student
    /// \returns the student's M Number
    std::string GetMNumber() const;

    /// \brief Computes the student's age
    /// \returns The age of the student in years
    int GetAge() const;

    /// \brief Checks if M Number of left is greater than right
    /// \returns Whether the left side's M Number is greater
    bool operator>(const Student& rhs) const;

    /// \brief Checks if M Number of left is less than right
    /// \returns Whether the left side's M Number is less
    bool operator<(const Student& rhs) const;

    /// \brief Checks if M Numbers of both are equal
    /// \returns Whether M Numbers of both students are equal
    bool operator==(const Student& rhs) const;

    /// \brief Checks if M Numbers of both are not equal
    /// \returns Whether M Numbers of both students are not equal
    bool operator!=(const Student& rhs) const;

    /// \brief Converts a Student to a string containing the M# of the student.
    operator std::string() const;

    /// \brief overload of ostream operator
    /// \details should not be used except by the built-in streams.
    friend std::ostream &operator<<(std::ostream& stream, const Student& student);
};


#endif //LAB08_STUDENT_H
