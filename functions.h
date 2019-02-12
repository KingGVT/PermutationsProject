#ifndef functions
#define functions
int fillArr(int**, int);//2
int fX(int**, int, int);//returns a value from the BOTTOM row in the permutations
bool isInjection(int**, int);//3
bool isSurjection(int**, int);//4
bool isPermutation(int**, int);//5
bool isPermutation1(int**, int);//we need to check if the elements from the top row are unique for the function to be injection and for it to work later on the cycle notations
int permutationsCount(int);//6
bool fixedHead(int**, int);//7
int fixedHeadCount(int**, int);//8
bool isID(int**, int);//9
int cyclesCnt(int**, int);//counts the cycles in order to create the rows for the cycle notations
int returnInd(int**, int, int);//returns the index of the BOTTOM row from the permutations array - we use it for the filling of the cycle notations
int returnIndB(bool *, int);//returns the index of the first false element in the false array for the cycle notations
int fillCycles(int**, int**, int, int);//10
int findLengths(int**, int*, int, int);//11
int printCycles(int**, int);//prints the cycles 
int reversedCycles(char *, char **);//12
#endif // !functions
