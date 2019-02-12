#include <iostream>
#include "functions.h"

#define ROWS 2

using std::cout;
using std::cin;

int main()
{
	//cin.getline causes problems if it is called later in the program so we call it here
	const unsigned size = 15;
	char cyclesArr[size];
	cout << "Please, enter a cycle notation: \n";
	cin.getline(cyclesArr, size - 1);
	//cout << cyclesArr << "\n";
	//problem 1
	int cols;
	cout << "Please, enter the number of columns: ";
	cin >> cols;
	while (cols < 0) {
		cout << "Please, enter a VALID number of columns: ";
		cin >> cols;
	}
	int **function = new int *[ROWS];
	for (unsigned i = 0; i < ROWS; i++) {
		function[i] = new int[cols];
	}

	//problem 2
	int fA = fillArr(function, cols); //we check if the number of columns can fit in the interval if not - terminate program
	if (fA == 0) {
		return 0;
	}

	//problem 4
	cout << "Is the function surjection: " << ((isSurjection(function, cols)) ? "yes\n" : "no\n");

	//problem 5
	bool iP = isPermutation(function, cols);
	cout << "Is the function f(x) permutation: " << ((iP) ? "yes\n" : "no\n");
	if (iP == false) {
		return 0; // the function is not permutation and we terminate the program
	}

	//we need to terminate the program if the first row is not a permutation because it will not work later
	bool iP1 = isPermutation1(function, cols);
	if (iP1 == false) {
		cout << "The first line does not contain a unique elements!\n";
		return 0; // the function is not permutation and we terminate the program
	}

	//problem 3 is here because each element must be unique which we check in the permutation function
	cout << "Is the function injection: " << ((isInjection(function, cols)) ? "yes\n" : "no\n");

	//problem 6
	cout << "The count of permutations is " << permutationsCount(cols) << "\n";

	//problem 7
	cout << "Does the permutation have fixed head: " << ((fixedHead(function, cols)) ? "yes\n" : "no\n");

	//problem 8
	unsigned fixedH = fixedHeadCount(function, cols);
	cout << "The count of fixed heads in the permutation is: " << fixedH;

	//problem 9
	cout << "\nIs the permutation ID: " << ((isID(function, cols)) ? "yes\n" : "no\n");

	//problem 10
	unsigned cyclesCntC = cyclesCnt(function, cols) + fixedH;
	cout << "The count of cycles is: " << cyclesCntC << "\n";
	int ** cycles = new int*[cols];
	for (unsigned i = 0; i < cyclesCntC; i++) {
		cycles[i] = new int[cols];
		for (unsigned j = 0; j < cols; j++) {
			cycles[i][j] = 0;
		}
	}

	fillCycles(function, cycles, cols, cyclesCntC);;
	//problem 11
	int * lengths = new int[cyclesCntC];
	findLengths(cycles, lengths, cols, cyclesCntC);
	cout << "The lengths of the cycles are:\n";
	for (unsigned i = 0; i < cyclesCntC; i++) {
		cout << lengths[i] << "\n";
	}
	printCycles(cycles, cyclesCntC);

	char ** result = new char *[ROWS];
	for (unsigned i = 0; i < ROWS; i++) {
		result[i] = new char[15];
		for (unsigned j = 0; j < 14; j++) {
			result[i][j] = '|'; //we fill it with | because it is more readable and we use it for the implementation of the filling logic
		}
	}
	reversedCycles(cyclesArr, result);



	//deleteing the arrays
	for (unsigned i = 0; i < ROWS; i++) {
		delete[] result[i];
	}
	result = NULL;
	delete[] lengths;
	for (unsigned i = 0; i < ROWS; i++) {
		delete[] function[i];
	}
	delete[] function;
	function = NULL;

	for (unsigned i = 0; i < cyclesCntC; i++) {
		delete[] cycles[i];
	}
	delete[] cycles;
	cycles = NULL;
	return 0;
}
