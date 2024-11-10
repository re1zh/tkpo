#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

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

class CourseBase {
    public:
        virtual ~CourseBase() = default;
        virtual string getName() const = 0;
};

class Course : public CourseBase {
    public:
        explicit Course(const string& name) : name(name) {}
        string getName() const override { return name; }
    private:
        string name;
};

class Student : public Person {
    public:
        explicit Student(const string& name) : Person(name) {}
        void enroll(const Course& course) {
            enrolledCourses.push_back(course);
        }
        vector<Course> getCourses() const{
            return enrolledCourses;
        }
    private:
        vector<Course> enrolledCourses;
};

class Teacher : public Person {
    public:
        explicit Teacher(const string& name) : Person(name) {}
        void createCourse(const string& courseName) {
            createdCourses.emplace_back(courseName);
        }
        vector<Course> getCourses() const{
            return createdCourses;
        }
    private:
        vector<Course> createdCourses;
};

class Grade {
    public:
        Grade(const Student& student, const Course& course, const int score)
            : studentName(student.getName()), courseName(course.getName()), score(score) {}
        string getStudentName() const { return studentName; }
        string getCourseName() const { return courseName; }
        int getScore() const { return score; }
    private:
        string studentName;
        string courseName;
        int score;
};

class ArchiveBase {
    public:
        virtual ~ArchiveBase() = default;
        virtual void getArchiveInfo() const = 0;
};

class Archive : ArchiveBase {
    public:
        void saveRecord(const Teacher& teacher,  const Course& course, const Student& student, const int score) {
            const Grade grade(student, course, score);
            records[teacher.getName()][course.getName()].push_back(grade);
        }
        void getArchiveInfo() const override {
            for (const auto& teacherRecord : records) {
                cout << "Преподаватель: " << teacherRecord.first << endl;
                for (const auto& courseRecord : teacherRecord.second) {
                    cout << "   Курс: " << courseRecord.first << endl;
                    for (const auto& grade : courseRecord.second) {
                        cout << "       студент: " << grade.getStudentName() << ", оценка: " << grade.getScore() << endl;
                    }
                }
            }
        }
    private:
        map<string, map<string, vector<Grade>>> records;
};


void testConsole() {
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;

    int numTeachers, numStudents;

    cout << "----------------Факультатив----------------" << endl;

    Archive archive;

    cout << "Введите количество преподавателей: ";
    cin >> numTeachers; cin.ignore();
    if (numTeachers > 0) {
        for (int i = 0; i < numTeachers; ++i) {
            string teacherName;
            cout << "Введите имя преподавателя " << i + 1 << ": ";
            getline(cin, teacherName);
            teachers.emplace_back(teacherName);

            int numCourses;
            cout << "Введите количество курсов для преподавателя " << i + 1 << ": ";
            cin >> numCourses; cin.ignore();

            for (int j = 0; j < numCourses; ++j) {
                string courseName;
                cout << "Введите название курса №"<< j + 1 << ": ";
                getline(cin, courseName);
                teachers.back().createCourse(courseName);
            }
        }

        cout << "Введите количество студентов: ";
        cin >> numStudents; cin.ignore();
        for (int i = 0; i < numStudents; ++i) {
            string studentName;
            cout << "Введите имя студента №"<< i + 1 << ": ";
            getline(cin, studentName);
            students.emplace_back(studentName);
        }
        cout << endl;

        for (Student& student : students) {
            cout << "Запись студента " << student.getName() << " на курсы" << endl;

            for (int i = 0; i < teachers.size(); ++i) {
                Teacher& teacher = teachers[i];
                cout << "Преподаватель: " << teacher.getName() << endl;
                const auto& courses = teacher.getCourses();

                for (int j = 0; j < courses.size(); ++j) {
                    cout << "  [" << j + 1 << "] " << courses[j].getName() << endl;
                }
                cout << "Введите номера курсов через пробел для записи студента " << student.getName() << " (0 для пропуска): ";
                string line;
                getline(cin, line);
                stringstream ss(line);
                int courseChoice;
                while (ss >> courseChoice) {
                    if (courseChoice > 0 && courseChoice <= courses.size()) {
                        student.enroll(courses[courseChoice - 1]);
                    }
                }
            }
        }
        cout << endl;

        for (const Teacher& teacher : teachers) {
            const auto& courses = teacher.getCourses();
            for (const Course& course : courses) {
                cout << "Ввод оценок для курса " << course.getName() << " преподавателя " << teacher.getName() << "." << endl;
                for (const Student& student : students) {
                    bool enrolled = false;
                    for (const Course& enrolledCourse : student.getCourses()) {
                        if (enrolledCourse.getName() == course.getName()) {
                            enrolled = true;
                            break;
                        }
                    }
                    if (enrolled) {
                        int grade;
                        cout << "Введите оценку для студента " << student.getName() << " (0 - 100): ";
                        cin >> grade;
                        archive.saveRecord(teacher, course, student, grade);
                    }
                }
            }
        }
        cout << endl;

        cout << "----------------Оценки студентов----------------" << endl;
        archive.getArchiveInfo();
    } else {
        cout << "Кол-во преподавателей не может быть < 0! Введите его заново ";
    }
}

int main() {
    testConsole();
    return 0;
}
