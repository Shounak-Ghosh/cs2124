/**
 * @file hw05.cpp
 * @author Shounak Ghosh
 * @brief  Simulate a game of medival times, as per the problem statement
 * @date March 2 2023
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior {
public:
    Warrior(const string& name, int strength): name(name), strength(strength), employed(false) {}

    string getName() const {
        return name;
    }

    int getStrength() const {
        return strength;
    }

    void setStrength(int strength) {
        this->strength = strength;
    }

    bool isEmployed() const {
        return employed;
    }

    void setEmployed(bool employed) {
        this->employed = employed;
    }

    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    int strength;
    bool employed;
};

class Noble {
public:
    Noble(const string& name): name(name), alive(true) {}

    string getName() const {
        return name;
    }

    bool hire(Warrior& warrior) {
        if (!warrior.isEmployed()) {
            army.push_back(&warrior);
            warrior.setEmployed(true);
            return true;
        }
        else {
            cerr << "Warrior " << warrior.getName() << " is already employed" << endl;
            return false;
        }
    }

    bool fire(Warrior& warrior) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior) {
                army.erase(army.begin() + i); //TODO: check if this is allowed
                warrior.setEmployed(false);
                return true;
            }
        }
        cerr << "Warrior " << warrior.getName() << " is not employed by " << name << endl;
        return false;
    }

    double getArmyStrength() const {
        double strength = 0;
        for (Warrior* warrior : army) {
            strength += warrior->getStrength();
        }
        return strength;
    }

    void uponDeath() {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0);
        }

    }

    void battle(Noble& otherNoble) {
        cout << name << " battles " << otherNoble.name << endl;

        if (!alive && !otherNoble.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!alive) {
            cout << "He's dead, " << otherNoble.name << endl;
        }
        else if (!otherNoble.alive) {
            cout << "He's dead, " << name << endl;
        }
        else {
            double armyStrength = getArmyStrength();
            double otherArmyStrength = otherNoble.getArmyStrength();

            if (armyStrength == otherArmyStrength) {
                cout << "Mutual Annihilation: " << name << " and " << otherNoble.name << " die at each other's hands" << endl;
                uponDeath();
                otherNoble.uponDeath();
            }
            else if (armyStrength > otherArmyStrength) {
                cout << name << " defeats " << otherNoble.name << endl;
                double ratio = otherArmyStrength / armyStrength;
                for (size_t i = 0; i < army.size(); ++i) {
                    army[i]->setStrength(army[i]->getStrength() * (1 - ratio));
                }
                otherNoble.uponDeath();
            }
            else {
                cout << otherNoble.name << " defeats " << name << endl;
                double ratio = armyStrength / otherArmyStrength;
                for (size_t i = 0; i < otherNoble.army.size(); ++i) {
                    otherNoble.army[i]->setStrength(otherNoble.army[i]->getStrength() * (1 - ratio));
                }
                uponDeath();
            }
        }

    }

    friend ostream& operator<<(ostream& os, const Noble& noble);
private:
    string name;
    vector<Warrior*> army;
    bool alive;
};

// function prototypes
ostream& operator<<(ostream& os, const Warrior& warrior);
ostream& operator<<(ostream& os, const Noble& noble);
Warrior* getWarrior(const string& name, const vector<Warrior*>& warriors);
Noble* getNoble(const string& name, const vector<Noble*>& nobles);

int main() {
    ifstream ifs("nobleWarriors.txt");

    if (!ifs) {
        cerr << "Could not open the file" << endl;
        exit(1);
    }

    string command;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;


    while (ifs >> command) {
        if (command == "Noble") {
            string name;
            ifs >> name;
            if (getNoble(name, nobles) != nullptr) {
                cerr << "Noble " << name << " already exists" << endl;
            }
            else {
                nobles.push_back(new Noble(name));
            }
        }
        else if (command == "Warrior") {
            string name;
            int strength;
            ifs >> name >> strength;
            if (getWarrior(name, warriors) != nullptr) {
                cerr << "Warrior " << name << " already exists" << endl;
            }
            else {
                warriors.push_back(new Warrior(name, strength));
            }
        }
        else if (command == "Hire") {
            string nobleName;
            string warriorName;
            ifs >> nobleName >> warriorName;
            Noble* noble = getNoble(nobleName, nobles);
            Warrior* warrior = getWarrior(warriorName, warriors);
            if (noble == nullptr) {
                cerr << "Noble " << nobleName << " does not exist" << endl;
            }
            else if (warrior == nullptr) {
                cerr << "Warrior " << warriorName << " does not exist" << endl;
            }
            else {
                noble->hire(*warrior);
            }
        }
        else if (command == "Fire") {
            string nobleName;
            string warriorName;
            ifs >> nobleName >> warriorName;
            Noble* noble = getNoble(nobleName, nobles);
            Warrior* warrior = getWarrior(warriorName, warriors);
            if (noble == nullptr) {
                cerr << "Noble " << nobleName << " does not exist" << endl;
            }
            else if (warrior == nullptr) {
                cerr << "Warrior " << warriorName << " does not exist" << endl;
            }
            else {
                noble->fire(*warrior);
            }
        }
        else if (command == "Battle") {
            string noble1Name;
            string noble2Name;
            ifs >> noble1Name >> noble2Name;
            Noble* noble1 = getNoble(noble1Name, nobles);
            Noble* noble2 = getNoble(noble2Name, nobles);
            if (noble1 == nullptr) {
                cerr << "Noble " << noble1Name << " does not exist" << endl;
            }
            else if (noble2 == nullptr) {
                cerr << "Noble " << noble2Name << " does not exist" << endl;
            }
            else {
                noble1->battle(*noble2);
            }
        }
        else if (command == "Status") {
            cout << "Status" << endl;
            cout << "======" << endl;
            cout << "Nobles:" << endl;
            if (nobles.size() == 0) {
                cout << "NONE" << endl;
            }
            else {
                for (size_t i = 0; i < nobles.size(); ++i) {
                    cout << *nobles[i] << endl;
                }
            }
            cout << "\nUnemployed Warriors:" << endl;
            int unemployedWarriors = 0;
            for (size_t i = 0; i < warriors.size(); ++i) {
                if (!warriors[i]->isEmployed()) {
                    unemployedWarriors++;
                    cout << *warriors[i] << endl;
                }
            }

            if (warriors.size() == 0 || unemployedWarriors == 0) {
                cout << "NONE" << endl;
            }

        }
        else if (command == "Clear") {
            for (size_t i = 0; i < nobles.size(); ++i) {
                delete nobles[i];
            }
            nobles.clear();
            for (size_t i = 0; i < warriors.size(); ++i) {
                delete warriors[i];
            }
            warriors.clear();
        }
        else {
            cerr << "Unknown command: " << command << endl;
            exit(1);
        }
    }
}

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength;
    return os;
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size();
    for (Warrior* warrior : noble.army) {
        os << "\n\t" << *warrior;
    }
    return os;
}

Warrior* getWarrior(const string& name, const vector<Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == name) {
            return warriors[i];
        }
    }
    return nullptr;
}

Noble* getNoble(const string& name, const vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) {
            return nobles[i];
        }
    }
    return nullptr;
}