//
//  TicketSeller.cpp
//  homework3
//	group 3

#include "TicketSeller.h"

Timer* TicketSeller::timer = nullptr;
pthread_mutex_t* TicketSeller::cout_mutex = nullptr;
pthread_mutex_t TicketSeller::seats_mutex;
pthread_mutex_t TicketSeller::queue_mutex;

TicketSeller::TicketSeller(string name, seat_matrix* seats) {
	this->name = name;
	this->seats = seats;
	this->start();
	pthread_mutex_init(&queue_mutex, 0);
}

TicketSeller::~TicketSeller() {
	pthread_mutex_destroy(&queue_mutex);
}

void TicketSeller::setCoutMutex(pthread_mutex_t *cout_mutex) {
	TicketSeller::cout_mutex = cout_mutex;
}

void TicketSeller::setTimer(class Timer* timer) {
	TicketSeller::timer = timer;
}

void TicketSeller::start() {
	pthread_t thread;
	pthread_create(&thread, NULL, TicketSeller::sellTickets, this);
}

void TicketSeller::initSeatsMutex() {
	pthread_mutex_init(&TicketSeller::seats_mutex, 0);
}

void TicketSeller::destroySeatsMutex() {
	pthread_mutex_destroy(&TicketSeller::seats_mutex);
}

void* TicketSeller::sellTickets(void *ticketsellerptr) {
	TicketSeller* ticketSeller = static_cast<TicketSeller *>(ticketsellerptr);
	list<Customer>* customerQueue = &(ticketSeller->customerQueue);
	seat_matrix* seats = ticketSeller->seats;
	Timer* timer = ticketSeller->timer;
	
	int time = 0;
	while (time < 60) {
		
		pthread_mutex_lock(&queue_mutex);
		bool empty = customerQueue->empty();
		pthread_mutex_unlock(&queue_mutex);
		if (empty) {
			// if no one in queue, wait one minute
			sleep(1);
			time++;
		}
		else {
			pthread_mutex_lock(&queue_mutex);
			Customer* currentCustomer = &(customerQueue->front());
			pthread_cancel(currentCustomer->waitThread); //Kill 10 second countdown
			customerQueue->pop_front();
			pthread_mutex_unlock(&queue_mutex);
			
			string customerName = currentCustomer->name;
			
			// check for and attempt to assign customer to a seat
			pthread_mutex_lock(&TicketSeller::seats_mutex);
			bool seatAvailable = ticketSeller->assignSeat(currentCustomer->name);
			pthread_mutex_unlock(&TicketSeller::seats_mutex);
			
			if (seatAvailable) {
				
				// spend time selling ticket (this will vary by subclass)
				sleep(ticketSeller->sellTime());
				time += ticketSeller->sellTime();
				string seats_str = "";
				seats_str += timer->currentTime() + " " + customerName + " completed purchase\n";
				
				// print current seat matrix
				seats_str += "Currently assigned seats:\n";
				for (int row = 0; row < 10; row ++) {
					for (int seat = 0; seat < 10; seat++) {
						pthread_mutex_lock(&TicketSeller::seats_mutex);
						string occupant = seats[row][seat] != "" ? seats[row][seat] : "-";
						pthread_mutex_unlock(&TicketSeller::seats_mutex);
						
						seats_str += " " + occupant + " \t";
					}
					seats_str += "\n";
					
				}
				pthread_mutex_lock(cout_mutex);
				cout << seats_str;
				pthread_mutex_unlock(cout_mutex);
			}
			
			// Customer leaves
			pthread_mutex_lock(cout_mutex);
			cout << timer->currentTime() << " " << customerName << " left\n";
			pthread_mutex_unlock(cout_mutex);
		}
	}
	// return nullptr because the compiler said so
	return nullptr;
	
}
