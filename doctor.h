/*
 * doctor.h
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#ifndef DOCTOR_H_
#define DOCTOR_H_

#include<string>

using namespace std;

class Doctor{
public:
	Doctor();
	Doctor(string n, string s, int r);
	~Doctor();

	string getDrName();
	string getDrSpec();
	int getDrRoom();

private:
	string name;
	string spec;
	int room;

};

#endif /* DOCTOR_H_ */
