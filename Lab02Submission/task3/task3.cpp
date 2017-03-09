// Lab 2 Task 3
// Data Structures CS2028C
// Kristian Snyder

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Product.h"
using namespace std;

const int IDPREFIXLEN = 4;    // "ID: "
const int UNITSPREFIXLEN = 7; // "Units: "
const int PRICEPREFIXLEN = 7; // "Price: "

enum LineType {
    ID = 0,
    Units,
    Price
};

// Function prototypes
void calcSales(Product products[], int numProducts);
void showOrder(const Product products[], int num);
void dualSort(Product products[], int numProducts);
void showTotals(const Product products[], int num);

// NUM_PRODS is the number of products produced.
const int NUM_PRODS = 9;

int main()
{
    cout << "Enter a file to read from: ";

    string fname = "";
    cin >> fname;

    ifstream file;
    file.open(fname, ios::in);

    Product products[NUM_PRODS];

    if (file.is_open()) {
        // used as the length of the array at the end.
        unsigned short productsAdded = 0;

        while (!file.eof() && productsAdded < NUM_PRODS) {
            // Read 3 lines at a time.
            string lines[3];
            bool unexpectEnd = false;
            for (int i = 0; i < 3; i++) {
                getline(file, lines[i]);
                if (lines[i].length() == 0) {
                    // reached the end of the file unexpectedly
                    unexpectEnd = true;
                }
            }
            if (unexpectEnd) {
                break;
            }
            products[productsAdded] =
                    Product(lines[0].substr(IDPREFIXLEN),
                                lines[1].substr(UNITSPREFIXLEN),
                                lines[2].substr(PRICEPREFIXLEN));

            cout << products[productsAdded].id <<
                    products[productsAdded].price << endl;

            productsAdded += 1;

        }

        if (productsAdded > 0) {
            // Calculate each product's sales.
            calcSales(products, productsAdded);

            // Sort the elements in the sales array in descending
            // order and shuffle the ID numbers in the id array to
            // keep them in parallel.
            dualSort(products, productsAdded);

            // Set the numeric output formatting.
            cout << setprecision(2) << fixed << showpoint;

            // Display the products and sales amounts.
            showOrder(products, productsAdded);

            // Display total units sold and total sales.
            showTotals(products, productsAdded);
        } else {
            cout << "No products available." << endl;
        }
    } else {
        cout << "File name is invalid." << endl;
    }


    return 0;
}

//****************************************************************
// Definition of calcSales. Accepts units, prices, and sales     *
// arrays as arguments. The size of these arrays is passed       *
// into the num parameter. This function calculates each         *
// product's sales by multiplying its units sold by each unit's  *
// price. The result is stored in the sales array.               *
//****************************************************************

void calcSales(Product products[], int numProducts)
{
    for (int i = 0; i < numProducts; i++) {
        products[i].sales = products[i].units * products[i].price;
    }
}

//***************************************************************
// Definition of function dualSort. Accepts id and sales arrays *
// as arguments. The size of these arrays is passed into size.  *
// This function performs a descending order selection sort on  *
// the sales array. The elements of the id array are exchanged  *
// identically as those of the sales array. size is the number  *
// of elements in each array.                                   *
//***************************************************************

void dualSort(Product products[], int numProducts)
{
    int startScan, maxIndex;
    Product maxValue;

    for (startScan = 0; startScan < (numProducts - 1); startScan++)
    {
        maxIndex = startScan;
        maxValue = products[startScan];
        for(int index = startScan + 1; index < numProducts; index++)
        {
            if (products[index].sales > maxValue.sales)
            {
                maxValue = products[index];
                maxIndex = index;
            }
        }
        products[maxIndex] = products[startScan];
        products[startScan] = maxValue;
    }
}

//****************************************************************
// Definition of showOrder function. Accepts sales and id arrays *
// as arguments. The size of these arrays is passed into num.    *
// The function first displays a heading, then the sorted list   *
// of product numbers and sales.                                 *
//****************************************************************

void showOrder(const Product products[], int num)
{
    cout << "Product Number\tSales\n";
    cout << "----------------------------------\n";
    for (int index = 0; index < num; index++)
    {
        cout << products[index].id << "\t\t\t\t$";
        cout << setw(8) << products[index].sales << endl;
    }
    cout << endl;
}

//*****************************************************************
// Definition of showTotals function. Accepts sales and id arrays *
// as arguments. The size of these arrays is passed into num.     *
// The function first calculates the total units (of all          *
// products) sold and the total sales. It then displays these     *
// amounts.                                                       *
//*****************************************************************

void showTotals(const Product products[], int num)
{
    int totalUnits = 0;
    double totalSales = 0.0;

    for (int index = 0; index < num; index++)
    {
        totalUnits += products[index].units;
        totalSales += products[index].sales;
    }
    cout << "Total units Sold:  " << totalUnits << endl;
    cout << "Total sales:      $" << totalSales << endl;
}

