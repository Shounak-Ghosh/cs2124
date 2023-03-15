#include <string>
#include <iostream>

#ifndef WARRIOR_H
#define WARRIOR_H
namespace WarriorCraft {
    class Noble; 
    class Warrior {
    public:
        Warrior(const std::string& name, int strength);
        const std::string& getName() const;
        const int getStrength() const;
        void setStrength(int strength);
        const Noble* getEmployer() const;
        void setEmployer(Noble* employer);
        bool isHired() const;
        bool runaway();
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    private:
        std::string name;
        int strength;
        Noble* employer;
    };
}
#endif