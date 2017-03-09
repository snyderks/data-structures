//
// Created by Kristian Snyder on 1/30/17.
//

#ifndef LAB03_VECTOR_H
#define LAB03_VECTOR_H


class Vector {
private:
    double x;
    double y;
public:
    double getX() const {
        return x;
    }

    void setX(double val) {
        x = val;
    }

    double getY() const {
        return y;
    }

    void setY(double val) {
        y = val;
    }

    double getMagnitude();
    double getAngle(bool radians);

    void print();

    // operator overloading
    void operator+ (const Vector &rhs);
    void operator- (const Vector &rhs);
    void operator* (double n);
    void operator/ (double n);
    bool operator==(const Vector &rhs) const;

    Vector();
    Vector(double xVal, double yVal);
    Vector(double magnitude, double angle, bool radians);
    ~Vector();
};


#endif //LAB03_VECTOR_H
