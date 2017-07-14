//
//  LowTicketSeller.cpp
//  homework3
//	group 3

#include "LowTicketSeller.h"

int LowTicketSeller::ticketsSold = 0;

LowTicketSeller::LowTicketSeller(string name, seat_matrix* seats) : TicketSeller(name, seats) {
	
}

int LowTicketSeller::sellTime() {
	return rand() % 4 + 4;
}

bool LowTicketSeller::assignSeat(string customerName) {
	bool foundSeat = false;
	
	// search seats for an open seat according to the priority
	for(int row = 9; row >= 0; row--)
	{
		if(foundSeat)
			break;
		for(int col = 9; col >=0; col--)
		{
			if(seats[row][col].length() == 0)//empty
			{
				seats[row][col] = customerName;//add customer to matrix
				foundSeat = true;
				break;
			}
			
		}
	}
	
	// if an open seat is found, place the customer there (customerName)
	if (foundSeat) {
		LowTicketSeller::ticketsSold++;
		pthread_mutex_lock(cout_mutex);
		cout << this->timer->currentTime() << " " << customerName << " was assigned a seat\n";
		pthread_mutex_unlock(cout_mutex);
		return true;
	}
	else {
		// else sold out
		pthread_mutex_lock(cout_mutex);
		cout << timer->currentTime() << " " << customerName << " was told the concert is sold out\n";
		pthread_mutex_unlock(cout_mutex);
		return false;
	}
}
