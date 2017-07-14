//
//  MediumTicketSeller.h
//  homework3
//	group 3

#pragma once
#include "TicketSeller.h"

class MediumTicketSeller : public TicketSeller
{
public:
	static int ticketsSold;
	MediumTicketSeller(string name, seat_matrix* seats);
	virtual int sellTime();
	virtual bool assignSeat(string customerName);
};