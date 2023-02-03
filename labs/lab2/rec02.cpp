/*
   Author: Shounak Ghosh
   rec02.cpp
   spring 2023
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct hydrocarbon {
    vector<string> names;
    int carbon;
    int hydrogen;
};

void get_filestream(ifstream& file); // function prototype

void print_hydrocarbon(const hydrocarbon& h); // function prototype

void print_vector(
    const vector<hydrocarbon>& hydrocarbons); // function prototype

void fill_vector(ifstream& file,
    vector<hydrocarbon>& hydrocarbons); // function prototype

size_t find_hydrocarbon(const vector<hydrocarbon>& hydrocarbons,
    int carbon, int hydrogen); // function prototype

void sort_vector(vector<hydrocarbon>& hydrocarbons); // function prototype

/**
 * @brief main function
 *
 * @return int 0 on success
 */
int main() {
    vector<hydrocarbon> hydrocarbons;
    ifstream file;

    get_filestream(file);

    fill_vector(file, hydrocarbons);

    sort_vector(hydrocarbons);

    print_vector(hydrocarbons);
}

/**
 * @brief Get the filestream object
 *
 * @param file the filestream object
 */
void get_filestream(ifstream& file) {
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;
    file.open(filename);

    while (!file) {
        cout << "File not found" << endl;
        file.clear();
        cout << "Enter a filename: ";
        cin >> filename;
        file.open(filename);
    }
}

/**
 * @brief find the index of a hydrocarbon in the vector
 *
 * @param hydrocarbons the vector of hydrocarbons
 * @param carbon the number of carbons
 * @param hydrogen the number of hydrogens
 * @return size_t the index of the hydrocarbon in the vector, 
 *         or the size of the vector if not found
 */
size_t find_hydrocarbon(const vector<hydrocarbon>& hydrocarbons, int carbon,
    int hydrogen) {
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        if (hydrocarbons[i].carbon == carbon &&
            hydrocarbons[i].hydrogen == hydrogen) {
            return i;
        }
    }
    return hydrocarbons.size(); // size_t is an unsigned int, can't return -1
}

/**
 * @brief fill the vector with hydrocarbons
 *
 * @param file the filestream object
 * @param hydrocarbons the vector of hydrocarbons
 */
void fill_vector(ifstream& file, vector<hydrocarbon>& hydrocarbons) {
    string name;
    char temp;
    int carbon;
    int hydrogen;

    // "input chaining"; the while repeatedly reads these variables in this order
    while (file >> name >> temp >> carbon >> temp >>
        hydrogen) { // temp stores the 'C' and 'H'
        size_t index = find_hydrocarbon(hydrocarbons, carbon, hydrogen);
        if (index == hydrocarbons.size()) {
            hydrocarbon h;
            h.names.push_back(name);
            h.carbon = carbon;
            h.hydrogen = hydrogen;
            hydrocarbons.push_back(h);
        }
        else {
            hydrocarbons[index].names.push_back(name);
        }
    }
    file.close();
}

/**
 * @brief print a hydrocarbon
 *
 * @param h the hydrocarbon
 */
void print_hydrocarbon(const hydrocarbon& h) {
    cout << "C" << h.carbon << "H" << h.hydrogen << " ";
    for (const string& name : h.names) {
        cout << name << " ";
    }
    cout << endl;
}

/**
 * @brief print the vector of hydrocarbons
 *
 * @param hydrocarbons the vector of hydrocarbons
 */
void print_vector(const vector<hydrocarbon>& hydrocarbons) {
    for (const hydrocarbon& h : hydrocarbons) {
        print_hydrocarbon(h);
    }
}

/**
 * @brief sort the vector of hydrocarbons
 *
 * @param hydrocarbons the vector of hydrocarbons
 */
void sort_vector(vector<hydrocarbon>& hydrocarbons) {
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        for (size_t j = 0; j < hydrocarbons.size() - 1; j++) {
            if (hydrocarbons[j].carbon > hydrocarbons[j + 1].carbon) {
                hydrocarbon temp = hydrocarbons[j];
                hydrocarbons[j] = hydrocarbons[j + 1];
                hydrocarbons[j + 1] = temp;
            }
            else if (hydrocarbons[j].carbon == hydrocarbons[j + 1].carbon) {
                if (hydrocarbons[j].hydrogen > hydrocarbons[j + 1].hydrogen) {
                    hydrocarbon temp = hydrocarbons[j];
                    hydrocarbons[j] = hydrocarbons[j + 1];
                    hydrocarbons[j + 1] = temp;
                }
            }
        }
    }
}
