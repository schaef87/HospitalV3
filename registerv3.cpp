/*
 * registerv3.cpp
 *
 *  Created on: May 2, 2015
 *      Author: Justin
 */

// ********************************************************************************************
//                                   POINTER REMINDER!
//
//            I'll give u an example: int q=12; int *p=&q; int *pp; pp=&q;
//
//   Technically * and & do not hold for anything since they both operate on variables.
//               * will extract the value while & will extract the address.
//                The best way to dig the magic of pointers up is to debug.
//
//***********************************************************************************************

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

#include"room.h"

using namespace std;

void doctorCI();
void doctorCO();
void patientCI();
void patientAutoCI(Patient p);
void patientCO();
string specList();

vector<Room> rooms;

ofstream file;

bool once = false;

int main(){
	file.open("messages.out");

	char levelIO;
	char checkIO;

	while(once == false){
		for(int x = 0;x<25;x++){
			Room temp(x);
			rooms.push_back(temp);

			if(x>=24){
				once = true;
			}
		}
	}

	do{
		cout << "Wecome! Please follow our guided check-in process" << endl;
		cout << endl;
		cout << "Please type \"D\" if you are a doctor, or \"P\" if you are a patient." << endl;
		file << "Please type \"D\" if you are a doctor, or \"P\" if you are a patient." << endl;

		cin >> levelIO;
		levelIO = toupper(levelIO);

		while (levelIO != 'D' && levelIO != 'P'){
			cout << "Invalid selection. Please try again." << endl;
			cin >> levelIO;
			levelIO = toupper(levelIO);
		}

		if(levelIO == 'D'){
			cout << "Are you checking in our out? \"I\" or \"O\"" << endl;
			cin >> checkIO;
			checkIO = toupper(checkIO);

			while (checkIO != 'I' && checkIO != 'O'){
				cout << "Invalid selection. Please try again." << endl;
				cin >> checkIO;
				checkIO = toupper(checkIO);
			}

			if(checkIO == 'I'){
				doctorCI();
			} else {
				doctorCO();
			}
		} else {
			cout << "Are you checking in our out? \"I\" or \"O\"" << endl;
			cin >> checkIO;
			checkIO = toupper(checkIO);

			while (checkIO != 'I' && checkIO != 'O'){
				cout << "Invalid selection. Please try again." << endl;
				cin >> checkIO;
				checkIO = toupper(checkIO);
			}

			if(checkIO == 'I'){
				patientCI();
			} else {
				patientCO();
			}

		}
	}while(levelIO != 'Q');  //END WHILE LOOP
}// *** END OF MAIN ***

void doctorCI(){
	string name;
	string spec;
	int room;

	cout << "What is your name?" << endl;
	cin >> name;
	spec = specList();
	cout << "What room would you prefer? Choose 1-25" << endl;
	cin >> room;

	while(rooms.at(room-1).hasDr()){
		cout << "Room occupied." << endl;
		cout << "Please select another room. Choose 1-25" << endl;
		cin >> room;
	}

	Doctor *doc = new Doctor(name, spec, room);

	string mess = "Welcome, Dr. " + doc->getDrName() + ".\n\n";
	cout << mess;
	file << mess;

	rooms.at(room-1).drArrive(*doc);   //Assigns doctor to room.
}

void doctorCO(){
	string name;
	Doctor* leaving = 0;
	int tracker;

	cout << "What is your name?" << endl;
	cin >> name;

	test:for(tracker =0;tracker<25;tracker++){
		if(name == rooms.at(tracker).getDoctor()->getDrName()){
			leaving == rooms.at(tracker).getDoctor();
			break;
		} else {
			cout << "Please try again." << endl;
			cin >> name;
			goto test;
		}
	}

	cout << "Thank you. Your patients are being re-assigned." << endl;
	file << "Dr. " << name << " has departed. Patients are being re-assigned." << endl;
	rooms.at(tracker).drDepart(leaving);

	while(rooms.at(tracker).numWaiting() != 0){
		Patient *temp = rooms.at(tracker).getPatient();
		patientAutoCI(*temp);
	}
}

void patientCI(){
	string name;
	string drName;
	string spec;
	string drSpec;
	int track=0;
	int age;

	cout << "What is your name?" << endl;
	cin >> name;
	cout << "What is your age" << endl;
	cin >> age;

	if(age > 15){
		spec = specList();
	} else {
		spec = "PED";
	}

	Patient *pat = new Patient(name, spec, age);

	int docTrack;
	bool defaultFam = false;
	int x = -1;
	while(track != 1 && x < 24){
		x++;
		if(rooms.at(x).hasDr()){
			drName = rooms.at(x).getDoctor()->getDrName();
			drSpec = rooms.at(x).getDoctor()->getDrSpec();
			if (drSpec == "FAM"){
				defaultFam = true;
				docTrack = x;
			}
			if(drSpec == pat->getSpec()){
				defaultFam = false;
				pat->setRoom(x+1);
				rooms.at(x).patArrive(*pat);
				track = 1;
				cout << endl;
				cout << "Welcome, " << pat->getName() << ". You will see Dr. " << drName << " in room #" << x+1 << endl;
				file << pat->getName() << " will see Dr. " << drName << " in room #" << x+1 << endl;
			}
		}
	}

	if(defaultFam == true){
		track = 1;
		pat->setRoom(docTrack+1);
		rooms.at(docTrack).patArrive(*pat);
		cout << endl;
		cout << "Welcome, " << pat->getName() << ". We do not have the specialist you seek." << endl;
		cout << "You will see our on staff Family Practitioner Dr. " << rooms.at(docTrack).getDoctor()->getDrName() << " in room #" << docTrack+1 << endl;
		cout << endl;
		file << pat->getName() << " will see Dr. " << rooms.at(docTrack).getDoctor()->getDrName() << " in room #" << docTrack+1 << endl;
	}

	if(track == 0){
		cout << "We are sorry, " << pat->getName() << " we do not have the required specialist on duty at this moment" << endl;
		file << "We are sorry, " << pat->getName() << " we do not have the required specialist on duty at this moment" << endl;
		cout << endl;
	}
}

void patientAutoCI(Patient p){
	string name;
	string drName;
	string spec;
	string drSpec;
	int track=0;

	int docTrack;
	//	int x = 0;
	for(int x=0;x<25;x++){
		int count = 0;
		if(rooms.at(x).hasDr()){
			drName = rooms.at(x).getDoctor()->getDrName();
			if (rooms.at(x).getDoctor()->getDrSpec() == "FAM"){
				docTrack = x;
			}
			drSpec = rooms.at(x).getDoctor()->getDrSpec();
			if(drSpec == p.getSpec()){
				p.setRoom(x+1);
				rooms.at(x).patArrive(p);
				track = 1;
				cout << "Welcome, " << p.getName() << ". You will see Dr. " << drName << " in room #" << x+1 << endl;
				file << p.getName() << " will see Dr. " << drName << " in room #" << x+1 << endl;
			} else if(drSpec != p.getSpec() && count == 24){
				p.setRoom(docTrack+1);
				rooms.at(docTrack).patArrive(p);
				track = 1;
			}
		}
	}

	if(track ==0){
		int waitList = 0;

		for(int x=0;x<25;x++){
			if(rooms.at(x).hasDr()){
				if(waitList > rooms.at(x).numWaiting()){
					waitList = rooms.at(x).numWaiting();
				}
			}
		}

		cout << p.getName() << ", you have been assigned to Dr. " << rooms.at(waitList).getDoctor()->getDrName() << " in room "<< rooms.at(waitList).roomNumber() << endl;
		file << p.getName() << ", has been relocated to Dr. " << rooms.at(waitList).getDoctor()->getDrName() << " in room " << rooms.at(waitList).roomNumber() << endl;

		rooms.at(waitList).patArrive(p);
	}
}

void patientCO(){
	string name;
	bool nameFound = false;

	cout << "Please enter your name." << endl;
	cin >> name;

	for(int x=0;x<25;x--){
		cout << rooms.at(x).getDoctor()->getDrName() << endl;
		if(name == rooms.at(x).getPatient()->getName()){
			nameFound = true;
			rooms.at(x).patDepart();
			cout << "Have a wonderful day " << name << "!" << endl;
			file << name << " has checked out" << endl;
		}
	}

	if(nameFound == false){
		cout << "Patient not found. Please try again." << endl;
	}
}

string specList(){
	string input;
	string options[12];

	options[0]="PED";
	options[1]="FAM";
	options[2]="INT";
	options[3]="CAR";
	options[4]="SUR";
	options[5]="OBS";
	options[6]="PSY";
	options[7]="NEU";
	options[8]="ORT";
	options[9]="DET";
	options[10]="OPT";
	options[11]="ENT";


	cout << "Please enter a specialty code." << endl;
	cout << endl;
	cout << "Pediatrics\t\tPED" << endl;
	cout << "Family practice\t\tFAM" << endl;
	cout << "Internal medicine\tINT" << endl;
	cout << "Cardiology\t\tCAR" << endl;
	cout << "Surgeon\t\t\tSUR" << endl;
	cout << "Obstetrics\t\tOBS" << endl;
	cout << "Psychiatry\t\tPSY" << endl;
	cout << "Neurology\t\tNEU" << endl;
	cout << "Orthopedics\t\tORT" << endl;
	cout << "Dermatology\t\tDET" << endl;
	cout << "Ophthalmology\t\tOPT" << endl;
	cout << "Ear, Nose, and Throat\tENT" << endl;

	cin >> input;

	transform(input.begin(), input.end(), input.begin(), ::toupper);

	bool hasMatch = false;
	while(hasMatch == false){
		if(input != "PED" && input != "FAM" && input != "INT" && input != "CAR" && input != "SUR" && input != "OBS" &&
				input != "PSY" && input != "NEU" && input != "ORT" && input != "DET" && input != "OPT" && input != "ENT"){
			cout << "Invalid selection. Please try again." << endl;
			cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::toupper);
		} else {
			hasMatch = true;
		}
	}

	return input;
}
