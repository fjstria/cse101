/*
 * FJ Tria (@fjstria)
 * CSE101/pa7/Dictionary.cpp
 */

#include "Dictionary.h"
#include <stdexcept>

using namespace std;

// Helper Functions -----
void Dictionary::inOrderString(string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(string& s, Node* R) const {
    if (R != nil) {
        s.append(R->key);
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        R->parent = nullptr;
        R->left = nullptr;
        R->right = nullptr;
        delete R;
        num_pairs--;
    }
}

void Dictionary::transplant(Node* U, Node* V) {
    if (U->parent == nil) {
        root = V;
    }
    else if (U == U->parent->left) {
        U->parent->left = V;
    }
    else {
        U->parent->right = V;
    }
    if (V != nil) {
        V->parent = U->parent;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil) {
        return nil;
    }
    else if (R->key == k) {
        return R;
    }
    else if (k < R->key) {
        return search(R->left, k);
    }
    else {
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        throw logic_error("Dictionary: findMin(): subtree given is rooted at nil");
    }
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {
        throw logic_error("Dictionary: findMax(): subtree given is rooted at nil");
    }
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node* Y = N->parent;
    while (Y != nil && N == Y->right) {
        N = Y;
        Y = Y->parent;
    }
    return Y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node* Y = N->parent;
    while (Y != nil && N == Y->left) {
        N = Y;
        Y = Y->parent;
    }
    return Y;
}


// Constructors & Destructor -----
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
    nil = new Node("\0", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("\0", -1);
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}


// Access Functions -----
int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    if (search(root, k) == nil) {
        return false;
    }
    return true;
}

valType& Dictionary::getValue(keyType k) const {
    Node *N = search(root, k);
    if (N == nil) {
        throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    if (current == nil || current == nullptr) {
        return false;
    }
    return true;
}

keyType Dictionary::currentKey() const {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation Procedures -----
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* X = root;
    Node* Y = nil;
    Node* Z = new Node(k, v);
    Z->left = nil;
    Z->right = nil;

    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        }
        else {
            X = X->right;
        }
    }
    Z->parent = Y;
    if (Y == nil) {
        root = Z;
        num_pairs++;
    }
    else if (k < Y->key) {
        Y->left = Z;
        num_pairs++;
    }
    else if (k > Y->key) {
        Y->right = Z;
        num_pairs++;
    }
    else {
        Y->val = v;
        delete Z;
    }    
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
    if (N->left == nil) {
        transplant(N, N->right);
        delete N;
    }
    else if (N->right == nil) {
        transplant(N, N->left);
        delete N;
    }
    else {
        Node* Y = findMin(N->right);
        if (Y->parent != N) {
            transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        delete N;
    }
    num_pairs--;
}

void Dictionary::begin() {
    if (num_pairs > 0) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (num_pairs > 0) {
        current = findMax(root);
    }
}

void Dictionary::next() {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: next(): current not defined");
    }
    if (findNext(current) != nil) {
        Node* N = findNext(current);
        current = N;
    }
    else {
        current = nil;
    }
}

void Dictionary::prev() {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: prev(): current not defined");
    }
    if (findPrev(current) != nil) {
        Node* N = findPrev(current);
        current = N;
    }
    else {
        current = nil;
    }
}


// Other Functions -----
std::string Dictionary::to_string() const {
    string S = "";
    this->inOrderString(S, this->root);
    return S;
}

std::string Dictionary::pre_string() const {
    string S = "";
    this->preOrderString(S, this->root);
    return S;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (this->num_pairs != D.num_pairs) {
        return false;
    }
    string A, B;
    A = this->to_string();
    B = D.to_string();
    if (A == B) {
        return true;
    }
    return false;
}


// Overloaded Operators -----
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        swap(nil, temp.nil);
        swap(root, temp.root);
        swap(current, temp.current);
        swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
