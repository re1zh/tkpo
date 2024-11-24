#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

using namespace std;

class Property {
	public:
    	Property(string type, double area, int residents, int yearBuilt, double wearAndTear);
    	virtual ~Property() = default;
    	virtual double calculateBaseRate() const = 0;
    	string getType() const;
		int getYearBuilt() const;
		int getResidents() const;
		double getArea() const;
	protected:
		string type;
		double area;
		int residents;
		int yearBuilt;
		double wearAndTear;
};

class Apartment : public Property {
	public:
	    Apartment(double area, int residents, int yearBuilt, double wearAndTear);
	    double calculateBaseRate() const override;
};

class Townhouse : public Property {
	public:
	    Townhouse(double area, int residents, int yearBuilt, double wearAndTear);
	    double calculateBaseRate() const override;
};

class Cottage : public Property {
	public:
	    Cottage(double area, int residents, int yearBuilt, double wearAndTear);
	    double calculateBaseRate() const override;
};

#endif //PROPERTY_H
