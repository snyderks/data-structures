//
// Created by Kristian Snyder on 1/30/17.
//

#include "Vector.h"
#include <cmath>
#include <iostream>
using namespace std;

// degrees for half a circle
const int HALFCIRCLE = 180;

Vector::Vector() {
    // default values
    x = 0;
    y = 0;
}

Vector::Vector(double xVal, double yVal) {
    x = xVal;
    y = yVal;
}

Vector::Vector(double magnitude, double angle, bool radians) {
    if (!radians) {
        // convert degrees to radians
        angle = angle * M_PI / HALFCIRCLE;
    }
    // split the magnitude into the sine (horizontal) and cosine (vertical)
    x = cos(angle) * magnitude;
    y = sin(angle) * magnitude;
}

// nothing to actually delete. Primitives are handled automatically.
Vector::~Vector() {};

double Vector::getMagnitude() {
    return sqrt(x * x + y * y);
}

double Vector::getAngle(bool radians) {
    // arc tangent takes the side opposite the angle divided by the side adjacent to the angle
    // here, opposite is y and adjacent is x.
    double angle = atan(y / x);

    // conversion to degrees. atan() returns radians.
    if (!radians) {
        angle = angle * HALFCIRCLE / M_PI;
    }
    return angle;
}

void Vector::print() {
    cout << "X: " << x << " Y: " << y << " Magnitude: " << getMagnitude() << " Angle: " << getAngle(true) << endl;
}

// operator overloading
void Vector::operator+ (const Vector &rhs) {
    // add the components of each vector. Store in left vector.
    x += rhs.getX();
    y += rhs.getY();
}

void Vector::operator- (const Vector &rhs) {
    // subtract components of right side from left vector. Store in left vector.
    x -= rhs.getX();
    y -= rhs.getY();
}
void Vector::operator* (double n) {
    // multiply each component by a scalar. Store in left vector.
    x *= n;
    y *= n;
}
void Vector::operator/ (double n) {
    // prevent division by 0
    if (n != 0) {
        // divide each component by a scalar. Store in left vector.
        x /= n;
        y /= n;
    }
}
bool Vector::operator==(const Vector &rhs) const {
    // as doubles cannot be assured to have the same value,
    // differences below this are assumed to be equivalent.
    const double tolerance = 0.0001;
    if (abs(x - rhs.getX()) < tolerance &&
        abs(y - rhs.getY()) < tolerance) {
        return true;
    }
    return false;
}
