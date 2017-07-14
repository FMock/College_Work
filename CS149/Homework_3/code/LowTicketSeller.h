//
//  LowTicketSeller.h
//  homework3
//	group 3

#pragma once
#include "TicketSeller.h"

class LowTicketSeller : public TicketSeller
{
public:
	static int ticketsSold;
	LowTicketSeller(string name, seat_matrix* seats);
	virtual int sellTime();
	virtual bool assignSeat(string customerName);
};