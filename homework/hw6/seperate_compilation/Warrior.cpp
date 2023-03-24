#include <vector>
#include <string>
#include <iostream>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    /**
     * @brief Construct a new Warrior object
     * 
     * @param name the name of the warrior
     * @param strength the strength of the warrior
     */
    Warrior::Warrior(const string& name, double strength):
        name(name), strength(strength), employer(nullptr) {}

    /**
     * @brief Get the name of the warrior
     * 
     * @return const string& the name of the warrior
     */
    const string& Warrior::getName() const {
        return name;
    }

    /**
     * @brief Get the strength of the warrior
     * 
     * @return const double the strength of the warrior
     */
    const double Warrior::getStrength() const {
        return strength;
    }

    /**
     * @brief Set the strength of the warrior
     * 
     * @param strength the new strength of the warrior
     */
    void Warrior::setStrength(double strength) {
        this->strength = strength;
    }

    /**
     * @brief Get the employer of the warrior
     * 
     * @return const Noble* the employer of the warrior
     */
    const Noble* Warrior::getEmployer() const {
        return employer;
    }

    /**
     * @brief Set the employer of the warrior
     * 
     * @param employer the new employer of the warrior
     */
    void Warrior::setEmployer(Noble* employer) {
        this->employer = employer;
    }

    /**
     * @brief Check if the warrior is hired
     * 
     * @return true if the warrior is hired, f
     *         false otherwise
     */
    bool Warrior::isHired() const {
        return employer != nullptr;
    }

    /**
     * @brief Make the warrior runaway
     * 
     * @return true if the warrior is successfully runaway,
     *        false otherwise
     */
    bool Warrior::runaway() {
        if (employer != nullptr) {
            cout << name << " flees in terror, abandoning his lord, "
                << employer->getName() << endl;
            employer->fire(*this, true);
            return true;
        }
        else {
            cout << name << " is already unemployed." << endl;
            return false;
        }
    }

    /**
     * @brief Overload the << operator for the Warrior
     * 
     * @param os the output stream
     * @param warrior the Warrior to be output
     * @return ostream& the output stream
     */
    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
}