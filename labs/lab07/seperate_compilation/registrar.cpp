#include "registrar.h"
#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
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
            os << *rhs.courses[i] << endl;
        }
        os << "Students:" << endl;
        for (size_t i = 0; i < rhs.students.size(); ++i) {
            os << *rhs.students[i] << endl;
        }
        return os;
    }

}

