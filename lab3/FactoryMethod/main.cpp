#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

class Shape {
    public:
        virtual void draw() = 0;
        virtual ~Shape() = default;
};

class IShape : public Shape {
    public:
        void draw() override {
            cout << " __ " << endl;
            cout << "|__|" << endl;
            cout << "|__|" << endl;
            cout << "|__|" << endl;
            cout << "|__|" << endl;
            cout << endl;
        }
};

class TShape : public Shape {
public:
    void draw() override {
        cout << " __ __ __ " << endl;
        cout << "|__|__|__|" << endl;
        cout << "   |__|" << endl;
        cout << endl;
    }
};

class OShape : public Shape {
public:
    void draw() override {
        cout << " __ __ " << endl;
        cout << "|__|__|" << endl;
        cout << "|__|__|" << endl;
        cout << endl;
    }
};

class JShape : public Shape {
public:
    void draw() override {
        cout << "    __ " << endl;
        cout << "   |__|" << endl;
        cout << " __|__|" << endl;
        cout << "|__|__|" << endl;
        cout << endl;
    }
};

class LShape : public Shape {
public:
    void draw() override {
        cout << " __    " << endl;
        cout << "|__|   " << endl;
        cout << "|__|__ " << endl;
        cout << "|__|__|" << endl;
        cout << endl;
    }
};

class SShape : public Shape {
public:
    void draw() override {
        cout << "    __ __ " << endl;
        cout << "   |__|__|" << endl;
        cout << "|__|__|   " << endl;
        cout << endl;
    }
};

class ZShape : public Shape {
public:
    void draw() override {
        cout << " __ __    " << endl;
        cout << "|__|__|__ " << endl;
        cout << "   |__|__|" << endl;
        cout << endl;
    }
};

class SuperOShape : public Shape {
    void draw() override {
        cout << " __ __ __ " << endl;
        cout << "|__|__|__|" << endl;
        cout << "|__|__|__|" << endl;
        cout << "|__|__|__|" << endl;
        cout << endl;
    }
};

class SuperTShape : public Shape {
    void draw() override {
        cout << " __ __ __ __ __ " << endl;
        cout << "|__|__|__|__|__|" << endl;
        cout << "      |__|      " << endl;
        cout << "      |__|      " << endl;
        cout << "      |__|      " << endl;
        cout << endl;
    }
};

class ShapeFactory {
public:
    virtual Shape* createShape() = 0;
    virtual ~ShapeFactory() = default;
};

class RandomShapeFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        int rnd = rand() % 9;
        switch (rnd) {
            case 0: return new TShape();
            case 1: return new IShape();
            case 2: return new JShape();
            case 3: return new LShape();
            case 4: return new SShape();
            case 5: return new ZShape();
            case 6: return new OShape();
            case 7: return new SuperOShape();
            case 8: return new SuperTShape();
        }
        return nullptr;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    ShapeFactory* factory = new RandomShapeFactory();

    for (int i = 0; i < 12; ++i) {
        Shape* shape = factory->createShape();
        shape->draw();
        sleep(2);
        delete shape;
    }
    delete factory;

    return 0;
}
