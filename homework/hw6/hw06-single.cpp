/**
 * @file hw06-single.cpp
 * @author Shounak Ghosh
 * @brief Stimulate a game of medival times, as per the problem statement
 * @date 2023-03-13
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble; // forward declaration

class Warrior {
public:
    Warrior(const string& name, int strength);
    const string& getName() const;
    const int getStrength() const;
    void setStrength(int strength);
    const Noble* getEmployer() const;
    void setEmployer(Noble* employer);
    bool isHired() const;
    bool runaway();
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    int strength;
    Noble* employer;
};

class Noble {
public:
    Noble(const string& name);
    const string& getName() const;
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior, bool runaway = false);
    void battle(Noble& otherNoble);
    void uponDeath();
    friend ostream& operator<<(ostream& os, const Noble& otherNoble);
private:
    string name;
    double strength;
    bool alive;
    vector<Warrior*> army;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy); // spock is already hired

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
        << lance << endl
        << jim << endl
        << linus << endl
        << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
        << lance << endl
        << jim << endl
        << linus << endl
        << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
        << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
        << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

Warrior::Warrior(const string& name, int strength):
    name(name), strength(strength), employer(nullptr) {}

const string& Warrior::getName() const {
    return name;
}

const int Warrior::getStrength() const {
    return strength;
}

void Warrior::setStrength(int strength) {
    this->strength = strength;
}

const Noble* Warrior::getEmployer() const {
    return employer;
}

void Warrior::setEmployer(Noble* employer) {
    this->employer = employer;
}

bool Warrior::isHired() const {
    return employer != nullptr;
}

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

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength;
    return os;
}

Noble::Noble(const string& name): name(name), strength(0), alive(true) {}

const string& Noble::getName() const {
    return name;
}

bool Noble::hire(Warrior& warrior) {
    if (!alive) {
        cout << name << " is dead -- they cannot hire anymore." << endl;
        return false;
    }
    else if (warrior.isHired()) {
        cout << warrior.getName() << " is already hired!" << endl;
        return false;
    }
    else {
        warrior.setEmployer(this);
        army.push_back(&warrior);
        strength += warrior.getStrength();
        return true;
    }
}

bool Noble::fire(Warrior& warrior, bool runaway) {
    size_t warriorPosition = army.size();
    for (size_t i = 0; i < army.size(); ++i) {
        if (alive && army[i] == &warrior) {
            if (!runaway) {
                cout << warrior.getName() << " you don't work for me any more! -- "
                    << name << endl;
            }
            warriorPosition = i;
            strength -= warrior.getStrength();
            warrior.setEmployer(nullptr);
        }
    }

    if (warriorPosition < army.size()) {
        for (size_t i = warriorPosition; i < army.size() - 1; ++i) {
            army[i] = army[i + 1];
        }
        army.pop_back();
        return true;
    }
    else {
        cout << "Couldn't find " << warrior.getName() << " in " << name
            << "'s army!" << endl;
        return false;
    }
}

void Noble::uponDeath() {
    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->setStrength(0);
    }
    strength = 0;
    alive = false;
}

void Noble::battle(Noble& otherNoble) {
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
    else if (strength == otherNoble.strength) {
        cout << "Mutual Annihilation: " << name << " and " << otherNoble.name
            << " die at each other's hands" << endl;
        uponDeath();
        otherNoble.uponDeath();
    }
    else if (strength > otherNoble.strength) {
        cout << name << " defeats " << otherNoble.name << endl;
        double ratio = (strength - otherNoble.strength) / strength;
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(army[i]->getStrength() * ratio);
        }
        strength = strength * ratio;
        otherNoble.uponDeath();
    }
    else {
        cout << otherNoble.name << " defeats " << name << endl;
        double ratio = (otherNoble.strength - strength) / otherNoble.strength;
        for (size_t i = 0; i < otherNoble.army.size(); ++i) {
            otherNoble.army[i]->setStrength(otherNoble.army[i]->getStrength() * ratio);
        }
        otherNoble.strength = otherNoble.strength * ratio;
        uponDeath();
    }
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (size_t i = 0; i < noble.army.size(); ++i) {
        os << "\t" << *noble.army[i] << endl;
    }
    return os;
}



