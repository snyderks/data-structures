// Lab 2 Task 2
// Data Structures CS2028C
// Kristian Snyder

using namespace std;
#include <fstream>
#include <iostream>

int main() {
    cout << "Enter the name of a file to read: ";

    string fname = "";
    cin >> fname;

    cout << "Enter the name of a file to write to: ";

    string ofname = "";
    cin >> ofname;

    // Create a stream
    fstream file;
    file.open(fname, ios::in);

    ofstream outfile;
    outfile.open(ofname, ios::app);

    if (!file.is_open() || !outfile.is_open()) {
        cout << "File doesn't exist or an error occurred opening files.";
    } else {
        for (int i = 0; i < 10; i++) {
            string line;
            getline(file, line);
            if (file.eof() && line.length() == 0) {
                break;
            }
            outfile << line << endl;

        }
    }
    file.close();
    outfile.close();
    return 0;
}