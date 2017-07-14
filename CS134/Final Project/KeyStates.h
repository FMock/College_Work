#ifndef KEYSTATES_H
#define KEYSTATES_H

#include <algorithm> //std::fill
#include<string>
#include<sstream>

class KeyStates{
public:
	KeyStates();
	int states[100];
	void zeroAllKeyStates();
	std::string to_string() const;
};

#endif