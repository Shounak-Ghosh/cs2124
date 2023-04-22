/*
  rec05.cpp
  Author: Shounak Ghosh

 */

//TODO: add doc comments

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section {
private:
     class StudentRecord {
     private:
          string name;
          vector<int> grades;

     public:
          StudentRecord(const string& name): name(name), grades(14, -1) {}

          // copy constructor
          // StudentRecord(const StudentRecord& rhs): name(rhs.name), grades(rhs.grades) {}

          const string& getName() const { return name; }

          void setGrade(int grade, int week) {
               grades[week] = grade;
          }

          friend ostream& operator<<(ostream& os, const StudentRecord& student);
     };

     class TimeSlot {
     private:
          string day;
          unsigned time;

     public:
          TimeSlot(const string& day, unsigned time): day(day), time(time) {}

          TimeSlot(const TimeSlot& rhs): day(rhs.day), time(rhs.time) {}


          friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot);
     };

     string name;
     vector<StudentRecord*> students;
     TimeSlot timeSlot;


public:
     Section(const string& name, const string& day, int time): name(name), timeSlot(day, time) {}

     // destructor
     ~Section() {
          for (size_t i = 0; i < students.size(); ++i) {
               cout << "Deleting " << students[i]->getName() << endl;
               delete students[i];
          }
     }

     // copy constructor
     Section(const Section& rhs): name(rhs.name), timeSlot(rhs.timeSlot) {
          for (size_t i = 0; i < rhs.students.size(); ++i) {
               students.push_back(new StudentRecord(*rhs.students[i]));
          }
     }

     void addStudent(const string& name) {
          students.push_back(new StudentRecord(name));
     }

     void setStudentGrade(const string& name, int grade, int week) {
          for (size_t i = 0; i < students.size(); ++i) {
               if (students[i]->getName() == name) {
                    students[i]->setGrade(grade, week);
                    return;
               }
          }
     }
     

     friend ostream& operator<<(ostream& os, const Section& section);
     friend ostream& operator<<(ostream& os, const Section::StudentRecord& student);
     friend ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot);

};

class LabWorker {
private:
     string name;
     Section* pSection;
public:
     LabWorker(const string& name): name(name), pSection(nullptr) {}

     void addSection(Section& section) {
          pSection = &section;
     }

     void addGrade(const string& studentName, int grade, int week) {
          pSection->setStudentGrade(studentName, grade, week);
     }
     friend ostream& operator<<(ostream& os, const LabWorker& worker);
};

// function prototypes
ostream& operator<<(ostream& os, const Section::StudentRecord& student);
ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot);
ostream& operator<<(ostream& os, const Section& section);
ostream& operator<<(ostream& os, const LabWorker& worker);


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

     cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

     cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

     cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

     cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

     cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

     cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);  
     moe.addGrade("Paul", 19, 1);  
     moe.addGrade("George", 16, 1);  
     moe.addGrade("Ringo", 7, 1);  
     cout << moe << endl;

     cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);  
     moe.addGrade("Paul", 20, 3);  
     moe.addGrade("Ringo", 0, 3);  
     moe.addGrade("George", 16, 3);  
     cout << moe << endl;

     cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
          << "those students (or rather their records?)\n";

     cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
          << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main


ostream& operator<<(ostream& os, const Section& section) {
     os << "Section " << section.name << ", Time slot: ";
     os << section.timeSlot << ", Students: ";
     if (section.students.size() == 0) {
          os << "None";
     }
     else
     {
          os << endl;
          for (size_t i = 0; i < section.students.size(); ++i) {
               os << *section.students[i] << endl;
          }
     }

     return os;
}

ostream& operator<<(ostream& os, const Section::StudentRecord& student) {
     os << "Name: " << student.name << ", Grades: ";
     for (size_t i = 0; i < student.grades.size(); ++i) {
          os << student.grades[i] << " ";
     }
     return os;
}

ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot) {
     os << "[Day: " << timeSlot.day << ", Start Time: " << timeSlot.time%12 << (timeSlot.time > 12 ? "pm" : "am" ) << "]";
     return os;
}



ostream& operator<<(ostream& os, const LabWorker& worker) {
     if (worker.pSection == nullptr) {
          os << worker.name << " has no section";
     }
     else {
          os << worker.name << " has " << *worker.pSection;
     }
     return os;
}

