//
//  TicketSeller.h
//  homework3
//	group 3

#pragma once
#include <iostream>
#include <list>
#include <unistd.h>
#include <pthread.h>
#include "Customer.h"
#include "Timer.h"

using namespace std;

typedef string seat_matrix[10];

class Customer;

class TicketSeller {
protected:
	static pthread_mutex_t* cout_mutex;
	static class Timer* timer;
	static pthread_mutex_t seats_mutex;
public:
	string name;
	seat_matrix* seats;
	list<Customer> customerQueue;
	static pthread_mutex_t queue_mutex;
	TicketSeller(string name, seat_matrix* seats);
	~TicketSeller();
	virtual void start();
	virtual int sellTime() = 0;
	virtual bool assignSeat(string customerName) = 0;
	static void setCoutMutex(pthread_mutex_t* cout_mutex);
	static void setTimer(class Timer* timer);
	static void initSeatsMutex();
	static void destroySeatsMutex();
private:
	static void* sellTickets(void*);
};