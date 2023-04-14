#include <string>
#include <vector>
#include <iostream>
#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft {
    /**
     * @brief Base constructor for a Noble
     * 
     * @param name the name of the Noble
     * @param strength the initial strength of the Noble
     */
    Noble::Noble(const string& name, double strength): name(name), strength(strength), alive(true) {}

    /**
     * @brief Get the name of the Noble
     * 
     * @return string the Noble's name
     */
    const string& Noble::getName() const {
        return name;
    }

    /**
     * @brief Get the strength of the Noble
     * 
     * @return double the Noble's strength
     */
    double Noble::getStrength() const {
        return strength;
    }

    /**
     * @brief Set the strength of the Noble
     * 
     * @param strength set the Noble's strength to this value
     */
    void Noble::setStrength(double strength) {
        this->strength = strength;
    }

    /**
     * @brief Return true if the Noble is alive, false otherwise
     * 
     * @return true the Noble is alive
     * @return false the Noble is dead
     */
    bool Noble::isAlive() const {
        return alive;
    }

    /**
     * @brief Simulate a battle between two Nobles
     * 
     * @param other the other Noble to be battled
     */
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

    /**
     * @brief Update the Noble's strength after a battle
     * 
     * @param ratio the ratio of the other Noble's strength to the Noble's strength
     */
    void Noble::postBattle(double ratio) {
        if (ratio >= 1) {
            strength = 0;
            alive = false;
        }
        else
            strength = strength * (1 - ratio);
    }

    /**
     * @brief Print the Noble's current status
     * 
     * @param os the output stream 
     * @param noble the Noble to be printed
     * @return ostream& the output stream
     */
    ostream& operator<<(ostream& os, const Noble& noble) {
        return noble.print(os);
    }

    /**
     * @brief Construct a new Lord object
     * 
     * @param name 
     */
    Lord::Lord(const string& name): Noble(name) {}

    bool Lord::hires(Protector& protector) {
        if (isAlive() && protector.getLord() == nullptr) {
            army.push_back(&protector);
            protector.setLord(this);
            setStrength(getStrength() + protector.getStrength());
            return true;
        }
        return false; // protector already has a lord
    }

    /**
     * @brief Fire a Protector from the Lord's army
     * 
     * @param protector the Protector to be fired
     * @param runaway true if the Protector is running away, false otherwise
     * @return true if the Protector was fired
     * @return false if the Protector was not fired
     */
    bool Lord::fires(Protector& protector, bool runaway) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &protector) {
                if (!runaway)
                    cout << protector.getName() << ", you don't work for me anymore ! -- " << getName() << endl;
                setStrength(getStrength() - protector.getStrength());
                protector.setLord(nullptr);
                for (size_t j = i; j < army.size() - 1; ++j) {
                    army[j] = army[j + 1];
                }
                army.pop_back();
                return true;
            }
        }
        cout << "Couldn't find " << protector.getName() << " in " << getName() << "'s army!" << endl;
        return false;
    }

    /**
     * @brief Display the Lord's battle cry
     * 
     */
    void Lord::battleCry() const {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->battleCry();
        }
    }

    /**
     * @brief Update the Lord's army after a battle
     * 
     * @param ratio the ratio of the other Noble's strength to the Noble's strength
     */
    void Lord::postBattle(double ratio) {
        Noble::postBattle(ratio);
        for (size_t i = 0; i < army.size(); ++i) {
            if (ratio >= 1) // if lord is dead, all his army dies
                army[i]->setStrength(0);
            else
                army[i]->setStrength(army[i]->getStrength() * (1 - ratio));
        }
    }

    /**
     * @brief Output the Lord's current status
     * 
     * @param os the output stream
     * @return ostream& the output stream
     */
     ostream& Lord::print(ostream& os) const {
        os << getName() << " has an army of size: " << army.size();
        for (size_t i = 0; i < army.size(); ++i) {
            os << "\n\t" << *army[i];
        }
        return os;
    }

    /**
     * @brief Construct a new PersonWithStrengthToFight object  
     * 
     * @param name the name of the object
     * @param strength the strength of the object
     */
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength): Noble(name, strength) {}

    void PersonWithStrengthToFight::battleCry() const {
        cout << "Ugh!" << endl;
    }

    /**
     * @brief Output the PersonWithStrengthToFight's current status
     * 
     * @param os the output stream
     * @return ostream& the output stream
     */
    ostream& PersonWithStrengthToFight::print(ostream& os) const {
        os << getName() << " has strength: " << getStrength();
        return os;
    }
}