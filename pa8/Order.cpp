/*
 * FJ Tria (@fjstria)
 * CSE101/pa8/Order.cpp
 */

#include "Dictionary.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    // check for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return EXIT_FAILURE;
    }

    // open files and check if it's readable
    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Could not open the file " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    ofstream outfile;
    outfile.open(argv[2], fstream::out);


    // read line by line
    Dictionary D;
    string k = "";
    int v = 1;
    while (getline(infile, k)) {
        D.setValue(k, v);
        v++;
    }

    outfile << D.to_string() << endl;
    outfile << D.pre_string() << endl;

    D.clear();

    infile.close();
    outfile.close();
    return EXIT_SUCCESS;
}
