/*
 * FJ Tria (@fjstria)
 * CSE101/pa8/WordFrequency.cpp
 */

#include "Dictionary.h"
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line, key;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary D;

    // check for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    // open and check files
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    // read lines
    while (getline(in, line)) {
        len = line.length();

        // get first key
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));

        // key found
        while (key != "") {
            // convert key to lower case:
            // https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
            transform(key.begin(), key.end(), key.begin(), ::tolower);

            // add to dictionary
            if (D.contains(key)) {
                D.getValue(key)++;
            }
            else {
                D.setValue(key, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    // output dictionary
    out << D << endl;
    
    // clean up, close files
    D.clear();
    in.close();
    out.close();

    return EXIT_SUCCESS;
}