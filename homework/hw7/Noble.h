#include <string>
#include <vector>

#ifndef WARRIORCRAFT_NOBLE_H
#define WARRIORCRAFT_NOBLE_H
namespace WarriorCraft {
    class Protector; // forward declaration

    class Noble {
    public:
        Noble(const std::string& name, double strength = 0);
        std::string getName() const;
        double getStrength() const;
        void setStrength(double strength);
        void battle(Noble& other);
        virtual void battleCry() const = 0;
        virtual void postBattle(double ratio);
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    protected:
        std::string name;
        double strength;
        bool alive;

    };

    class Lord: public Noble {
    public:
        Lord(const std::string& name);
        bool hires(Protector& protector);
        bool fires(Protector& protector, bool runaway = false);
        void battleCry() const;
        void postBattle(double ratio);
        friend std::ostream& operator<<(std::ostream& os, const Lord& noble);
    private:
        std::vector<Protector*> army;

    };

    class PersonWithStrengthToFight: public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void battleCry() const;
        void postBattle(double ratio);
        friend std::ostream& operator<<(std::ostream& os, const PersonWithStrengthToFight& noble);
    };


}
#endif //WARRIORCRAFT_NOBLE_H