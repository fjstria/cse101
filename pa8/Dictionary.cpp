/*
 * FJ Tria (@fjstria)
 * CSE101/pa8/Dictionary.cpp
 */

#include "Dictionary.h"
#include <stdexcept>

#define RED -1
#define BLACK -2

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
        delete R;
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
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
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

void Dictionary::LeftRotate(Node* N) {
    Node* Y = N->right;

    N->right = Y->left;
    if (Y->left != nil) {
        Y->left->parent = N;
    }

    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    }
    else if (N == N->parent->left) {
        N->parent->left = Y;
    }
    else {
        N->parent->right = Y;
    }

    Y->left = N;
    N->parent = Y;
}

void Dictionary::RightRotate(Node* N) {
    Node* Y = N->left;

    N->left = Y->right;
    if (Y->right != nil) {
        Y->right->parent = N;
    }

    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    }
    else if (N == N->parent->right) {
        N->parent->right = Y;
    }
    else {
        N->parent->left = Y;
    }

    Y->right = N;
    N->parent = Y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node* Y = N->parent->parent->right;
            // case 1
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                // case 2
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                // case 3
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else {
            Node* Y = N->parent->parent->left;
            // case 4
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                // case 5
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                // case 6
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            Node* W = N->parent->right;
            // case 1
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            // case 2
            if (W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                N = N->parent;
            }
            else {
                // case 3
                if (W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }
                // case 4
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else {
            Node* W = N->parent->left;
            // case 5
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }
            // case 6
            if (W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                N = N->parent;
            }
            else {
                // case 7
                if (W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }
                // case 8
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N) {
    Node* X;
    Node* Y = N;
    int save = Y->color;
    if (N->left == nil) {
        X = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        X = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        Y = findMin(N->right);
        save = Y->color;
        X = Y->right;
        if (Y->parent == N) {
            X->parent = Y;
        }
        else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if (save == BLACK) {
        RB_DeleteFixUp(X);
    }
    delete N;
}


// Constructors & Destructor -----
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

Dictionary::Dictionary() {
    nil = new Node("\0", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("\0", -1);
    nil->color = BLACK;
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
    Z->color = RED;

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
        return;
    }    
    RB_InsertFixUp(Z);
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
    RB_Delete(N);
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
        throw logic_error("Dictionary: next(): current undefined");
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
        throw logic_error("Dictionary: prev(): current undefined");
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
