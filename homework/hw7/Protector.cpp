/**
 * @file Protector.cpp
 * @author Shounak Ghosh
 * @brief Source file for Protector and derived classes
 * @date 2023-04-13
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    /**
     * @brief Base constructor for a Protector
     * 
     * @param name the name of the Protector
     * @param strength the strenght of a Protector
     */
    Protector::Protector(const string& name, double strength): name(name), strength(strength), alive(true), lord(nullptr) {}

    /**
     * @brief Get the name of the Protector
     * 
     * @return const string& the Protector's name
     */
    const string& Protector::getName() const {
        return name;
    }

    /**
     * @brief Get the strength of the Protector
     * 
     * @return double the Protector's strength
     */
    double Protector::getStrength() const {
        return strength;
    }

    /**
     * @brief Set the strength of the Protector
     * 
     * @param strength the new strength of the Protector
     */
    void Protector::setStrength(double strength) {
        this->strength = strength;
    }

    /**
     * @brief Return the Lord of the Protector
     * 
     * @return Lord* const the Lord of the Protector
     */
    Lord* const Protector::getLord() const {
        return lord;
    }

    /**
     * @brief Set the Lord of the Protector
     * 
     * @param lord the new Lord of the Protector
     */
    void Protector::setLord(Lord* lord) {
        this->lord = lord;
    }

    /**
     * @brief Have the Protector runaway from his Lord
     * 
     * @return true the Protector has fled
     * @return false the Protector has not fled
     */
    bool Protector::runaway() {
        if (lord != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << lord->getName() << endl;
            lord->fires(*this,true);
            lord = nullptr;
            return true;
        }
        return false;
    }

    /**
     * @brief Output the Protector's name and strength
     * 
     * @param os the output stream
     * @param protector the Protector to be output
     * @return ostream& the output stream
     */
    ostream& operator<<(ostream& os, const Protector& protector) {
        os << protector.name << " has strength " << protector.strength;
        return os;
    }

    /**
     * @brief Construct a new Wizard object
     * 
     * @param name the name of the Wizard
     * @param strength the strength of the Wizard
     */
    Wizard::Wizard(const string& name, double strength): Protector(name, strength) {}

    /**
     * @brief Output the Wizard's battle cry
     * 
     */
    void Wizard::battleCry() const {
        cout << "POOF" << endl;
    }

    /**
     * @brief Construct a new Warrior object
     * 
     */
    Warrior::Warrior(const string& name, double strength): Protector(name, strength) {}

    /**
     * @brief Construct a new Archer object
     * 
     * @param name the name of the Archer
     * @param strength the strength of the Archer
     */
    Archer::Archer(const string& name, double strength): Warrior(name, strength) {}

    /**
     * @brief Output the Archer's battle cry
     * 
     */
    void Archer::battleCry() const {
        cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }

    /**
     * @brief Construct a new Swordsman object
     * 
     * @param name the name of the Swordsman
     * @param strength the strength of the Swordsman
     */
    Swordsman::Swordsman(const string& name, double strength): Warrior(name, strength) {}

    /**
     * @brief Output the Swordsman's battle cry
     * 
     */
    void Swordsman::battleCry() const {
        cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }
}

