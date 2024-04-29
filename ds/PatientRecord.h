#pragma once
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
class PatientRecord {
	int pid;
	string pname;
	string ad_date;
	string d_diagnoses;
	bool admitted;
public:
	PatientRecord()
	{
		pid = 0;
		pname = "\0";
		ad_date = "\0";
		d_diagnoses = "\0";
		admitted = 0;
	}
	PatientRecord(int id,/*const char*/string name, /*const char**/string date, /*const char**/string disease, bool ad)
	{
		if (id > 0)
			pid = id;
		else
			id = 0;
		pname = name;
		d_diagnoses = disease;
		ad_date = date;
		admitted = ad;
	}
	PatientRecord(const PatientRecord& obj)
	{
		this->pname = obj.pname;
		this->ad_date = obj.ad_date;
		this->admitted = obj.admitted;
		this->d_diagnoses = obj.d_diagnoses;
		this->pid = obj.pid;
	}
	void editrecord(int id, string name, string date, string disease, bool ad)
	{
		if (id > 0)
			pid = id;
		else
			id = 0;
		pname = name;
		d_diagnoses = disease;
		ad_date = date;
		admitted = ad;
	}
	void EnterRecord()
	{
		cout << "Enter the Patient ID : ";
		do {
			cin >> pid;
			if (pid <= 0)
				cout << "Enter again : ";
		} while (pid <= 0);
		cin.ignore();
		cout << "Enter the Patient Name : ";
		getline(cin, pname);
		cout << "Enter the Admission Date : ";
		getline(cin, ad_date);
		cout << "Enter the Disease : ";
		getline(cin, d_diagnoses);
		cout << "Press 'Y' if Admitted" << endl;
		cout << "Press 'N' if Not-Admitted" << endl;
		char temp;
		temp = _getch();
		if (temp == 'y')
			admitted = 1;
		else
			admitted = 0;
	}
	void printrecord()
	{
		cout << "----------------------------------------------" << endl;
		cout << "Name : " << pname << endl;
		cout << "ID : " << pid << endl;;
		cout << "Admission Date : " << ad_date << endl;
		cout << "Disease : " << d_diagnoses << endl;
		cout << "Admitted : ";
		if (admitted)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		cout << "----------------------------------------------" << endl;
	}
	int getid()
	{
		return pid;
	}
	bool getadmitted()
	{
		return admitted;
	}
};
