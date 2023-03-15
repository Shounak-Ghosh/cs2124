#include "hw04.cpp"

void test() {

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
    art.fire(cheetah); // should succeed
    cout << art << endl;

    art.battle(art); // should fail
    art.battle(lance);

    // lance is dead, so he should not be able to hire or anyone
    Warrior lawrence2("Lawrence, the Brave", 8);
    lance.hire(lawrence2);
    lance.fire(theGovernator);

    jim.battle(lance);
    billie.battle(linus); // linus should win
    // linus.battle(billie);
    billie.battle(lance);

    billie.battle(jim); // jim should win

    cout << "==========\n"
        << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";




}
