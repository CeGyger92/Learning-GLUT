// --------------------------------------------------------------------------------------------------------------------
// Developer -- Eddie Gyger																							  *
// Course ----- CS3233																								  *
// Project ---- Homework #3																							  *
// Due Date --- 10/26/2020																							  *
//																													  *
// Do-It-Yourself: This program performs the three fundamental transforms on a given coordinate.					  *
//---------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>
using namespace std;

//Multipy 3x3 Matrix by 1x3 Vector
void calculateVector(float matrix[3][3], float vector[3]) {
	float result[3] = { 0,0,0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
	cout << endl;
	cout << "X: " << vector[0] << endl << endl;
	cout << "Y: " << vector[1] << endl << endl;
	cout << "X prime: " << result[0] << endl << endl;
	cout << "Y prime: " << result[1] << endl << endl;
}

//Take translation input and build translation matrix
void translate(float * vector) {
	float xTranslate;
	float yTranslate;
	system("cls");

	cout << "Enter the value by which to translate the X coordinate: " << endl;
	cin >> xTranslate;
	cout << endl << "Enter the value by which to translate the Y coordinate: " << endl;
	cin >> yTranslate;
	float translateMatrix[3][3] = { 1, 0, xTranslate, 0, 1, yTranslate, 0, 0, 1 };
	cout << "\nTranslated:\n";
	calculateVector(translateMatrix, vector);
}

//Take scale factor input and build scaling matrix
void scale(float * vector) {
	float xScaleFactor;
	float yScaleFactor;
	system("cls");

	cout << "Enter the scale factor for X: " << endl;
	cin >> xScaleFactor;
	cout << "Enter the scale factor for Y: " << endl;
	cin >> yScaleFactor;
	float scaleMatrix[3][3] = {xScaleFactor, 0, 0, 0, yScaleFactor, 0, 0, 0, 1 };
	cout << "\nScaled:\n";
	calculateVector(scaleMatrix, vector);
}

//Take rotation angle input and build rotation matrix
void rotate(float * vector) {
	float theta;
	float PI = 2 * acosf(0.0);
	system("cls");

	cout << "Enter the angle by which you would like to rotate (Theta)" << endl;
	cin >> theta;
	//convert to radians
	theta *= PI / 180.0;
	float rotateMatrix[3][3] = { cosf(theta), (-1 * sinf(theta)), 0, sinf(theta), cosf(theta), 0, 0, 0, 1 };
	cout << "\nRotated:\n";
	calculateVector(rotateMatrix, vector);
}

int main()
{
	float inputVector[3] = { 1,1,1 };
	char input = 'a';

	//Get coordinate
	cout << "Enter the value for X: " << endl;
	cin >> inputVector[0];
	cout << "Enter the value for Y: " << endl;
	cin >> inputVector[1];
	
	//While exit is not chosen display menu and take menu choice input
	while (input != '5') {
		system("cls");
		cout << "Enter the number of the desired operation:\n\n1. Translate\n2. Scale\n3. Rotate\n4. Change Coordinate\n5. Exit\n";
		cin >> input;
		if (input == '1') {
			translate(inputVector);
		}
		else if (input == '2') {
			scale(inputVector);
		}
		else if (input == '3') {
			rotate(inputVector);
		}
		else if (input == '4') {
			system("cls");
			cout << "Enter the value for X: " << endl;
			cin >> inputVector[0];
			cout << "Enter the value for Y: " << endl;
			cin >> inputVector[1];
		}
		else if (input == '5') {
			return 0;
		}
		system("PAUSE");
	}
}