/*
  hw02.cpp
  Author: Shounak Ghosh
  Simulates a game of medivival times, as per the problem statement
  Feb 9 2023
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

    // attempt to read the file, exit if error
    ifstream infile("warriors.txt");
    if (!infile) {
        cerr << "Error: could not open file" << endl;
        exit(1);
    }

    string command;

    // read in the command at the beginning of each loop iteration
    // based on the command, read in more as needed
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
            // one or both of the warriors do not exist
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

/**
 * @brief Given the name of the warrior,
 *        returns the index of the warrior in the vector
 *
 * @param warriors the vector of warriors
 * @param name the name of the warrior
 * @return size_t the index of the warrior in the vector,
 *               or the size of the vector if the warrior does not exist
 */
size_t get_warrior_index(const vector<warrior>& warriors, const string& name) {
    for (int i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

/**
 * @brief Adds a warrior to the vector of warriors
 *
 * @param warriors the vector of warriors
 * @param name the name of the warrior to be added,
 *             outputs an error if the warrior already exists
 * @param strength the strength of the warrior to be added
 */
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

/**
 * @brief Simulates a battle between two warriors
 *
 * @param warrior1 the first warrior
 * @param warrior2 the second warrior
 */
void do_battle(warrior& warrior1, warrior& warrior2) {
    // initial print announcing the battle
    cout << warrior1.name << " battles " << warrior2.name << endl;
    // both warriors are dead
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    // one warrior is dead
    else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    }
    // both warriors are alive
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
    // both warriors have the same strength, both die
    else {
        warrior1.strength = 0;
        warrior2.strength = 0;
        cout << "Mutual Annihilation: " << warrior1.name << " and " <<
            warrior2.name << " die at each other's hands" << endl;
    }
}

/**
 * @brief Get the status of all the warriors
 *
 * @param warriors the vector of warriors
 */
void get_status(const vector<warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (int i = 0; i < warriors.size(); i++) {
        cout << "Warrior: " << warriors[i].name <<
            ", strength: " << warriors[i].strength << endl;
    }
}