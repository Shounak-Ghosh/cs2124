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

/**
 * @brief Simulates a Warrior, as per the problem statement
 *
 */
class Warrior {
public:
    /**
     * @brief Construct a new Warrior object
     *
     * @param name the name of the warrior
     * @param strength the strength of the warrior
     */
    Warrior(const string& name, int strength): name(name), strength(strength), employed(false) {}

    /**
     * @brief Get the name of the warrior
     *
     * @return const string& the name of the warrior
     */
    const string& getName() const {
        return name;
    }

    /**
     * @brief Get the strength of the warrior
     *
     * @return const int the strength of the warrior
     */
    const int getStrength() const {
        return strength;
    }

    /**
     * @brief Set the strength of the warrior
     *
     * @param strength the new strength of the warrior
     */
    void setStrength(int strength) {
        this->strength = strength;
    }

    /**
     * @brief Check if the warrior is employed
     *
     * @return true if the warrior is employed
     * @return false otherwise
     */
    const bool isEmployed() const {
        return employed;
    }

    /**
     * @brief Set the employed status of the warrior
     *
     * @param employed the new employed status of the warrior
     */
    void setEmployed(bool employed) {
        this->employed = employed;
    }

    /**
     * @brief Overload the output operator for the warrior class
     *
     * @param os the output stream
     * @param warrior the warrior to output
     * @return ostream& the output stream
     */
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    int strength;
    bool employed;
};

/**
 * @brief Simulates a Noble, as per the problem statement
 *
 */
class Noble {
public:
    /**
     * @brief Construct a new Noble object
     *
     * @param name the name of the noble
     */
    Noble(const string& name): name(name), alive(true) {}

    /**
     * @brief Get the name of the noble
     *
     * @return string the name of the noble
     */
    const string& getName() const {
        return name;
    }

    /**
     * @brief Hire a warrior for the noble
     *
     * @param warrior the warrior to hire
     * @return true if the warrior was hired
     * @return false otherwise
     */
    bool hire(Warrior& warrior) {
        if (!warrior.isEmployed()) {
            army.push_back(&warrior);
            warrior.setEmployed(true);
            return true;
        }
        else {
            cout << name << " failed to fire " << warrior.getName() << endl;
            return false;
        }
    }

    /**
     * @brief Fire a warrior from the noble
     *
     * @param warrior the warrior to fire
     * @return true if the warrior was fired
     * @return false otherwise
     */
    bool fire(Warrior& warrior) {
        size_t warriorPosition = army.size();
          for (size_t i = 0; i < army.size(); ++i) {
               if (army[i] == &warrior) { // direct comparison of addresses
                    if (alive) { // a noble must be alive to fire a warrior
                         cout << warrior.getName() <<
                              " you don't work for me any more! -- " <<
                              name << endl;
                         warrior.setEmployed(false);
                         warriorPosition = i;
                    }
               }
          }
          // the warrior is employed by this noble
          if (warriorPosition != army.size()) {
               // shift the pointers left by one, 
               //starting from the warrior's position
               for (size_t i = warriorPosition; i < army.size() - 1; ++i) {
                    army[i] = army[i + 1];
               }
               // remove the last element
               army.pop_back();
               return true;
          }
          else {
               cout << name << " failed to fire " << warrior.getName() << endl;
               return false;
          }
    }

    /**
     * @brief Get the noble's army strength
     *
     * @return double returns the army strength
     */
    double getArmyStrength() const {
        double strength = 0;
        for (Warrior* warrior : army) {
            strength += warrior->getStrength();
        }
        return strength;
    }

    /**
      * @brief Sets the strength of all the noble's army to 0,
      *        and sets the noble's alive status to false
      *
      */
    void uponDeath() {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0);
        }
        alive = false;
    }

    /**
     * @brief Do battle with another noble
     *
     * @param otherNoble the other noble
     */
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

    /**
     * @brief Overload the output operator for the noble class
     *
     * @param os the output stream
     * @param noble the noble to output
     * @return ostream& the output stream
     */
    friend ostream& operator<<(ostream& os, const Noble& noble);
private:
    string name;
    vector<Warrior*> army;
    bool alive;
};

// function prototypes
ostream& operator<<(ostream& os, const Warrior& warrior);
ostream& operator<<(ostream& os, const Noble& noble);
Warrior* getWarrior(const string& name, const vector<Warrior*>& army);
Noble* getNoble(const string& name, const vector<Noble*>& nobles);

/**
 * @brief Stimulate a game of medieval times, as per the problem statement
 *
 * @return int 0 on success
 */
int main() {
    ifstream ifs("nobleWarriors.txt");

    if (!ifs) {
        cerr << "Could not open the file" << endl;
        exit(1);
    }

    string command;
    vector<Noble*> nobles;
    vector<Warrior*> army;


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
            if (getWarrior(name, army) != nullptr) {
                cerr << "Warrior " << name << " already exists" << endl;
            }
            else {
                army.push_back(new Warrior(name, strength));
            }
        }
        else if (command == "Hire") {
            string nobleName;
            string warriorName;
            ifs >> nobleName >> warriorName;
            Noble* noble = getNoble(nobleName, nobles);
            Warrior* warrior = getWarrior(warriorName, army);
            if (noble == nullptr) {
                cerr << "Noble " << nobleName << " does not exist" << endl;
            }
            else if (warrior == nullptr) {
                cerr << "Attempting to hire using unknown warrior: " << warriorName << endl;
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
            Warrior* warrior = getWarrior(warriorName, army);
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
            for (size_t i = 0; i < army.size(); ++i) {
                if (!army[i]->isEmployed()) {
                    unemployedWarriors++;
                    cout << "\t" << *army[i] << endl;
                }
            }

            if (army.size() == 0 || unemployedWarriors == 0) {
                cout << "NONE" << endl;
            }

        }
        else if (command == "Clear") {
            for (size_t i = 0; i < nobles.size(); ++i) {
                delete nobles[i];
            }
            nobles.clear();
            for (size_t i = 0; i < army.size(); ++i) {
                delete army[i];
            }
            army.clear();
        }
        else {
            cerr << "Unknown command: " << command << endl;
            exit(1);
        }
    }
}

/**
 * @brief Overload the output operator for the Warrior class
 *
 * @param os the output stream
 * @param warrior the warrior to output
 * @return ostream& the output stream
 */
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength;
    return os;
}

/**
 * @brief Overload the output operator for the Noble class
 *
 * @param os the output stream
 * @param noble the noble to output
 * @return ostream& the output stream
 */
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size();
    for (Warrior* warrior : noble.army) {
        os << "\n\t" << *warrior;
    }
    return os;
}

/**
 * @brief Get a warrior from a vector of army
 *
 * @param name the name of the warrior to get
 * @param army the vector of army
 * @return Warrior* the warrior with the given name,
 *         or nullptr if it does not exist
 */
Warrior* getWarrior(const string& name, const vector<Warrior*>& army) {
    for (size_t i = 0; i < army.size(); ++i) {
        if (army[i]->getName() == name) {
            return army[i];
        }
    }
    return nullptr;
}

/**
 * @brief Get the Noble object
 * 
 * @param name the name of the noble to get
 * @param nobles the vector of nobles
 * @return Noble* the noble with the given name, 
 *         or nullptr if it does not exist
 */
Noble* getNoble(const string& name, const vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) {
            return nobles[i];
        }
    }
    return nullptr;
}