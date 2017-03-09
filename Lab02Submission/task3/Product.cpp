//
// Created by Kristian Snyder on 1/23/17.
//

#include "Product.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Product::Product() {
    return;
}

Product::Product(string idIn, string unitsIn, string priceIn) {
    cout << idIn << endl << unitsIn << endl << priceIn << endl;
    id = stoi(idIn);
    units = stoi(unitsIn);
    price = atoi(priceIn.c_str());
}

