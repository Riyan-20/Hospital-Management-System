

#include <iostream>
#include "PatientRecord.h"
#include "Tree.h"
using namespace std;
int main()
{
	/*--------------------------------- Creating HospitalData Object-------------------------------------------------*/

	HospitalData H1;

	/*----------------------------------- Creating Patient Records to insert in the tree --------------------------------------*/

	PatientRecord P1(1, "Sallahudin Awan", "28-10-2021", "Chronic Glioma", 0);
	PatientRecord P2(2, "Amina Qaiser", "18-11-2021", "Gastritis", 0);
	PatientRecord P3(3, "Umar Khatab", "10-10-2021", "Obesity", 1);
	PatientRecord P4(4, "Seemal Arif", "20-11-2021", "Sore Throat", 1);
	PatientRecord P5(5, "Raida Munir", "23-09-2021", "Depression", 0);
	PatientRecord P6(6, "Asma Ahmad", "24-11-2021", "Cricket Fever", 1);

	/*--------------------------------- Inserting Records -------------------------------------------*/

	H1.Insert(P6);
	H1.Insert(P4);
	H1.Insert(P1);
	H1.Insert(P5);
	H1.Insert(P2);
	H1.Insert(P3);
	cout << endl;
	cout << "\nTree is: " << endl;
	H1.printTree();



	/*-------------------------------- Editing Record with pid '4' --------------------------------------------*/
	H1.Edit(4, "Sallahudin Awan", "28-10-2021", "Nausea", 0);
	cout << "\nPatient Record After Editing:\n";
	H1.Output(4);



	/*-------------------------------- Searching the same record and moving to depth '1' --------------------------------------*/
	PatientRecord SP = H1.Search(4, 1);
	/*-------------------------------- Printing the searched Record --------------------------------------*/
	if (SP.getid() != 0) //0 is the assumed error ID
	{
		cout << "\nSearched record: " << endl;
		SP.printrecord();
	}
	cout << endl << "Updated Tree: " << endl;
	H1.printTree();




	/*-------------------------------- Removing the record with pid '4' ----------------------------------*/
	H1.Remove(4);
	cout << endl << "The Updated Tree after removal Pid = 4: " << endl;
	H1.printTree();






	/*-------------------------------- Printing records of the admitted patients ------------------------------------------*/

	cout << "\nAdmitted Patients Records: " << endl;
	H1.OutputAdmitted();





	/*-------------------------------- Splitting tree ---------------------------------------------*/

	HospitalData H2 = H1.Split();
	cout << endl << "Tree-1: " << endl;
	H1.printTree();
	cout << endl << "Tree-2: " << endl;
	H2.printTree();



	/*-------------------------------- Printing record in tree h1 with pid '2' -----------------------------------------*/
	cout << "\nRecord with pid = 2 In Tree-1 is: " << endl;
	H1.Output(2);

	/*-------------------------------- Printing record in tree h1 with pid '2' -----------------------------------------*/
	cout << "\nRecord with pid = 2 In Tree-2 is: " << endl;
	H2.Output(2);
	cout << H2.wrapper_count();

	system("pause");
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
