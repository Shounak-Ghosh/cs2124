/**
 * @file hw04.cpp
 * @author Shounak Ghosh
 * @brief Simulates a game of medivival times with nobles and warriors,
          as per the problem statement
 * @date 2023-02-20
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * @brief Represents a warrior
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
     Warrior(const string& name, double strength): name(name),
          strength(strength), employed(false) {}

     /**
      * @brief Get the warrior's name
      * 
      * @return const string& the warrior's name
      */
     const string& getName() const {
          return name;
     }

     /**
      * @brief Get the warrior's strength
      * 
      * @return double the warrior's strength
      */
     double getStrength() const {
          return strength;
     }

     /**
      * @brief Set the warrior's strength
      * 
      * @param strength the new strength of the warrior
      */
     void setStrength(double strength) {
          this->strength = strength;
     }

     /**
      * @brief Check if the warrior is employed
      * 
      * @return true if the warrior is employed
      * @return false otherwise
      */
     bool isEmployed() const {
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

     friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
     string name;
     double strength;
     bool employed;
};

/**
 * @brief Represents a Noble
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
      * @brief Attempt to hire a warrior
      * 
      * @param warrior the warrior to be hired
      * @return true if the warrior was hired
      * @return false otherwise
      */
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

     /**
      * @brief Attempt to fire a warrior
      * 
      * @param warrior the warrior to be fired
      * @return true if the warrior was fired
      * @return false otherwise
      */
     bool fire(Warrior& warrior) {
          size_t warriorPosition = warriors.size();
          for (size_t i = 0; i < warriors.size(); ++i) {
               if (warriors[i]->getName() == warrior.getName()) {
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
          if (warriorPosition != warriors.size()) {
               // shift the pointers left by one, 
               //starting from the warrior's position
               for (size_t i = warriorPosition; i < warriors.size() - 1; ++i) {
                    warriors[i] = warriors[i + 1];
               }
               // remove the last element
               warriors.pop_back();
               return true;
          }
          else {
               cout << name << " failed to fire " << warrior.getName() << endl;
               return false;
          }

     }

     /**
      * @brief Sets the strength of all the noble's warriors to 0
      * 
      */
     void death() {
          alive = false;
          for (size_t i = 0; i < warriors.size(); ++i) {
               warriors[i]->setStrength(0);
          }
     }

     /**
      * @brief Do battle with another noble
      * 
      * @param other_noble the other noble
      */
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
                    cout << "Mutual Annihilation: " << name << " and "
                         << other_noble.name << " die at each other's hands"
                         << endl;
                    death();
                    other_noble.death();
               }
               else if (myStrength > otherStrength) {
                    cout << name << " defeats " << other_noble.name << endl;
                    double ratio = otherStrength / myStrength;
                    for (size_t i = 0; i < warriors.size(); ++i) {
                         warriors[i]->setStrength(warriors[i]->getStrength()
                              * (1 - ratio));
                    }
                    other_noble.death();
               }
               else {
                    cout << other_noble.name << " defeats " << name << endl;
                    double ratio = myStrength / otherStrength;
                    for (size_t i = 0; i < other_noble.warriors.size(); ++i) {
                         warriors[i]->setStrength(other_noble.warriors[i]->
                              getStrength() * (1 - ratio));
                    }
                    death();
               }
          }
     }

     /**
      * @brief Get the strength of the noble 
      * 
      * @return double the noble's strength
      */
     double getStrength() const {
          double currentStrength = 0.0;
          for (size_t i = 0; i < warriors.size(); ++i) {
               currentStrength += warriors[i]->getStrength();
          }
          return currentStrength;
     }

     friend ostream& operator<<(ostream& os, const Noble& noble);
private:
     string name;
     vector<Warrior*> warriors;
     bool alive;
};

// function prototypes
ostream& operator<<(ostream& os, const Noble& noble);
ostream& operator<<(ostream& os, const Warrior& warrior);

/**
 * @brief Simulate a game of medival times
 *
 * @return int 0 on success
 */
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
     Warrior lawrence("Lawrence", 8);

     art.hire(wizard);
     art.hire(cheetah);
     art.hire(nimoy);
     art.hire(lawrence);

     lance.hire(theGovernator);
     lance.hire(dylan);

     jim.hire(nimoy);

     linus.hire(lawless);

     billie.hire(mrGreen);



     cout << "==========\n"
          << "Status before all battles, etc.\n";
     cout << jim << endl;
     cout << lance << endl;
     cout << art << endl;
     cout << linus << endl;
     cout << billie << endl;
     cout << "==========\n";


     art.fire(mrGreen); // should fail
     art.fire(cheetah);
     cout << art << endl;

     art.battle(lance);

     // lance is dead, so he should not be able to hire or anyone
     Warrior lawrence2("Lawrence, the Brave", 8);
     lance.hire(lawrence2);
     lance.fire(theGovernator);

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

/**
 * @brief Overload the << operator for the Noble class
 *
 * @param os output stream
 * @param noble noble object to be printed
 * @return ostream& output stream
 */
ostream& operator<<(ostream& os, const Noble& noble) {
     os << noble.name << " has an army of " <<
          noble.warriors.size() << endl;
     for (size_t i = 0; i < noble.warriors.size(); ++i) {
          if (noble.warriors[i] != nullptr) {
               os << "\t" << *noble.warriors[i];
          }
     }
     return os;
}

/**
 * @brief Overload the << operator for the Warrior class
 *
 * @param os output stream
 * @param warrior warrior object to be printed
 * @return ostream& output stream
 */
ostream& operator<<(ostream& os, const Warrior& warrior) {
     os << warrior.name << ": " << warrior.strength << endl;
     return os;
}

