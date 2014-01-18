#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "tools.h"


using namespace std;

int randomInt (int maxNum)
{
	srand ( unsigned ( time(0) ) );
	return rand()%maxNum;
	//return maxNum;
}
