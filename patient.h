/*
 * patient.h
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#ifndef PATIENT_H_
#define PATIENT_H_

#include<string>

using namespace std;

class Patient{
public:
	Patient();
	Patient(string n, string s, int a);
	~Patient();

	string getName();
	string getSpec();
	int getAge();
	int getRoom();

	void setRoom(int r);

private:
	string name;
	string spec;
	int age;
	int room;
};

#endif /* PATIENT_H_ */
