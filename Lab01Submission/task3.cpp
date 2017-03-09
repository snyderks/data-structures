// Kristian Snyder - Lab 01
// This program produces a sales report for DLC, Inc.
#include <iostream>
#include <iomanip>
using namespace std;

struct Product {
    int id;
    int units;
    double price;
    double sales;
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
    Product products[NUM_PRODS];
    // Array with product ID numbers
    int id[NUM_PRODS] = {914, 915, 916, 917, 918, 919, 920,
                         921, 922};

    // Array with number of units sold for each product
    int units[NUM_PRODS] = {842, 416, 127, 514, 437, 269, 97,
                            492, 212};

    // Array with product prices
    double prices[NUM_PRODS] = {12.95, 14.95, 18.95, 16.95, 21.95,
                                31.95, 14.95, 14.95, 16.95};

    // Array to hold the computed sales amounts
    double sales[NUM_PRODS];

    for (int i = 0; i < NUM_PRODS; i++) {
        products[i] = { id[i], units[i], prices[i] };
    }

    // Calculate each product's sales.
    calcSales(products, NUM_PRODS);

    // Sort the elements in the sales array in descending
    // order and shuffle the ID numbers in the id array to
    // keep them in parallel.
    dualSort(products, NUM_PRODS);

    // Set the numeric output formatting.
    cout << setprecision(2) << fixed << showpoint;

    // Display the products and sales amounts.
    showOrder(products, NUM_PRODS);

    // Display total units sold and total sales.
    showTotals(products, NUM_PRODS);
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
        cout << products[index].id << "\t\t$";
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
