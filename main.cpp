﻿/*
Branden Lee
CIS 22B
Fall 2017
Assignment E
Problem E3

Used Microsoft Visual Studio 2017

Car class
we use an array of pointers to Car and make
a copy of the users Car objects in the heap.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>      // std::fstream
#include <stdio.h>
using namespace std;

/**************************************************
** Car class
**************************************************/
class Car
{
protected:
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
public:
	Car () { setup ("", 0, "other", false, "NONE"); } //default constructor
	Car (const Car &CarObj) { setup (CarObj.reportingMark, CarObj.carNumber, CarObj.kind, CarObj.loaded, CarObj.destination); } //copy constructor
	Car (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	virtual ~Car () {} // destructor
	void setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit);
	void output ();
	Car & Car::operator=(const Car & carB);
	friend bool Car::operator==(const Car CarObj1, const Car CarObj2);
	virtual void setKind (std::string kindInit);
};

/**************************************************
** FreightCar class
**************************************************/
class FreightCar : public Car
{
public:
	FreightCar () { setup ("", 0, "other", false, "NONE"); } //default constructor
	FreightCar (const FreightCar &CarObj) { setup (CarObj.reportingMark, CarObj.carNumber, CarObj.kind, CarObj.loaded, CarObj.destination); } //copy constructor
	FreightCar (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	~FreightCar () {}
	FreightCar & FreightCar::operator=(const FreightCar & carB);
	virtual void setKind (std::string kindInit);
};

/**************************************************
** PassengerCar class
**************************************************/
class PassengerCar : public Car
{
public:
	PassengerCar () { setup ("", 0, "other", false, "NONE"); } //default constructor
	PassengerCar (const PassengerCar &CarObj) { setup (CarObj.reportingMark, CarObj.carNumber, CarObj.kind, CarObj.loaded, CarObj.destination); } //copy constructor
	PassengerCar (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	~PassengerCar () {}
	PassengerCar & PassengerCar::operator=(const PassengerCar & carB);
	virtual void setKind (std::string kindInit);
};

/**************************************************
** StringOfCars class
**************************************************/

class StringOfCars
{
private:
	Car **carArrayPtr;
	static const int ARRAY_SIZE = 10;
	int carCount;
public:
	StringOfCars () //default constructor
	{
		carArrayPtr = new Car*[ARRAY_SIZE];
		// set all ptrs to zero
		for (int i = 0; i < ARRAY_SIZE; i++)
			carArrayPtr[i] = 0;
		carCount = 0;
	}
	StringOfCars (const StringOfCars* &StringOfCarsObj)  //copy constructor
	{
		carArrayPtr = new Car*[ARRAY_SIZE];
		// set all ptrs to zero
		for (int i = 0; i < ARRAY_SIZE; i++)
			carArrayPtr[i] = 0;
		carCount = 0;
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			push ((*StringOfCarsObj->carArrayPtr[i]));
		}
	}
	~StringOfCars ()
	{ // destructor
		for (int i = 0; i < ARRAY_SIZE; i++)
			delete carArrayPtr[i];
		delete[] carArrayPtr;
	} // destructor

	void output ();
	void push (const Car &CarObj);
	void push (const FreightCar &CarObj);
	void push (const PassengerCar &CarObj);
	void pop (Car &CarObj);
};

/**************************************************
** global functions, and variables
**************************************************/

void input (StringOfCars & StringOfCarsObj);

int main ()
{
	StringOfCars cars;
	input (cars);
	cars.output ();
	//system ("pause");
	return 0;
}

/**************************************************
** Car class method definitions
**************************************************/

/******************* Car::setup *******************
** Puts the car data into the object
**************************************************/
void Car::setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit)
{
	reportingMark = reportingMarkInit;
	carNumber = carNumberInit;
	(*this).setKind (kindInit);
	loaded = loadedInit;
	destination = destinationInit;

}

/********************* Car::output ****************
** Prints the car data in a neat format
**************************************************/
void Car::output ()
{
	// cout << bool will output an integer
	// we create a temporary string to output the bool
	// std::boolalpha can also be used
	string loadedString = (!loaded) ? "false" : "true";
	cout << setw (16) << left << "reportingMark:" << reportingMark << endl
		<< setw (16) << left << "carNumber: " << carNumber << endl
		<< setw (16) << left << "kind: " << kind << endl
		<< setw (16) << left << "loaded: " << loadedString << endl
		<< setw (16) << left << "destination: " << destination << endl << endl;
}

/********************* operator= ******************
** operator over load for Car class assignment =
**************************************************/
Car & Car::operator=(const Car & carB)
{
	setup (carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

	return *this;
}

/********************* Car::setKind ***************
** Sets the car kind
**************************************************/
void Car::setKind (std::string kindInit)
{
	kind = "other";
	if (kindInit == "business" || kindInit == "maintenance")
	{
		kind = kindInit;
	}
}

/**************************************************
** FreightCar class method definitions
**************************************************/

/********************* operator= ******************
** operator over load for Car class assignment =
**************************************************/
FreightCar & FreightCar::operator=(const FreightCar & carB)
{
	setup (carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

	return *this;
}

/**************** FreightCar::setKind *************
** Sets the car kind
**************************************************/
void FreightCar::setKind (std::string kindInit)
{
	kind = "otherFreight";
	if (kindInit == "box" || kindInit == "tank" || kindInit == "flat")
	{
		kind = kindInit;
	}
}

/**************************************************
** PassengerCar class method definitions
**************************************************/

/********************* operator= ******************
** operator over load for Car class assignment =
**************************************************/
PassengerCar & PassengerCar::operator=(const PassengerCar & carB)
{
	setup (carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

	return *this;
}

/**************** FreightCar::setKind *************
** Sets the car kind
**************************************************/
void PassengerCar::setKind (std::string kindInit)
{
	kind = "otherPassenger";
	if (kindInit == "chair" || kindInit == "sleeper")
	{
		kind = kindInit;
	}
}

/******************** operator== ******************
** operator over load for Car class comparison ==
**************************************************/
bool operator==(const Car CarObj1, const Car CarObj2)
{
	if (CarObj1.reportingMark == CarObj2.reportingMark && CarObj1.carNumber == CarObj2.carNumber&& CarObj1.kind == CarObj2.kind&& CarObj1.loaded == CarObj2.loaded&& CarObj1.destination == CarObj2.destination) { return true; }
	return false;
}

/**************************************************
** StringOfCars class method definitions
**************************************************/

/************* StringOfCars::output ***************
** Outputs each car data. Prints "NO cars" if
** StringOfCars is empty.
**************************************************/
void StringOfCars::output ()
{
	if (carCount > 0)
	{
		for (int i = 0; i < carCount; i++)
		{
			cout << "Car #" << i + 1 << endl;
			(*carArrayPtr[i]).output ();
		}
	}
	else
	{
		cout << "NO cars" << endl;
	}
}

/*************** StringOfCars::push ***************
** Puts a Car into the StringOfCars array
**************************************************/
void StringOfCars::push (const Car &CarObj)
{
	if (carCount < ARRAY_SIZE)
	{
		carArrayPtr[carCount] = new Car (CarObj);
		carCount++;
	}
	else
	{
		cout << "string of cars is full";
		exit (EXIT_FAILURE);
	}
}

/*************** StringOfCars::push ***************
** Puts a FreightCar into the StringOfCars array
**************************************************/
void StringOfCars::push (const FreightCar &CarObj)
{
	if (carCount < ARRAY_SIZE)
	{
		carArrayPtr[carCount] = new FreightCar (CarObj);
		carCount++;
	}
	else
	{
		cout << "string of cars is full";
		exit (EXIT_FAILURE);
	}
}

/*************** StringOfCars::push ***************
** Puts a PassengerCar into the StringOfCars array
**************************************************/
void StringOfCars::push (const PassengerCar &CarObj)
{
	if (carCount < ARRAY_SIZE)
	{
		carArrayPtr[carCount] = new PassengerCar (CarObj);
		carCount++;
	}
	else
	{
		cout << "string of cars is full";
		exit (EXIT_FAILURE);
	}
}

/*************** StringOfCars::pop ****************
** Removes the last Car added from the StringOfCars
** assigns removed Car to the argument
**************************************************/
void StringOfCars::pop (Car &CarObj)
{
	if (carCount > 0)
	{
		CarObj = Car ((*carArrayPtr[carCount - 1]));
		delete carArrayPtr[carCount - 1];
		carArrayPtr[carCount - 1] = 0;
		carCount--;
	}
	else
	{
		cout << "string of cars is empty";
		exit (EXIT_FAILURE);
	}
}

/**************************************************
** global function definitions
**************************************************/

/********************* input **********************
** Reads the car data from the text file "data.txt"
** Prints data from the file
**************************************************/
void input (StringOfCars & StringOfCarsObj)
{
	string carType, carName, reportingMarkInit, kindInit, destinationInit, loadedInit;
	int carNumberInit;
	std::fstream inputFile;
	inputFile.open ("data.txt");
	if (!inputFile)
	{
		cerr << "File could not be opened." << endl;
		exit (1);
	}
	while (inputFile.peek () != EOF)
	{
		while (inputFile.peek () == ' ')
			inputFile.get ();
		// carName added to maintain alignment
		inputFile >> carType >> carName >> reportingMarkInit >> carNumberInit >> kindInit >> loadedInit;
		while (inputFile.peek () == ' ')
			inputFile.get ();
		getline (inputFile, destinationInit);
		// If the carType is not "Car", send an error message and do nothing.
		if (carType == "Car")
		{
			// If the carType is "Car", declare a Car object named temp using the constructor that takes 5 parameters.
			Car temp (reportingMarkInit, carNumberInit, kindInit, loadedInit == "true" ? true : false, destinationInit);
			StringOfCarsObj.push (temp);
		}
		else if (carType == "FreightCar")
		{
			// If the carType is "Car", declare a Car object named temp using the constructor that takes 5 parameters.
			FreightCar temp (reportingMarkInit, carNumberInit, kindInit, loadedInit == "true" ? true : false, destinationInit);
			StringOfCarsObj.push (temp);
		}
		else if (carType == "PassengerCar")
		{
			// If the carType is "Car", declare a Car object named temp using the constructor that takes 5 parameters.
			PassengerCar temp (reportingMarkInit, carNumberInit, kindInit, loadedInit == "true" ? true : false, destinationInit);
			StringOfCarsObj.push (temp);
		}
		// If the carType is not "Car", send an error message and do nothing.
		else cerr << "Not a car, FreightCar, or PassengerCar" << endl;
	}
	inputFile.close ();
}

/* Execution results
Car #1
reportingMark:  CN
carNumber:      819481
kind:           maintenance
loaded:         false
destination:    NONE

Car #2
reportingMark:  SLSF
carNumber:      46871
kind:           business
loaded:         true
destination:    Memphis

Car #3
reportingMark:  AOK
carNumber:      156
kind:           other
loaded:         true
destination:    McAlester

Car #4
reportingMark:  MKT
carNumber:      123456
kind:           tank
loaded:         false
destination:    Fort Worth

Car #5
reportingMark:  MP
carNumber:      98765
kind:           box
loaded:         true
destination:    Saint Louis

Car #6
reportingMark:  SP
carNumber:      567890
kind:           flat
loaded:         true
destination:    Chicago

Car #7
reportingMark:  GMO
carNumber:      7878
kind:           otherFreight
loaded:         true
destination:    Mobile

Car #8
reportingMark:  KCS
carNumber:      7893
kind:           chair
loaded:         true
destination:    Kansas City

Car #9
reportingMark:  PAPX
carNumber:      145
kind:           sleeper
loaded:         true
destination:    Tucson

Car #10
reportingMark:  GN
carNumber:      744
kind:           otherPassenger
loaded:         false
destination:    NONE
*/