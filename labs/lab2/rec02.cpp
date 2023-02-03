/* 
   Author: Shounak Ghosh
   rec02.cpp
   spring 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct hydrocarbon {
    vector<string> names;
    int carbon;
    int hydrogen;
};

void get_filestream(ifstream& file); // function prototype

void print_hydrocarbon(const hydrocarbon& h); // function prototype

void print_vector(const vector<hydrocarbon>& hydrocarbons); // function prototype

void fill_vector(ifstream& file, vector<hydrocarbon>& hydrocarbons); // function prototype

size_t find_hydrocarbon(const vector<hydrocarbon>& hydrocarbons, const hydrocarbon& h); // function prototype

void sort_vector(vector<hydrocarbon>& hydrocarbons); // function prototype

int main() {
    vector<hydrocarbon> hydrocarbons;
    ifstream file;

    get_filestream(file);

    fill_vector(file, hydrocarbons);

    sort_vector(hydrocarbons);

    print_vector(hydrocarbons);

}

void get_filestream(ifstream& file)
{
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;
    file.open(filename);

    while (!file) {
        cout << "File not found" << endl;
        file.clear();
        cout << "Enter a filename: ";
        cin >> filename;
        file.open(filename);
    }
}

size_t find_hydrocarbon(const vector<hydrocarbon>& hydrocarbons, const hydrocarbon& h)
{
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        if (hydrocarbons[i].carbon == h.carbon && hydrocarbons[i].hydrogen == h.hydrogen) {
            return i;
        }
    }
    return hydrocarbons.size();
}

void fill_vector(ifstream& file, vector<hydrocarbon>& hydrocarbons)
{
    string name;
    char temp;
    int carbon;
    int hydrogen;
    while (file >> name >> temp >> carbon >> temp >> hydrogen) {
        hydrocarbon h;
        h.names.push_back(name);
        h.carbon = carbon;
        h.hydrogen = hydrogen;

        size_t index = find_hydrocarbon(hydrocarbons, h);
        if (index == hydrocarbons.size()) {
            hydrocarbons.push_back(h);
        }
        else {
            hydrocarbons[index].names.push_back(h.names[0]);
        }
    }
    file.close();
}

void print_hydrocarbon(const hydrocarbon& h) {

    cout << "C" << h.carbon << "H" << h.hydrogen << " ";
    for (const string& name : h.names) {
        cout << name << " ";
    }
    cout << endl;
}


void print_vector(const vector<hydrocarbon>& hydrocarbons)
{
    for (const hydrocarbon& h : hydrocarbons) {
        print_hydrocarbon(h);
    }
}

void sort_vector(vector<hydrocarbon>& hydrocarbons)
{
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        for (size_t j = 0; j < hydrocarbons.size() - 1; j++) {
            if (hydrocarbons[j].carbon > hydrocarbons[j + 1].carbon) {
                hydrocarbon temp = hydrocarbons[j];
                hydrocarbons[j] = hydrocarbons[j + 1];
                hydrocarbons[j + 1] = temp;
            }
            else if (hydrocarbons[j].carbon == hydrocarbons[j + 1].carbon) {
                if (hydrocarbons[j].hydrogen > hydrocarbons[j + 1].hydrogen) {
                    hydrocarbon temp = hydrocarbons[j];
                    hydrocarbons[j] = hydrocarbons[j + 1];
                    hydrocarbons[j + 1] = temp;
                }
            }
        }
    }
}
