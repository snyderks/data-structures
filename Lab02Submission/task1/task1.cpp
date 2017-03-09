// Lab 2 Task 1
// Data Structures CS2028C
// Kristian Snyder

#include <fstream>
#include <iostream>
using namespace std;

int main() {
    cout << "Enter the name of a file to read: ";

    string fname = "";
    cin >> fname;

    // Create a stream
    fstream file;
    file.open(fname, ios::in);

    if (!file.is_open()) {
        cout << "File doesn't exist.";
    } else {
        for (int i = 0; i < 10; i++) {
            string line;
            getline(file, line);
            if (file.eof() && line.length() == 0) {
                break;
            }
            cout << line << endl;
        }
    }
    file.close();
    return 0;
}