/*
 * patient.cpp
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#include"patient.h"

Patient::Patient(){
	name = "0";
	spec = "0";
	age = 0;
	room = -1;
}

Patient::Patient(string n, string s, int a){
	name = n;
	spec = s;
	age = a;
	room = -1;
}

Patient::~Patient(){
	name = "0";
	spec = "0";
	age = 0;
	room = -1;
}

string Patient::getName(){
	return name;
}

string Patient::getSpec(){
	return spec;
}

int Patient::getAge(){
	return age;
}

int Patient::getRoom(){
	return room;
}

void Patient::setRoom(int r){
	room = r;
}
