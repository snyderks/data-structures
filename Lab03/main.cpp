#include <iostream>
#include "Vector.h"
using namespace std;

// handles getting the vector to apply the operation to
Vector getRhs() {
    double x = 0;
    double y = 0;
    cout << "Enter the second vector:" << endl
         << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    return Vector(x, y);
}

// handles getting a scalar instead of a vector.
double getRhsScalar() {
    double v = 0;
    cout << "Enter a number: ";
    cin >> v;
    return v;
}

int main() {
    double x = 0;
    double y = 0;

    // Get the first vector values
    cout << "Enter the x value for the vector: ";
    cin >> x;
    cout << "Enter the y value for the vector: ";
    cin >> y;

    Vector lhs = Vector(x, y);
    // break out of loop when done. Avoids extra complexity.
    while (true) {
        bool invalidOp = true;
        string operation = "";
        while (invalidOp){
            cout << "Enter the operation to perform" << endl
                 << "(+, -, *, /, ==)" << endl;
            cin >> operation;

            invalidOp = false;

            // apply the correct operation based on input
            if (operation == "+") {
                lhs + getRhs();
            } else if (operation == "-") {
                lhs - getRhs();
            } else if (operation == "*") {
                lhs * getRhsScalar();
            } else if (operation == "/") {
                lhs / getRhsScalar();
            } else if (operation == "==") {
                if (lhs == getRhs()) {
                    cout << "The two vectors are equal.";
                } else {
                    cout << "The two vectors are not equal.";
                }
                cout << endl;
            } else {
                cout << "Invalid operator. Try again." << endl;
                invalidOp = true;
            }
        }
        // after the operation, print the resulting vector (unchanged for ==)
        lhs.print();

        string again = "";
        cout << "Continue? (Y/N) ";
        cin >> again;
        // continue unless user types something resembling "no"
        if (again == "N" || again == "n" || again == "no" || again == "No" || again == "NO") {
            break;
        }
    }
}