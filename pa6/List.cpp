/*
 * FJ Tria (@fjstria)
 * CSE101/pa6/List.cpp
 */

#include "List.h"
#include <stdexcept>

using namespace std;

// Node Constructor -----
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// List Constructor & Destructor -----
List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) { 
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access Functions -----
int List::length() const{
    return num_elements;
}

ListElement List::front() const{
    if (num_elements == 0) {
        throw length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

ListElement List::back() const{
    if (num_elements == 0) {
        throw length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

int List::position() const{
    if (pos_cursor < 0 || pos_cursor > num_elements) {
        throw range_error("List: position(): position underfined");
    }
    return pos_cursor;
}

ListElement List::peekNext() const{
    if (position() >= length()) {
        throw range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const{
    if (position() <= 0) {
        throw range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation Procedures -----
void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return;
}

void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext() {
    if (position() >= length()) {
        throw range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (position() <= 0) {
        throw range_error("List: movePrev(): cursor at front");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    if (position() < 0) {
        exit(EXIT_FAILURE);
    }
    if (afterCursor == nullptr || beforeCursor == nullptr) {
        exit(EXIT_FAILURE);
    }    
    Node *temp = new Node(x);

    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    temp->next = afterCursor;
    afterCursor->prev = temp;
    afterCursor = temp;

    num_elements++;
}

void List::insertBefore(ListElement x) {
    if (position() < 0) {
        exit(EXIT_FAILURE);
    }
    if (afterCursor == nullptr || beforeCursor == nullptr) {
        exit(EXIT_FAILURE);
    }
    Node *temp = new Node(x);

    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    temp->next = afterCursor;
    afterCursor->prev = temp;
    beforeCursor = temp;

    pos_cursor++;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw range_error("List: setAfter(): cursor at back");
    }
    afterCursor->next->data = x;
}

void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->prev->data=x;
}

void List::eraseAfter() {
    if (position() >= length()) {
        throw range_error("List: eraseAfter(): cursor at back");
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    N->next->prev = beforeCursor;
    afterCursor = N->next;
    delete N;
    num_elements--;
}

void List::eraseBefore() {
    if (position() <= 0) {
        throw range_error("List: eraseBefore(): cursor at front");
    }
    Node *N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete N;
    pos_cursor--;
    num_elements--;
}


// Other Functions -----
int List::findNext(ListElement x) {
    bool found = false;
    Node *N = afterCursor;
    while (!found && N != backDummy) {
        found = (N->data == x);
        if (!found) {
            N = N->next;
        }
        pos_cursor++;
    }
    afterCursor = N->next;
    beforeCursor = N;
    if (found) {
        return pos_cursor;
    }
    else {
        return -1;
    }
}

int List::findPrev(ListElement x) {
    bool found = false;
    do {
        if (x == movePrev()) {
            found = true;
            break;
        }
    } while (pos_cursor > 0);
    return (found ? pos_cursor : -1);
}

void List::cleanup() {
    int position = 0;
    Node *cursor = frontDummy->next;
    Node *current = nullptr;
    Node *n = nullptr;
    while (cursor != backDummy) {
        current = cursor;
        n = cursor->next;
        position++;
        while (n != backDummy) {
            if (cursor->data == n->data) {
                current->next = n->next;
                n->next->prev = current;
                delete n;
                n = current->next;
                num_elements--;
                if (position < pos_cursor) {
                    pos_cursor--;
                }
            }
            else {
                current = n;
                n = current->next;                
            }
        }
        cursor = cursor->next;
    }
}

List List::concat(const List& L) const {
    List newList;
    Node *N = this->frontDummy->next;
    Node *M = L.frontDummy->next;

    while (N != this->backDummy) {
        newList.insertAfter(N->data);
        N = N->next;
    }

    while (M != L.backDummy) {
        newList.insertAfter(M->data);
        M = M->next;
    }
    return newList;
}

std::string List::to_string() const {
    Node *N = nullptr;
    string s = "";
    for (N = frontDummy; N!= nullptr; N = N->next) {
        s += std::to_string(N->data) + " ";
    }
    return s;
}

bool List::equals(const List& R) const {
    bool eq = false;
    Node *N = nullptr;
    Node *M = nullptr;

    eq = (this->num_elements == R.num_elements);

    N = this->frontDummy;
    M = R.frontDummy;

    while (eq && N != nullptr) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----
std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.List::to_string();
}

bool operator==(const List& A, const List& B) {
    return A.List::equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
    
        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(num_elements, temp.num_elements);
        swap(beforeCursor, temp.beforeCursor);
        swap(afterCursor, temp.afterCursor);
        swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}
