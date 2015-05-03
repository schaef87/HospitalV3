/*
 * room.h
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#ifndef ROOM_H_
#define ROOM_H_

#include<string>
#include<queue>

#include"doctor.h"
#include"patient.h"

using namespace std;

class Room{
public:
	Room();
	Room(int n);
	~Room();

	bool hasDr();

	int numWaiting();
	int roomNumber();

	void setRmNum(int r);
	void drArrive(Doctor& d);
	void drDepart(Doctor* d);
	void patArrive(Patient& p);

	Patient* patDepart();
	Patient* getPatient();
	Doctor* getDoctor();



private:
	int roomNum;
	bool docIn;
	queue<Patient> waitingRoom;
	Doctor* doctor;
};


#endif /* ROOM_H_ */
