/**
 * @file hw03.cpp
 * @author Shounak Ghosh
 * @brief //TODO
 * @date Feb 12 2023
 *
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Warrior {
private:
    class Weapon {
    private:
        int strength;
        string name;
    public:
        Weapon() {
            strength = 0;
            name = "";
        }

        Weapon(const string& weapon_name, int weapon_strength) {
            name = weapon_name;
            strength = weapon_strength;
        }

        const string& getName() const {
            return name;
        }

        int getStrength() const {
            return strength;
        }

        void setStrength(int new_strength) {
            strength = new_strength;
        }

        friend ostream& operator<<(ostream& os, const Weapon& weapon);
    };

    // private variables for the Warrior class
    string name;
    Weapon weapon;

public:
    Warrior(const string& warrior_name, const string& weapon_name, int weapon_strength) {
        name = warrior_name;
        weapon = Weapon(weapon_name, weapon_strength);
    }

    const string& getName() const {
        return name;
    }

    const Weapon& getWeapon() const {
        return weapon;
    }

    void adjustWeaponStrength(int new_strength) {
        weapon.setStrength(new_strength);
    }

    friend ostream& operator<<(ostream& os, const Warrior& warrior);

    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
        os << weapon.name << ", " << weapon.strength;
        return os;
    }

};

// TODO insert function prototypes
size_t get_warrior_index(const vector<Warrior>& warriors, const string& name);

void add_warrior(vector<Warrior>& warriors, const string& name, const string& weapon_name, int weapon_strength);

void do_battle(Warrior& warrior1, Warrior& warrior2);

void get_status(const vector<Warrior>& warriors);


/**
 * @brief
 *
 * @return int 0 on success
 */
int main() {
    vector<Warrior> warriors;

    ifstream infile("warriors.txt");
    if (!infile) {
        cerr << "Could not open file" << endl;
        exit(1);
    }

    string command;

    // read in the command at the beginning of each loop iteration
    // based on the command, read in more as needed
    while (infile >> command) {
        if (command == "Warrior") {
            string name;
            string weapon_name;
            int weapon_strength;
            infile >> name >> weapon_name >> weapon_strength;
            add_warrior(warriors, name, weapon_name, weapon_strength);
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

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name;
    return os;
}

size_t get_warrior_index(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == name) {
            return i;
        }
    }
    return warriors.size();
}

void add_warrior(vector<Warrior>& warriors, const string& name, const string& weapon_name, int weapon_strength) {
    warriors.push_back(Warrior(name, weapon_name, weapon_strength));
}

void do_battle(Warrior& warrior1, Warrior& warrior2) {

    // TODO implement this function
    cout << warrior1.getName() << " battles " << warrior2.getName() << endl;

    // a warrior cannot battle themselves
    if (warrior1.getName() == warrior2.getName()) {
        cerr << "Error: warrior cannot battle themselves" << endl;

    }
    // both warriors are dead
    else if (warrior1.getWeapon().getStrength() == 0 && warrior2.getWeapon().getStrength() == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    // warrior1 is dead
    else if (warrior1.getWeapon().getStrength() == 0) {
        cout << "He's dead, " << warrior2.getName() << endl;
    }
    // warrior2 is dead
    else if (warrior2.getWeapon().getStrength() == 0) {
        cout << "He's dead, " << warrior1.getName() << endl;
    }
    // warrior1 is stronger than warrior2
    else if (warrior1.getWeapon().getStrength() > warrior2.getWeapon().getStrength()) {
        cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
        warrior1.adjustWeaponStrength(warrior1.getWeapon().getStrength() - warrior2.getWeapon().getStrength());
        warrior2.adjustWeaponStrength(0);
    }
    // warrior2 is stronger than warrior1
    else if (warrior2.getWeapon().getStrength() > warrior1.getWeapon().getStrength()) {
        cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
        warrior2.adjustWeaponStrength(warrior2.getWeapon().getStrength() - warrior1.getWeapon().getStrength());
        warrior1.adjustWeaponStrength(0);
    }
    // warrior1 and warrior2 have the same strength
    else {
        cout << "Mutual Annihilation: " << warrior1.getName() << " and " << warrior2.getName() << " die at each other's hands" << endl;
        warrior1.adjustWeaponStrength(0);
        warrior2.adjustWeaponStrength(0);
    }

}

void get_status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); i++) {
        cout << "Warrior: " << warriors[i] << ", weapon: " << warriors[i].getWeapon() << endl;
    }
}