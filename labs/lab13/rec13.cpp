// rec13_start.cpp
// Name: Shounak Ghosh
// Date: 04/28/23

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// task 9
void printList(const list<int>& l) {
    for (list<int>::const_iterator i = l.begin(); i != l.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

// task 10
void printListRanged(const list<int>& l) {
    for (int i : l) {
        cout << i << " ";
    }
    cout << endl;
}

// task 11
void printListAuto(const list<int>& l) {
    for (auto i = l.begin(); i != l.end(); i++) {
        cout << *i << " ";
        i++;
    }
    cout << endl;
}

// task 12
list<int>::const_iterator find(const list<int>& l, int value) {
    for (list<int>::const_iterator i = l.begin(); i != l.end(); i++) {
        if (*i == value) {
            return i;
        }
    }
    return l.end();
}

// task 13
auto findAuto(const list<int>& l, int value) {
    for (auto i = l.begin(); i != l.end(); i++) {
        if (*i == value) {
            return i;
        }
    }
    return l.end();
}

// task 14
auto findGeneric(const list<int>& l, int value) {
    auto res = find(l.begin(), l.end(), value);
    if (res == l.end()) {
        return l.end();
    }
    return res;
}

// task 15
bool isEven(int n) {
    return n % 2 == 0;
}

void findEven(const list<int>& l) {
    auto res = find_if(l.begin(), l.end(), isEven);
    if (res == l.end()) {
        cout << "No even numbers found" << endl;
    }
    else {
        cout << *res << endl;
    }
}

// task 16
class checkEven {
public:
    bool operator()(int n) {
        return n % 2 == 0;
    }
};

//task 19
list<int>::const_iterator ourFind(const list<int>::const_iterator& start, const list<int>::const_iterator& stop, int value) {
    for (list<int>::const_iterator i = start; i != stop; i++) {
        if (*i == value) {
            return i;
        }
    }
    return stop;
}

//task 20
template <typename T, typename U>
T ourFind(const T& start, const T& stop, const U& value) {
    for (T i = start; i != stop; i++) {
        if (*i == value) {
            return i;
        }
    }
    return stop;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v = { 6, 5, 4, 3, 2, 1 };
    for (int i : v) {
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list <int> l(v.begin(), v.end());
    for (int i : l) {
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
    for (int i : l) {
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < v.size(); i += 2) {
        cout << v[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    for (size_t i = 0; i < l.size(); i += 2) {
        // cout << l[i] << " "; // list does not support operator[]; innefficient
    }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = v.begin(); i != v.end(); i += 2) {
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
        cout << *i << " ";
        i++;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l.sort();
    for (int i : l) {
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(l);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRanged(l);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printListAuto(l);
    cout << "=======\n";


    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *find(l, 3) << endl;
    cout << *find(l, 7) << endl; // returns l.end()--; end() is one past the last element
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *findAuto(l, 3) << endl;
    cout << *findAuto(l, 7) << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *findGeneric(l, 3) << endl;
    cout << *findGeneric(l, 7) << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    findEven(l);
    list<int> lnoeven = { 1, 3, 5, 7 };
    findEven(lnoeven);
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    // ternary operator used
    auto it = find_if(l.begin(), l.end(), checkEven());
    it == l.end() ? cout << "No even numbers found\n" : cout << *it << endl;
    it = find_if(lnoeven.begin(), lnoeven.end(), checkEven());
    it == lnoeven.end() ? cout << "No even numbers found\n" : cout << *it << endl;
    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    it = find_if(l.begin(), l.end(), [](int i) {return i % 2 == 0; });
    it == l.end() ? cout << "No even numbers found\n" : cout << *it << endl;
    it = find_if(lnoeven.begin(), lnoeven.end(), [](int i) {return i % 2 == 0; });
    it == lnoeven.end() ? cout << "No even numbers found\n" : cout << *it << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[l.size()];
    copy(l.begin(), l.end(), arr);
    for (int i = 0; i < l.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << *find(arr, arr + l.size(), 3) << endl;
    cout << *find(arr, arr + l.size(), 7) << endl;
    cout << *find_if(arr, arr + l.size(), checkEven()) << endl;
    cout << *find_if(arr, arr + l.size(), [](int i) {return i % 2 == 0; }) << endl;
    delete[] arr;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(l.begin(),l.end(), 3) << endl;
    cout << *ourFind(l.begin(),l.end(), 7) << endl;

    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(v.begin(),v.end(), 3) << endl; 
    cout << *ourFind(v.begin(),v.end(), 7) << endl;
    cout << *ourFind(l.begin(),l.end(), 3) << endl;
    cout << *ourFind(l.begin(),l.end(), 7) << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream fin("pooh-nopunc.txt");
    vector<string> words;
    string word;
    while (fin >> word) {
        if (find(words.begin(), words.end(), word) == words.end())
            words.push_back(word);
    }
    fin.close();
    for (string s : words) {
        cout << s << " ";
    }
    cout << "\nNumber of distinct words: " << words.size() << endl;
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> words2;
    fin.open("pooh-nopunc.txt");
    while (fin >> word) {
        words2.insert(word);
    }
    fin.close();
    for (string s : words2) {
        cout << s << " ";
    }
    cout << "\nNumber of distinct words: " << words2.size() << endl;
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string,vector<int>> wordMap;
    fin.open("pooh-nopunc.txt");
    int pos = 0;
    while (fin >> word) {
        wordMap[word].push_back(pos++);
    }
    fin.close();
    for (auto p : wordMap) {
        cout << p.first << ": ";
        for (int i : p.second) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "=======\n";
}
