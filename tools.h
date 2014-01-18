#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>

#ifndef __TOOLS_H__
#define __TOOLS_H__


using namespace std;

int randomInt (int maxNum);

template<typename T>
T StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
};

template<typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
};

#endif
