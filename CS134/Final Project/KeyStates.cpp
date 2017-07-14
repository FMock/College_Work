#include"KeyStates.h"

using std::ostringstream;

KeyStates::KeyStates(){
	std::fill_n(states, 100, 0);
}

void KeyStates::zeroAllKeyStates(){
	std::fill_n(states, 100, 0);
}

std::string KeyStates::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "P = " <<  states[19] << "\n";
	return oss.str();
}


