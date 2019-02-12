#include <iostream>
#include "functions.h"
using std::cout;
using std::cin;

int fillArr(int ** arr, int n) {
	//collect the interal of a and b in order to count the number of cols and generate the array
	int a, b;
	cout << "The interval has the following structure [a, b].\nPlease, enter a: ";
	cin >> a;
	cout << "Please, enter b: ";
	cin >> b;
	if (b < a) {
		while (b < a) {
			cout << "The interval is not set correctly, A must be smaller than B!\n";
			cout << "Please, enter a: ";
			cin >> a;
			cout << "Please, enter b: ";
			cin >> b;
		}
	}
	cout << "Interval: [" << a << ", " << b << "]\n";
	//getting the cnt of numbers in the interval
	unsigned cnt = 0;
	for (int i = a; i <= b; i++) {
		cnt++;
	}
	cout << "\n";
	//checking if the cnt of numbers equals to the inputted number of columns 
	if (cnt != n) {
		cout << "The count of numbers in the interval cannot fit\nthe count of colums which you have inputed!\n";
		return 0;
	}
	//collecting the numbers of the first dimention of the array
	cout << "Filling the first dimention: \n";
	for (unsigned i = 0; i < cnt; i++) {
		cout << "Please, input a number in the interval which you have inputed X: ";
		cin >> arr[0][i];
		while (arr[0][i] < a || arr[0][i] > b) {
			cout << "Please, input a VALID number in the interval which you have inputed X: ";
			cin >> arr[0][i];
		}
	}
	cout << "Filling the second dimention: \n";
	//collecting the numbers for the second dimention of the array
	for (unsigned i = 0; i < cnt; i++) {
		cout << "Please, input a number in the interval which you have inputed F(x): ";
		cin >> arr[1][i];
		while (arr[1][i] < a || arr[1][i] > b) {
			cout << "Please, input a VALID number in the interval which you have inputed F(x): ";
			cin >> arr[1][i];
		}
	}
	//print
	cout << " x  ";
	for (unsigned i = 0; i < n; i++) {
		cout << "| " << arr[0][i] << " |";
	}
	cout << "\nf(x)";
	for (unsigned i = 0; i < n; i++) {
		cout << "| " << arr[1][i] << " |";
	}
	cout << "\n";
	//we return 1 so it does not interfear with the 0 that we will return if the columns can't fit the interval
	return 1;
}

int fX(int ** arr, int n, int x) {
	for (unsigned i = 0; i < n; i++) {
		if (arr[0][i] == x) {
			return arr[1][i];
		}
	}
}

bool isInjection(int ** arr, int n) {
	//in order to be injection each element from the TOP row must be contained in the BOTTOM row
	//it is requiered that the elements from the TOP row are unique
	int valueUp, valueDown;
	bool flag = false;
	unsigned i = 0;
	while (i < n) {
		valueUp = arr[0][i];
		for (unsigned j = 0; j < n; j++) {
			valueDown = arr[1][j];
			if (valueUp == valueDown) {
				flag = true;
				break;//we break the iteration because we have found the element and we need to move to the next one
			}
			else {
				flag = false;
			}
		}
		i++;//moving to the next element from the TOP row
	}
	return flag;
}

bool isSurjection(int ** arr, int n) {
	//in order to be surjection it is required the elements from the bottom row to be contained
	//in the upper row - and it is not required that the upper row must be unique
	int valueUp, valueDown;
	bool flag = false;
	unsigned i = 0;
	while (i < n) {
		valueDown = arr[1][i];
		for (unsigned j = 0; j < n; j++) {
			valueUp = arr[0][j];
			if (valueDown == valueUp) {
				flag = true;
				break;//element found - next element
			}
			else {
				flag = false;
			}
		}
		i++;//we move to the next element from the BOTTOM row
	}
	return flag;
}

bool isPermutation(int ** arr, int n) {
	//each element from the BOTTOM row must be unique
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = i + 1; j < n; j++) {
			if (arr[1][i] == arr[1][j]) {//we check if two elements are equal from the BOTTOM row
				return false;
			}
		}
	}
	return true;
}

bool isPermutation1(int ** arr, int n) {
	//each element from the TOP row must be unique for the cycles to work and for the function to be injection
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = i + 1; j < n; j++) {
			if (arr[0][i] == arr[0][j]) {
				return false;
			}
		}
	}
	return true;
}

int permutationsCount(int n) {
	unsigned long count = 1;
	for (int i = 1; i <= n; i++)
	{
		count *= i;
	}
	return count;
}

bool fixedHead(int ** arr, int n) {
	for (unsigned i = 0; i < n; i++) {
		if (arr[0][i] == arr[1][i]) {
			return true;
		}
	}
	return false;
}

int fixedHeadCount(int ** arr, int n) {
	unsigned cnt = 0;
	for (unsigned i = 0; i < n; i++) {
		if (arr[0][i] == arr[1][i]) {
			cnt++;
		}
	}
	return cnt++;
}

bool isID(int ** arr, int n) {
	if (fixedHeadCount(arr, n) == n) {
		return true;
	}
	return false;
}

int returnInd(int ** arr, int n, int el) {
	for (unsigned i = 0; i < n; i++) {
		if (arr[0][i] == el) {
			return i;
		}
	}
}

int cyclesCnt(int ** arr, int n) {
	//we create an array from zeros because we need to save the columns which we have already iterated so that we dont iterate them once more
	int * indexes = new int[n];
	for (unsigned i = 0; i < n; i++) {
		indexes[i] = 0;
	}

	int x, cnt = 0, dV, tmp1, index;

	for (unsigned i = 0; i < n; i++) {//start from the beginning
		x = arr[0][i];//x will be the value wich we get at the beginning of the cycle and which needs to be equal to the
		//tmp1 in order to form a cycle - if x == tmp1 there is a cycle and we increase the counter
		dV = fX(arr, n, x);
		tmp1 = dV;//in case that we dont enter the while cycle
		index = returnInd(arr, n, dV);//we get the index of the current column on which we have found the down value
		indexes[index] = 1;//we fill it with 1 so that we dont iterate it twice
		if (indexes[i] == 0) {//we check if we have already visited that column
			while (x != tmp1) {
				tmp1 = dV;
				dV = fX(arr, n, tmp1);
				index = returnInd(arr, n, dV);//index of visited column 
				indexes[index] = 1;
			}
			cnt++;
		}
	}
	delete[] indexes;
	return cnt;
}

int returnIndB(bool * arr, int n) {
	for (unsigned i = 0; i < n; i++) {
		if (arr[i] == false) {
			return i;
		}
	}
}

int fillCycles(int ** arr, int ** cycl, int n, int cycles) {
	bool * indexes = new bool[n];//bool array to save the columns which we have already visited 
	//fill indexes
	for (unsigned i = 0; i < n; i++) {
		indexes[i] = false;
	}

	int x, vU, vD, rowF = 0, colF = 0, curr = 0, pos;
	bool flag = true;

	for (unsigned end = 0; end < cycles; end++) {
		curr = returnIndB(indexes, n);//curr holds the index of the first found false value in the bool array
		//we need it in order to move on to the next cycle after we have finished this one
		//rowF is for the row that we need to fill
		//colF is for the next column of the current cycle
		x = arr[0][curr];//curr is for current cycle
		cycl[rowF][colF] = x;//we fill the first element
		vU = x;
		flag = true;
		while (flag) {//end of current Cycle notation
			vD = fX(arr, n, vU);
			pos = returnInd(arr, n, vD);
			if (indexes[pos] == false) {//we check if we have already been there and we fill it with true because we are currently there 
				indexes[pos] = true;//we do it because we need to change the CURR value 
			}
			colF++;
			if (vD != x) {
				cycl[rowF][colF] = vD;
				vU = vD;
			}
			if (x == vD) {
				flag = false;//end of while cycle and end of current cycle notation
				rowF++;//next row in cycles
				colF = 0;
			}
		}
	}
	//print the array of cycles 
	cout << "The array with the cycles is:\n";
	for (unsigned i = 0; i < cycles; i++) {
		for (unsigned j = 0; j < n; j++) {
			cout << cycl[i][j] << " ";
		}
		cout << "\n";
	}
	delete[] indexes;
	return 0;
}

int findLengths(int ** arr, int * len, int cols, int cycles) {
	unsigned cnt = 0;
	for (unsigned i = 0; i < cycles; i++) {
		for (unsigned j = 0; j < cols; j++) {
			if (arr[i][j] != 0) {//we have filled the master array with zeros and we count the elements while we reach zero
				cnt++;
			}
		}
		len[i] = cnt;
		cnt = 0;
	}
	return 0;
}

int printCycles(int ** cycles, int lenCnt) {
	bool flag = true;
	unsigned currRow = 0, currCol = 0;
	cout << "The cycles are: \n";
	for (unsigned i = 0; i < lenCnt; i++) {
		cout << "(";//begining of the current cycle
		while (flag) {
			cout << cycles[currRow][currCol] << ((cycles[currRow][currCol + 1] == 0) ? ")" : " ");//we check if the next element is zero and if it is we print ) else we print space
			currCol++;
			if (cycles[currRow][currCol] == 0) {
				flag = false;
				currCol = 0;
			}
		}
		flag = true;
		currRow++;
	}
	return 0;
}

int reversedCycles(char * cycleStr, char ** result) {
	unsigned colF = 0, j = 0, cnt = 0, curr = 0;
	//we fill the TOP row
	while (cycleStr[j] != '\0') {
		if (cycleStr[j] >= 48 && cycleStr[j] <= 57) {
			result[0][colF] = cycleStr[j];
			cnt++;
			colF++;
		}
		else if (cycleStr[j] == ')' && cycleStr[j + 1] == '(') {//if we have and of current cycle and start of next one we fill the array with | to be more readable 
			//and to be able to fill the BOTTOM row
			result[0][colF] = '|'; 
			cnt++;
			colF++;
		}
		j++;
	}
	/*
	for (unsigned i = 0; i < 2; i++) {
	for (unsigned j = 0; j < cnt; j++) {
	cout << result[i][j] << "  ";
	}
	cout << "\n";
	}
	*/
	//cout << cnt << "\n";
	// we fill the BOTTOM row
	colF = 0;
	curr = 0;
	int s = cnt;
	bool flag = true;
	while (flag) {
		if (result[0][colF] != '|') {
			result[1][colF] = result[0][colF + 1];//we need to fill the value which is next to the end value of the cycle 
			colF += 1;
		}
		else {
			result[1][colF - 1] = result[0][curr];//we take the beginning value and the cycle has ended
			colF++;
			curr = colF;
			if (result[0][colF] == '|') {
				flag = false;
			}
		}

	}
	cout << "\nThe cycles which we entered into the begining to table:\n";
	for (unsigned i = 0; i < 2; i++) {
		for (unsigned j = 0; j < s; j++) {
			cout << result[i][j] << "  ";
		}
		cout << "\n";
	}
	return 0;
}
