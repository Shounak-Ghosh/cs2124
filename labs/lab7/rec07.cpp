/*
  rec07_starter.cpp
  Author: Shounak Ghosh
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;


class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();
    const vector<Student*>& getStudents() const;

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

    const vector<Course*>& getCourses() const;

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
        const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
        << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

Student::Student(const string& name): name(name) {}

const string& Student::getName() const {
    return name;
}

bool Student::addCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == course) {
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == course) {
            courses[i] = courses[courses.size() - 1];
            courses.pop_back();
            return;
        }
    }
}

const vector<Course*>& Student::getCourses() const {
    return courses;
}

Course::Course(const string& courseName): name(courseName) {}

const string& Course::getName() const {
    return name;
}

bool Course::addStudent(Student* student) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i] == student) {
            return false;
        }
    }
    students.push_back(student);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); ++i) {
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

const vector<Student*>& Course::getStudents() const {
    return students;
}

Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i]->getName() == courseName) {
            return false;
        }
    }
    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string& studentName) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == studentName) {
            return false;
        }
    }
    students.push_back(new Student(studentName));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
    const string& courseName) {
    size_t studentIndex = findStudent(studentName);
    size_t courseIndex = findCourse(courseName);
    if (studentIndex == students.size() || courseIndex == courses.size()) {
        return false;
    }

    if (students[studentIndex]->addCourse(courses[courseIndex])) {
        courses[courseIndex]->addStudent(students[studentIndex]);
        return true;
    }
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    if (courseIndex == courses.size()) {
        return false;
    }
    courses[courseIndex]->removeStudentsFromCourse();
    delete courses[courseIndex];
    courses[courseIndex] = courses[courses.size() - 1];
    courses.pop_back();
    return true;
}

void Registrar::purge() {
    for (size_t i = 0; i < courses.size(); ++i) {
        delete courses[i];
    }
    courses.clear();
    for (size_t i = 0; i < students.size(); ++i) {
        delete students[i];
    }
    students.clear();
}

size_t Registrar::findStudent(const string& studentName) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == studentName) {
            return i;
        }
    }
    return students.size();
}

size_t Registrar::findCourse(const string& courseName) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i]->getName() == courseName) {
            return i;
        }
    }
    return courses.size();
}

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses:" << endl;
    for (size_t i = 0; i < rhs.courses.size(); ++i) {
        os << rhs.courses[i]->getName() << ": ";
        const vector<Student*>& students = rhs.courses[i]->getStudents();
        if (students.size() == 0) {
            os << "No Students";
        }
        else {
            for (size_t j = 0; j < students.size(); ++j) {
                os << students[j]->getName();
                if (j != students.size() - 1) {
                    os << ", ";
                }
            }
        }
        os << endl;
    }
    os << "Students:" << endl;
    for (size_t i = 0; i < rhs.students.size(); ++i) {
        os << rhs.students[i]->getName() << ": ";
        const vector<Course*>& courses = rhs.students[i]->getCourses();
        if (courses.size() == 0) {
            os << "No Courses";
        }
        else {
            for (size_t j = 0; j < courses.size(); ++j) {
                os << courses[j]->getName();
                if (j != courses.size() - 1) {
                    os << ", ";
                }
            }
        }
        os << endl;
    }
    return os;
}

