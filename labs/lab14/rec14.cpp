/*
  rec14.cpp
  Author: Shounak Ghosh
  Date: 5/05/2023
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
#include <stdexcept> 
using namespace std;


// Node type for the linked list
struct Node {
    int data;
    Node* next;
};

// Node type for the binary tree
struct TNode {
    int data;
    TNode* left, * right;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function: 
Node* listSum(Node* l1, Node* l2) {
    if (!l1 && !l2) // reached end of both lists
        return nullptr;
    else if (l1 && !l2) { // l1 still has values; make copies
        Node* temp = new Node;
        temp->data = l1->data;
        temp->next = listSum(l1->next, l2);
        return temp;
    }
    else if (!l1 && l2) { // l2 still has values; make copies
        Node* temp = new Node;
        temp->data = l2->data;
        temp->next = listSum(l1, l2->next);
        return temp;
    }
    else { // add values
        Node* temp = new Node;
        temp->data = l1->data + l2->data;
        temp->next = listSum(l1->next, l2->next);
        return temp;
    }
}

//   Task 2 function:
int treeMax(TNode* root) {
    if (!root) throw invalid_argument("Empty tree");
    if (!root->left && !root->right) // reached end of tree
        return root->data;
    else if (!root->left) // no left subtree
        return max(root->data, treeMax(root->right));
    else if (!root->right) // no right subtree
        return max(root->data, treeMax(root->left));
    else // both subtrees exist
        return max(root->data, max(treeMax(root->left), treeMax(root->right)));
}

//   Task 3 function:
bool palindrome(const char arr[], int size) {
    if (size <= 1) // reached end of array
        return true;
    if (arr[0] != arr[size - 1]) // check if first and last elements are equal
        return false;
    return palindrome(arr + 1, size - 2);
}

//   Task 4 function:
bool parity(int n) {
    if (n == 0) // reached end of binary representation
        return true;
    if (n % 2 == 1) // check if last digit is 1
        return !parity(n / 2);
    return parity(n / 2);
}

//   Task 5 function:
int towers(int n, char start, char spare, char end) {
    if (n == 1) // reached end of tower
        return 1;
    // move n-1 disks from start to spare
    // move 1 disk from start to end
    // move n-1 disks from spare to end
    return towers(n - 1, start, end, spare) + towers(1, start, spare, end) + towers(n - 1, spare, start, end);
}


void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}



int main() {
    // We have provided some test code to save you time. Certainly feel
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({ 2, 7, 1, 8 });
    cout << "List (l1): ";
    listPrint(l1);

    Node* l2 = listBuild({ 9, 1, 4, 1 });
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({ 3, 1, 4, 1, 5, 9 });
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);



    // Task 2:
    TNode a{1}, b{2}, c{4}, d{8, &a, &b}, e{16, &c}, f{32, &d, &e};
    cout << treeMax(&f) << endl;

    // added exception handling for empty tree
    try {
    cout << treeMax(nullptr) << endl;
    }
    catch (const exception& e) {
        cerr << "Invalid argument: " << e.what() << endl;
    }

    // Task 3:
    cout << "\n==============\n"
     << "#3) Testing palindrome\n";
    cout << boolalpha
     << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
     << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
     << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
     << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;

    // Task 4:
    cout << "\n==============\n" 
    << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }



    // Task 5:
    cout << "\n==============\n"
     << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
    cout << "towers(" << i << ", 'a', 'b', 'c'): " 
         << towers(i, 'a', 'b', 'c') << endl;
    }

    cout << "\n==============\n";
    // Task 6:
    for (int i = 0; i <= 10; ++i) {
        cout << "mystery(" << i << "): ";
        mystery(i);
        cout << endl;
    }


}


//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        result = new Node{ vals[index - 1], result };
    }
    return result;
}
