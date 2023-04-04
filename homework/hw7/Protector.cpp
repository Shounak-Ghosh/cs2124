#include <string>
#include <vector>
#include <iostream>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    Protector::Protector(const string& name, double strength): name(name), strength(strength), alive(true), lord(nullptr) {}

    string Protector::getName() const {
        return name;
    }

    double Protector::getStrength() const {
        return strength;
    }

    void Protector::setStrength(double strength) {
        this->strength = strength;
    }

    void Protector::setLord(Lord* lord) {
        this->lord = lord;
    }

    Lord* Protector::getLord() const {
        return lord;
    }

    bool Protector::runaway() {
        if (lord != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << lord->getName() << endl;
            lord->fires(*this,true);
            lord = nullptr;
            return true;
        }
        return false;
    }

    ostream& operator<<(ostream& os, const Protector& protector) {
        os << protector.name << ": " << protector.strength;
        return os;
    }

    Wizard::Wizard(const string& name, double strength): Protector(name, strength) {}

    void Wizard::battleCry() const {
        cout << "POOF" << endl;
    }

    Warrior::Warrior(const string& name, double strength): Protector(name, strength) {}

    Archer::Archer(const string& name, double strength): Warrior(name, strength) {}

    void Archer::battleCry() const {
        cout << "TWANG! " << name << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }

    Swordsman::Swordsman(const string& name, double strength): Warrior(name, strength) {}

    void Swordsman::battleCry() const {
        cout << "CLANG! " << name << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }

}

