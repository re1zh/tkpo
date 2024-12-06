#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

class Person {
    public:
        explicit Person(const string& name) : name(name) {}
        string getName() const { return name; }
    private:
        string name;
};

class Course {
    public:
        explicit Course(const string& name) : name(name) {}
        string getName() const { return name; }
    private:
        string name;
};

class Student : public Person {
    public:
        explicit Student(const string& name) : Person(name) {}
        void enroll(const Course& course) {
            enrolledCourses.push_back(course);
        }
        const vector<Course>& getCourses() const {
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
        const vector<Course>& getCourses() const {
            return createdCourses;
        }
    private:
        vector<Course> createdCourses;
};

class Grade {
    public:
        Grade(const Student& student, const Course& course, int score)
            : studentName(student.getName()), courseName(course.getName()), score(score) {}
        string getStudentName() const { return studentName; }
        string getCourseName() const { return courseName; }
        int getScore() const { return score; }
    private:
        string studentName;
        string courseName;
        int score;
};

class RecordArchive {
    public:
        void saveRecord(const Teacher& teacher, const Course& course, const Student& student, int score) {
            const Grade grade(student, course, score);
            records[teacher.getName()][course.getName()].push_back(grade);
        }
        const map<string, map<string, vector<Grade>>>& getRecords() const {
            return records;
        }
    private:
        map<string, map<string, vector<Grade>>> records;
};

class View {
    public:
        void showWelcomeMessage() const {
            cout << "----------------Факультатив----------------" << endl;
        }

        void showTeachersAndCourses(const vector<Teacher>& teachers) const {
            for (const auto& teacher : teachers) {
                cout << "Преподаватель: " << teacher.getName() << endl;
                for (const auto& course : teacher.getCourses()) {
                    cout << "  Курс: " << course.getName() << endl;
                }
            }
        }

        void showArchive(const RecordArchive& archive) const {
            const auto& records = archive.getRecords();
            for (const auto& teacherRecord : records) {
                cout << "Преподаватель: " << teacherRecord.first << endl;
                for (const auto& courseRecord : teacherRecord.second) {
                    cout << "   Курс: " << courseRecord.first << endl;
                    for (const auto& grade : courseRecord.second) {
                        cout << "       Студент: " << grade.getStudentName()
                             << ", Оценка: " << grade.getScore() << endl;
                    }
                }
            }
        }

        void showMessage(const string& message) const {
            cout << message << endl;
        }
};


class Controller {
    public:
        Controller(vector<Student>& students, vector<Teacher>& teachers, RecordArchive& archive, const View& view)
            : students(students), teachers(teachers), archive(archive), view(view) {}

        void run() {
            view.showWelcomeMessage();
            inputTeachersCourses();
            inputStudents();
            enrollStudents();
            inputGrades();
            view.showArchive(archive);
        }

    private:
        vector<Student>& students;
        vector<Teacher>& teachers;
        RecordArchive& archive;
        const View& view;

        void inputTeachersCourses() {
            view.showMessage("Введите количество преподавателей: ");
            int numTeachers;
            cin >> numTeachers; cin.ignore();

            for (int i = 0; i < numTeachers; ++i) {
                string teacherName;
                view.showMessage("Введите имя преподавателя " + to_string(i + 1) + ": ");
                getline(cin, teacherName);
                teachers.emplace_back(teacherName);

                view.showMessage("Введите количество курсов для преподавателя: ");
                int numCourses;
                cin >> numCourses; cin.ignore();

                for (int j = 0; j < numCourses; ++j) {
                    string courseName;
                    view.showMessage("Введите название курса: ");
                    getline(cin, courseName);
                    teachers.back().createCourse(courseName);
                }
            }
        }

        void inputStudents() {
            view.showMessage("Введите количество студентов: ");
            int numStudents;
            cin >> numStudents; cin.ignore();

            for (int i = 0; i < numStudents; ++i) {
                string studentName;
                view.showMessage("Введите имя студента: ");
                getline(cin, studentName);
                students.emplace_back(studentName);
            }
        }

        void enrollStudents() {
            for (auto& student : students) {
                for (auto& teacher : teachers) {
                    for (size_t j = 0; j < teacher.getCourses().size(); ++j) {
                        student.enroll(teacher.getCourses()[j]);
                    }
                }
            }
        }

        void inputGrades() {
            for (const auto& teacher : teachers) {
                for (const auto& course : teacher.getCourses()) {
                    for (const auto& student : students) {
                        int grade;
                        view.showMessage("Введите оценку для студента " + student.getName() +
                                         " по курсу " + course.getName() + ": ");
                        cin >> grade;
                        archive.saveRecord(teacher, course, student, grade);
                    }
                }
            }
        }
};

int main() {
    vector<Student> students;
    vector<Teacher> teachers;
    RecordArchive archive;
    View view;

    Controller controller(students, teachers, archive, view);
    controller.run();

    return 0;
}
