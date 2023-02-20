/*
//TODO edit this
  hw04.cpp
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
class Warrior {
private:
     string name;
     double strength;
     bool employed;
public:
     Warrior(const string& name, double strength): name(name), strength(strength), employed(false) {}

     friend ostream& operator<<(ostream& os, const Warrior& warrior);

     const string& getName() const {
          return name;
     }

     double getStrength() const {
          return strength;
     }

     void setStrength(double strength) {
          this->strength = strength;
     }

     bool isEmployed() const {
          return employed;
     }

     void setEmployed(bool employed) {
          this->employed = employed;
     }
};

class Noble {
private:
     string name;
     vector<Warrior*> warriors;
     bool alive;

public:
     Noble(const string& name): name(name), alive(true) {}

     bool hire(Warrior& warrior) {
          if (alive && !warrior.isEmployed()) {
               Warrior* pWarrior(&warrior);
               warriors.push_back(pWarrior);
               warrior.setEmployed(true);
               return true;
          }
          else {
               cout << name << " failed to hire " << warrior.getName() << endl;
               return false;
          }
     }

     bool fire(Warrior& warrior) {
          if (alive && warrior.isEmployed()) {
               cout << warrior.getName() << " you don't work for me any more! -- " << name << endl;
               size_t warriorPosition = 0;
               for (size_t i = 0; i < warriors.size(); ++i) {
                    if (warriors[i]->getName() == warrior.getName()) {
                         warrior.setEmployed(false);
                         warriorPosition = i;
                         warriors[i] = nullptr;
                    }
               }
               // shift the pointers left by one, starting from the warrior's position
               for (size_t i = warriorPosition; i < warriors.size() - 1; ++i) {
                    warriors[i] = warriors[i + 1];
               }
               warriors.pop_back();
               return true;
          }
          else {
               cout << name << " failed to fire " << warrior.getName() << endl;
               return false;
          }
          return false;
     }

     void battle(Noble& other_noble) {
          cout << name << " battles " << other_noble.name << endl;
          if (!alive && !other_noble.alive) {
               cout << "Oh, NO! They're both dead! Yuck!" << endl;
          }
          else if (!alive) {
               cout << "He's dead, " << other_noble.name << endl;
          }
          else if (!other_noble.alive) {
               cout << "He's dead, " << name << endl;
          }
          else {
               double myStrength = getStrength();
               double otherStrength = other_noble.getStrength();
               if (myStrength == otherStrength) {
                    cout << "Mutual Annihilation: " << name << " and " << other_noble.name << " die at each other's hands" << endl;
                    for (size_t i = 0; i < warriors.size(); ++i) {
                         warriors[i]->setStrength(0);
                    }
                    for (size_t i = 0; i < other_noble.warriors.size(); ++i) {
                         other_noble.warriors[i]->setStrength(0);
                    }
                    alive = false;
                    other_noble.alive = false;
               }
               else if (myStrength > otherStrength) {
                    cout << name << " defeats " << other_noble.name << endl;
                    double ratio = otherStrength / myStrength;
                    for (size_t i = 0; i < warriors.size(); ++i) {
                         warriors[i]->setStrength(warriors[i]->getStrength() * (1 - ratio));
                    }
                    for (size_t i = 0; i < other_noble.warriors.size(); ++i) {
                         other_noble.warriors[i]->setStrength(0);
                    }
                    other_noble.alive = false;
               }
               else {
                    cout << other_noble.name << " defeats " << name << endl;
                    double ratio = myStrength / otherStrength;
                    for (size_t i = 0; i < other_noble.warriors.size(); ++i) {
                         warriors[i]->setStrength(other_noble.warriors[i]->getStrength() * (1 - ratio));
                    }
                    for (size_t i = 0; i < warriors.size(); ++i) {
                         warriors[i]->setStrength(0);
                    }
                    alive = false;
               }
          }
     }

     double getStrength() const {
          double currentStrength = 0.0;
          for (size_t i = 0; i < warriors.size(); ++i) {
               currentStrength += warriors[i]->getStrength();
          }
          return currentStrength;
     }

     friend ostream& operator<<(ostream& os, const Noble& noble);

};

// TODO insert function prototypes
ostream& operator<<(ostream& os, const Noble& noble);
ostream& operator<<(ostream& os, const Warrior& warrior);


int main() {

     Noble art("King Arthur");
     Noble lance("Lancelot du Lac");
     Noble jim("Jim");
     Noble linus("Linus Torvalds");
     Noble billie("Bill Gates");

     Warrior cheetah("Tarzan", 10);
     Warrior wizard("Merlin", 15);
     Warrior theGovernator("Conan", 12);
     Warrior nimoy("Spock", 15);
     Warrior lawless("Xena", 20);
     Warrior mrGreen("Hulk", 8);
     Warrior dylan("Hercules", 3);

     jim.hire(nimoy);
     lance.hire(theGovernator);
     art.hire(wizard);
     lance.hire(dylan);
     linus.hire(lawless);
     billie.hire(mrGreen);
     art.hire(cheetah);
     art.hire(nimoy);

     cout << "==========\n"
          << "Status before all battles, etc.\n";
     cout << jim << endl;
     cout << lance << endl;
     cout << art << endl;
     cout << linus << endl;
     cout << billie << endl;
     cout << "==========\n";

     art.fire(cheetah);
     cout << art << endl;

     art.battle(lance);
     jim.battle(lance);
     linus.battle(billie);
     billie.battle(lance);

     cout << "==========\n"
          << "Status after all battles, etc.\n";
     cout << jim << endl;
     cout << lance << endl;
     cout << art << endl;
     cout << linus << endl;
     cout << billie << endl;
     cout << "==========\n";

}

ostream& operator<<(ostream& os, const Noble& noble) {
     os << noble.name << " has an army of " << noble.warriors.size() << endl;
     for (size_t i = 0; i < noble.warriors.size(); ++i) {
          if (noble.warriors[i] != nullptr) {
               os << "\t" << *noble.warriors[i];
          }
     }
     return os;
}

ostream& operator<<(ostream& os, const Warrior& warrior) {
     os <<  warrior.name << ": " << warrior.strength << endl;
     return os;
}

