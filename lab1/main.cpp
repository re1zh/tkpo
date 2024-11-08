#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Person {
public:
    explicit Person(const string name) : name(name) {}
    const string& getName() const{
        return name;
    }
private:
    string name;
};

class Course {
public:
    explicit Course(const string& name) : name(name) {}
    const string& getName() const{
        return name;
    }
private:
    string name;
};

class Grade {
public:
    Grade(const string& courseName, int score) : courseName(courseName), score(score) {}
    string getGradeInfo() const {
        return "Курс: " + courseName + ", Оценка: " + to_string(score);
    }
private:
    string courseName;
    int score;
};

class Student : public Person {
public:
    explicit Student(const string& name) : Person(name) {}
    void enroll(const Course& course) {
        enrolledCourses.push_back(&course);
    }
    const vector<const Course*>& getCourses() const { 
        return enrolledCourses; 
    }
private:
    vector<const Course*> enrolledCourses;
};

class Teacher : public Person {
public:
    explicit Teacher(const string& name) : Person(name) {}
    static Course createCourse(const string& courseName) {
        return Course(courseName);
    }
    static Grade assignGrade(const Course& course, int score) {
        return Grade(course.getName(), score);
    }
};

class Archive {
public:
    static Archive& getInstance() {
        static Archive instance;
        return instance;
    }
    void saveGrade(const string& studentName, const Grade& grade) {
        studentGrades[studentName].push_back(grade);
    }
    void printGrades(const string& studentName) const {
        if (const auto it = studentGrades.find(studentName); it != studentGrades.end()) {
            cout << "Оценки студента - " << studentName << ":\n";
            for (const Grade& grade : it->second) {
                cout << grade.getGradeInfo() << "\n";
            }
            cout << "\n";
        } else {
            cout << "Для " << studentName << " оценки не найдены.\n";
        }
    }
private:
    Archive() = default;
    map<string, vector<Grade>> studentGrades;
};

void testSystem() {
    Teacher teacher1("Гонтовой Сергей Викторович");
    Teacher teacher2("Пардаев Акбар Анварович");

    Course tkpo = teacher1.createCourse("Технология конструирования программного обеспечения");
    Course urpo = teacher2.createCourse("Управление разработкой программного обеспечения");

    Student student1("Олег Едисеев");
    Student student2("Иван Кубанов");

    student1.enroll(tkpo);
    student1.enroll(urpo);
    student2.enroll(tkpo);

    Archive::getInstance().saveGrade(student1.getName(), teacher1.assignGrade(tkpo, 85));
    Archive::getInstance().saveGrade(student1.getName(), teacher2.assignGrade(urpo, 90));
    Archive::getInstance().saveGrade(student2.getName(), teacher2.assignGrade(urpo, 78));

    Archive::getInstance().printGrades("Олег Едисеев");
    Archive::getInstance().printGrades("Иван Кубанов");
}

int main() {
    testSystem();
    return 0;
}
