/*
 * FJ Tria (@fjstria)
 * CSE101/pa6/BigInteger.cpp
 */

#include "BigInteger.h"
#include <stdexcept>
#include <ctype.h>

#define BASE 1000000000
#define POWER 9

using namespace std;

// Constructors & Destructors -----
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(string s) {
    if (s.length() == 0) {
        throw invalid_argument("BigInteger: Constructor: empty string");
    }
    if (s[0] == '+') {
        signum = 1;
        s.substr(1, s.length());
    }
    else if (s[0] == '-') {
        signum = -1;
        s.substr(1, s.length());
    }
    else {
        signum = 1;
    }

    for (char const &c: s) {
        if (!isdigit(c)) {
            throw invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    bool ex = false;
    for (int i = s.length() - POWER; ; i -= POWER) {
        if (i < 0) {
            digits.insertAfter(stol(s.substr(0, i + POWER)));
            ex = true;
        }
        else if (i == 0) {
            digits.insertAfter(stol(s.substr(i, POWER)));
            ex = true;
        }
        else {
            digits.insertAfter(stol(s.substr(i, POWER)));
        }
        if (ex) {
            break;
        }
    }
}

BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}


// Access Functions -----
int BigInteger::sign() const{
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const{
    // simple case, compare signs
    if (this->signum > N.signum) {
        return 1;
    }
    else if (this->signum < N.signum) {
        return -1;
    }
    else if (this->signum == 0 && N.signum == 0) {
        return 0;
    }
    
    // same sign, do checks
    List A = this->digits;
    List B = N.digits;

    // both positive
    if (this->signum == 1 && N.signum == 1) {
        // longer list is larger
        if (A.length() != B.length()) {
            if (A.length() > B.length()) {                
                return 1;
            }
            else {
                return -1;
            }
        }    
        A.moveFront();
        B.moveFront();
        // same length, compare digits
        for ( ; A.position() < A.length(); A.moveNext(), B.moveNext()) {
            if (A.peekNext() > B.peekNext()) {
                return 1;
            }
            else if (A.peekNext() < B.peekNext()) {
                return -1;
            }
        }
        return 0;
    }    
    // both negative
    else if (this->signum == -1 && N.signum == -1) {
        // shorter list is larger
        if (A.length() != B.length()) {
            if (A.length() > B.length()) {
                return -1;
            }
            else {
                return 1;
            }
        }       
        A.moveFront();
        B.moveFront();
        // compare digits
        for ( ; A.position() < A.length(); A.moveNext(), B.moveNext()) {
            if (A.peekNext() > B.peekNext()) {
                return -1;
            }
            else if (A.peekNext() < B.peekNext()) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}


// Manipulation Procedures -----
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum *= -1;
}

// Helper Functions -----
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(-1 * L.peekNext());
        L.moveNext();
    }
}

void sumList(List& S, List A, List B, int sign) {
    S.clear();
    B.moveFront();
    while (B.position() < B.length()) {
        B.setAfter(sign * B.peekNext());
        B.moveNext();
    }
    
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }
    while (A.position() > 0) {
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    while(B.position() > 0) {
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }

    S.moveFront();
    while (S.front() == 0 && S.length() > 1) {
        S.eraseAfter();
    }
}

int normalizeList(List& L) {
    if (L.front() == 0) {
        return 0;
    }

    int sign = 1;
    if (L.front() < 0) {
        negateList(L);
        sign = -1;
    }

    L.moveBack();
    ListElement E = 0;
    int carry = 0;
    while (L.position() > 0) {
        E = L.peekPrev();
        if (E < 0) {
            E += BASE + carry;
            L.setBefore(E);
            carry = -1;
        }
        else {
            E += carry;
            carry = 0;
            if (E >= BASE) {
                carry = E / BASE;
                E = E % BASE;
            }
            L.setBefore(E);
        }
        L.movePrev();
    }
    if (carry != 0) {
        L.moveFront();
        L.insertAfter(carry);
    }
    return sign;
}

void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

void scalarMultList(List& L, ListElement E) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * E);
        L.moveNext();
    }
}

// BigInteger Arithmetic Operations -----
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger S;
    List sum;
    List A = this->digits;
    List B = N.digits;
    
    if (this->signum < 0) {
        negateList(A);
    }
    if (N.signum < 0) {
        negateList(B);
    }
    sumList(sum, A, B, 1);
    S.signum = normalizeList(sum);
    S.digits = sum;

    return S;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger D;
    BigInteger cN = N;

    negateList(cN.digits);
    D = this->add(cN);
    
    return D;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger P;
    if (this->signum == 0 || N.signum == 0){
        return P;
    }
    List product;
    product.insertAfter(0);
    List L;
    List cN = N.digits;

    cN.moveBack();
    int shift = 0;
    while (cN.position() > 0) {
        L = this->digits;
        scalarMultList(L, cN.peekPrev());
        shiftList(L, shift);
        
        List productCopy = product;
        sumList(product, productCopy, L, 1);
        normalizeList(product);

        cN.movePrev();
        shift++;
    }

    P.digits = product;
    if (this->signum == N.signum) {
        P.signum = 1;
    }
    else {
        P.signum = -1;
    }

    return P;
}


// Other Functions -----
std::string BigInteger::to_string() {
    string out = "";
    if (this->signum == 0) {
        return "0";
    }
    else if (signum == -1) {
        out += "-";
    }

    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }

    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        string A = std::to_string(digits.peekNext());
        string B = "";
        while ((int)(B.length() + A.length()) < POWER && digits.position() != 0) {
            B += '0';
        }
        out += (B + A);
    }

    return out;
}


// Overriden Operators -----
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.BigInteger::to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) <= 0) {
        return true;
    }
    return false;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    if (A.compare(B) >= 0) {
        return true;
    }
    return false;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.BigInteger::add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.BigInteger::add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.BigInteger::sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.BigInteger::sub(B);
    return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.BigInteger::mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.BigInteger::mult(B);
    return A;
}
