/*
 * room.cpp
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

#include"room.h"

Room::Room(){
	roomNum = -1;
	docIn = false;
}

Room::Room(int n){
	roomNum = n;
	docIn = false;
}

Room::~Room(){
	roomNum = -1;
	docIn = false;
}

bool Room::hasDr(){
	return docIn;
}

int Room::numWaiting(){
	return waitingRoom.size();
}

int Room::roomNumber(){
	return roomNum;
}

void Room::setRmNum(int r){
	roomNum = r;
}

void Room::drArrive(Doctor& d){
	doctor = &d;
	docIn = true;
}

void Room::drDepart(Doctor* d){
	delete d;
	docIn = false;
}

void Room::patArrive(Patient& p){
	waitingRoom.push(p);
}

Patient* Room::patDepart(){
	Patient temp = waitingRoom.front();
	Patient* cured = &temp;
	waitingRoom.pop();
	return cured;
}

//Patient* Room::getPatient(){
//	Patient temp = waitingRoom.front();
//	Patient* patInfo = &temp;
//	return patInfo;
//}

Doctor* Room::getDoctor(){
	return doctor;
}
