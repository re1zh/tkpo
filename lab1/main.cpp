#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <format>

using namespace std;

class Person {
    public:
        explicit Person(const string &name) : name(name) {}
        string getName() const{
            return name;
        }
    private:
        string name;
};

class Course {
    public:
        explicit Course(const string& name) : name(name) {}
        string getName() const {
            return name;
        }
    private:
        string name;
};

class Grade {
    public:
        Grade(const string& courseName, const int score) : courseName(courseName), score(score) {}
        string getGradeInfo() const {
            return "Курс: " + courseName + ", оценка: " + to_string(score);
        }
    private:
        string courseName;
        int score;
};

class Student : public Person {
    public:
        explicit Student(const string& name) : Person(name) {}
        void enroll(Course& course) {
            enrolledCourses.push_back(&course);
        }
        vector<Course*> getCourses() const{
            return enrolledCourses;
        }
    private:
        vector<Course*> enrolledCourses;
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
                cout << "Оценки студента " << studentName << ": " << endl;
                for (const Grade& grade : it->second) {
                    cout << grade.getGradeInfo() << endl;
                }
                cout << endl;
            } else {
                cout << "Для " << studentName << " оценки не найдены" << endl;
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
    Archive::getInstance().saveGrade(student2.getName(), teacher2.assignGrade(urpo, 70));

    Archive::getInstance().printGrades("Олег Едисеев");
    Archive::getInstance().printGrades("Иван Кубанов");
}

void testConsoleApp() {
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;

    int numTeachers, numCourses, numStudents;

    cout << "----------------Факультатив----------------" << endl;

    cout << "Введите количество преподавателей: "; cin >> numTeachers;
    for (int i = 0; i < numTeachers; ++i) {
        string teacherName;
        cout << "Введите имя преподавателя " << i + 1 << ": "; cin >> teacherName;
        teachers.emplace_back(teacherName);
    }

    cout << "Введите количество курсов: "; cin >> numCourses;
    for (int i = 0; i < numCourses; ++i) {
        string courseName;
        cout << "Введите название курса "<< i + 1 << ": "; cin >> courseName;
        courses.emplace_back(courseName);
    }

    cout << "Введите количество студентов: "; cin >> numStudents;
    for (int i = 0; i < numStudents; ++i) {
        string studentName;
        cout << "Введите имя студента "<< i + 1 << ": "; cin >> studentName;
        students.emplace_back(studentName);
    }
    cout << endl;

    for (Student& student : students) {
        cout << "Запись студента " << student.getName() << " на курсы" << endl;
        int enroll_qty;

        cout << "Введите количество курсов, на которое хотите записаться: "; cin >> enroll_qty;
        for (int i = 0; i < enroll_qty; ++i) {
            cout << "Выберите номер курса (от 0 до " << numCourses - 1 << "): ";
            int course_i;
            cin >> course_i;

            if (course_i >= 0 && course_i < numCourses) {
                student.enroll(courses[course_i]);
                cout << "Студент " << student.getName() << " записался на курс " << courses[course_i].getName() << endl;
            } else {
                cout << "Неверный номер курса" << endl;
            }
        }
    }

    for (Student& student : students) {
        for (auto course : student.getCourses()) {
            int score;
            cout << "Введите оценку для студента " << student.getName() << " по курсу " << course->getName() << " (0 - 100): ";
            cin >> score;

            Grade grade = teachers[0].assignGrade(*course, score);
            Archive::getInstance().saveGrade(student.getName(), grade);
        }
    }
    cout << endl;

    cout << "----------------Оценки студентов----------------" << endl;
    for (const auto& student : students) {
        Archive::getInstance().printGrades(student.getName());
    }
}

int main() {
    testConsoleApp();
    return 0;
}
