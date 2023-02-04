/*
  hw02.cpp
  Author: Shounak Ghosh
  Simulate a game of medivival times, as per the problem statement
  Feb 7 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct warrior {
    string name;
    int strength;
};

// function prototypes
size_t get_warrior_index(const vector<warrior>& warriors, const string& name);

void add_warrior(vector<warrior>& warriors, const string& name, int strength);

void do_battle(warrior& warrior1, warrior& warrior2);

void get_status(const vector<warrior>& warriors);

/**
 * @brief Simulates a game of medivival times
 *
 * @return int 0 on success
 */
int main() {
    // stores all the warriors passed in via the file
    vector<warrior> warriors;

    // attemp to read the file, exit if error
    ifstream infile("warriors.txt");
    if (!infile) {
        cerr << "Error: could not open file" << endl;
        exit(1);
    }

    string command;

    while (infile >> command) {
        if (command == "Warrior") {
            string name;
            int strength;
            infile >> name >> strength;
            add_warrior(warriors, name, strength);
        }
        else if (command == "Status") {
            get_status(warriors);
        }
        else if (command == "Battle") {
            string name1, name2;
            infile >> name1 >> name2;
            size_t index1 = get_warrior_index(warriors, name1);
            size_t index2 = get_warrior_index(warriors, name2);
            if (index1 == warriors.size() || index2 == warriors.size()) {
                cerr << "Error: warrior does not exist" << endl;
            }
            else {
                do_battle(warriors[index1], warriors[index2]);
            }
        }
        else {
            cerr << "Error: invalid command" << endl;
        }
    }

    return 0;
}

size_t get_warrior_index(const vector<warrior>& warriors, const string& name) {
    for (int i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

void add_warrior(vector<warrior>& warriors, const string& name, int strength) {
    if (get_warrior_index(warriors, name) != warriors.size()) {
        cerr << "Error: warrior already exists" << endl;
    }
    else {
        warrior new_warrior;
        new_warrior.name = name;
        new_warrior.strength = strength;
        warriors.push_back(new_warrior);
    }
}

void do_battle(warrior& warrior1, warrior& warrior2) {
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    }
    else if (warrior1.strength > warrior2.strength) {
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
        cout << warrior1.name << " defeats " << warrior2.name << endl;
    }
    else if (warrior2.strength > warrior1.strength) {
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
        cout << warrior2.name << " defeats " << warrior1.name << endl;
    }
    else {
        warrior1.strength = 0;
        warrior2.strength = 0;
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
    }
}

void get_status(const vector<warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (int i = 0; i < warriors.size(); i++) {
        cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
}