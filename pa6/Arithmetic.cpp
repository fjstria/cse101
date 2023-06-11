/*
 * FJ Tria (@fjstria)
 * CSE101/pa6/Arithmetic.cpp
 */

#include "BigInteger.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    // check for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    // open files for read and write
    ifstream in;
    ofstream out;

    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read in strings for big int
    string sA, sB;
    in >> sA;
    in >> sB;

    // make big int objects
    BigInteger A = BigInteger(sA);
    BigInteger B = BigInteger(sB);
    BigInteger two("2");
    BigInteger three("3");
    BigInteger nine("9");
    BigInteger sixteen("16");

    // print out requested quantities
    
    // A
    out << (A) << endl << endl;
    
    // B
    out << (B) << endl << endl;
    
    // A + B
    out << (A + B) << endl << endl;
    
    // A - B
    out << (A - B) << endl << endl;
    
    // A - A
    out << (A - A) << endl << endl;
    
    // 3A - 2B
    out << ((three * A) - (two * B)) << endl << endl;
    
    // AB
    out << (A * B) << endl << endl;    
    
    // A^2
    out << (A * A) << endl << endl;
    
    // B^2
    out << (B * B) << endl << endl;
    
    // 9A^4 + 16B^5
    out << ((nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B))) << endl << endl;

    // close files
    in.close();
    out.close();
    return 0;
}
