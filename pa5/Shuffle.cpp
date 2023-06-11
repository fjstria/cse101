/*
 * FJ Tria (@fjstria)
 * CSE101/pa5/Shuffle.cpp
 */

#include "List.h"
#include <stdexcept>
#include <iomanip>

using namespace std;

// Thanks to tutor Ishika for helping debug!

void shuffle(List& D);

int main(int argc, char* argv[]) {
    int n, count, max;
    List Deck, Temp;

    //  check for correct number of arguments
    if (argc != 2) {
        throw invalid_argument("Incorrect number of arguments. Usage: Shuffle <int>");
    }

    // get input for max number of cards
    max = stoi(argv[1]);
    if (max <= 0) {
        throw invalid_argument("Argument must be a positive integer.");
    }

    // print header
    cout << "deck size\tshuffle count" << endl;
    string div(30, '-');
    cout << div << endl;    

    // iterate through possible deck sizes
    for (n = 1; n <= max; n++) {
        count = 0;
        Deck.moveBack();
        Deck.insertBefore(n - 1);    
        
        // shuffle once to start
        Temp = Deck;
        shuffle(Deck);
        count++;

        // do shuffles until deck matches original
        while (!(Temp == Deck)) {
            shuffle(Deck);
            count++;
        }

        // output num cards and shuffle count
        cout << " " << left << setw(16) << n << count << endl;
    }    
}

void shuffle(List& D) {  
    List A, B;
    int x, y;
    int n = D.length();

    // split D into halves
    D.moveFront();
    while (D.position() < n / 2) {
        x = D.moveNext();
        A.insertBefore(x);
    }   
    while (D.position() < n) {
        y = D.moveNext();
        B.insertBefore(y);
    }

    // reset D and shuffle A and B back into D
    D.clear();
    A.moveFront();
    B.moveFront();
    while (B.position() < B.length()) {
        x = B.moveNext();
        D.insertBefore(x);
        if (A.position() < A.length()) {
            y = A.moveNext();
            D.insertBefore(y);
        }
    }
}
