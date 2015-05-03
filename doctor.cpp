/*
 * doctor.cpp
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#include"doctor.h"

Doctor::Doctor(){
	name = "0";
	spec = "0";
	room = -1;
}

Doctor::Doctor(string n, string s, int r){
	name = n;
	spec = s;
	room = r;
}

Doctor::~Doctor(){
	name = "0";
	spec = "0";
	room = -1;
}

string Doctor::getDrName(){
	return name;
}

string Doctor::getDrSpec(){
	return spec;
}

int Doctor::getDrRoom(){
	return room;
}

