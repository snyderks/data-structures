//
// Created by Kristian Snyder on 1/23/17.
//

#ifndef LAB02_PRODUCT_H
#define LAB02_PRODUCT_H
#import <string>
using namespace std;

class Product {
public:
    Product();
    Product(string ID, string units, string price);
    int id;
    int units;
    double price;
    double sales;
};


#endif //LAB02_PRODUCT_H
