//
//  MediumTicketSeller.cpp
//  homework3
//	group 3

#include "MediumTicketSeller.h"

int MediumTicketSeller::ticketsSold = 0;

MediumTicketSeller::MediumTicketSeller(string name, seat_matrix* seats) : TicketSeller(name, seats) {
	
}

int MediumTicketSeller::sellTime() {
	return rand() % 3 + 2;
}

bool MediumTicketSeller::assignSeat(string customerName) {
	bool seatFound = false;
	// search seats for an open seat according to the priority
	int c = 19;
	int oldRow = 0;
	
	for(int row = 4; 20%c >= 0;)
	{
		oldRow = row;
		
		if(seatFound)
			break;
			
		for(int col = 0; col < 10; col++)
		{
				if(seats[row][col].length() == 0)//empty
				{
					seats[row][col] = customerName; //add customer to matrix
					seatFound = true;
					break;
				}
		}
		
		if((20%c)%2 == 0)
		{
				row -= 20%c;
		}
		else
		{
				row += 20%c;
		}
		c--;
		
		if(oldRow == row)
			break;
	}
	
	// if an open seat is found, place the customer there (customerName)
	if (seatFound) {
		MediumTicketSeller::ticketsSold++;
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
