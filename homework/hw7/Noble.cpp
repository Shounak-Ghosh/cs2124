#include <string>
#include <vector>
#include <iostream>
#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name, double strength): name(name), strength(strength), alive(true) {}

    string Noble::getName() const {
        return name;
    }

    double Noble::getStrength() const {
        return strength;
    }

    void Noble::setStrength(double strength) {
        this->strength = strength;
    }

    void Noble::battle(Noble& other) {
        cout << name << " battles " << other.name << endl;
        if (!alive && !other.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!alive) {
            cout << "He's dead, " << other.name << endl;
        }
        else if (!other.alive) {
            cout << "He's dead, " << name << endl;
        }
        else {
            battleCry();
            other.battleCry();
            double ratio = other.strength / strength;
            postBattle(ratio);
            other.postBattle(1 / ratio);
            if (strength > other.strength) {
                cout << name << " defeats " << other.name << endl;
            }
            else if (strength < other.strength) {
                cout << other.name << " defeats " << name << endl;
            }
            else {
                cout << "Mutual Annihilation: " << name << " and " << other.name << " die at each other's hands" << endl;
            }
        }

    }

    void Noble::postBattle(double ratio) {
        if (ratio >= 1) {
            strength = 0;
            alive = false;
        }
        else
            strength = strength * (1 - ratio);
    }

    Lord::Lord(const string& name): Noble(name) {}

    bool Lord::hires(Protector& protector) {
        if (alive && protector.getLord() == nullptr) {
            army.push_back(&protector);
            protector.setLord(this);
            strength += protector.getStrength();
            return true;
        }
        return false; // protector already has a lord
    }

    bool Lord::fires(Protector& protector, bool runaway) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &protector) {
                if (!runaway)
                    cout << protector.getName() << ", you don't work for me anymore ! -- " << name << endl;
                strength -= protector.getStrength();
                protector.setLord(nullptr);
                for (size_t j = i; j < army.size() - 1; ++j) {
                    army[j] = army[j + 1];
                }
                army.pop_back();
                return true;
            }
        }
        cout << "Couldn't find " << protector.getName() << " in " << name << "'s army!" << endl;
        return false;
    }

    void Lord::battleCry() const {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->battleCry();
        }
    }

    void Lord::postBattle(double ratio) {
        Noble::postBattle(ratio);
        for (size_t i = 0; i < army.size(); ++i) {
            if (ratio >= 1) // if lord is dead, all his army dies
                army[i]->setStrength(0);
            else
                army[i]->setStrength(army[i]->getStrength() * (1 - ratio));
        }
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength): Noble(name, strength) {}

    void PersonWithStrengthToFight::battleCry() const {
        cout << "Ugh!" << endl;
    }

    void PersonWithStrengthToFight::postBattle(double ratio) {
        Noble::postBattle(ratio);
    }

    // ostream& operator<<(ostream& os, const Noble& noble) {
    //     os << noble.name << " has an army of " << noble.strength << endl;
    //     return os;
    // }

    ostream& operator<<(ostream& os, const Lord& noble) {
        os << noble.name << " has an army of size: " << noble.army.size();
        for (size_t i = 0; i < noble.army.size(); ++i) {
            os << "\n\t" << *noble.army[i];
        }
        return os;
    }

    ostream& operator<<(ostream& os, const PersonWithStrengthToFight& noble) {
        os << noble.name << " has strength: " << noble.strength;
        return os;
    }


}