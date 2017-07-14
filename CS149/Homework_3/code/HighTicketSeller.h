//
//  HighTicketSeller.h
//  homework3
//	group 3

#pragma once
#include "TicketSeller.h"

class HighTicketSeller : public TicketSeller
{
public:
	static int ticketsSold;
	HighTicketSeller(string name, seat_matrix* seats);
	virtual int sellTime();
	virtual bool assignSeat(string customerName);
};