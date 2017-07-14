//
//  Customer.cpp
//  homework3
//  group 3

#include <pthread.h>
#include "Customer.h"

Timer* Customer::timer = nullptr;
pthread_mutex_t* Customer::cout_mutex = nullptr;


Customer::Customer(string name, int arrivalTime, class TicketSeller* ticketSeller) {
	this->name = name;
	this->arrivalTime = arrivalTime;
	this->ticketSeller = ticketSeller;
	this->timer = timer;
	
	pthread_t thread;
	
	// wait until arrival
	pthread_create(&thread, NULL, Customer::wait, this);
	pthread_create(&waitThread, NULL, Customer::checkWait, this);
	
}

void Customer::setCoutMutex(pthread_mutex_t *cout_mutex) {
	Customer::cout_mutex = cout_mutex;
}

void Customer::setTimer(class Timer* timer) {
	Customer::timer = timer;
}

bool Customer::operator==(const Customer &other){
	return this->name == other.name;
}

void* Customer::wait(void *customerptr) {
	
	Customer* customer = static_cast<Customer *>(customerptr);
	Timer* timer = customer->timer;
	
	// wait until arrival
	sleep(customer->arrivalTime);
	
	// upon arrival join ticket seller queue
	pthread_mutex_lock(&(customer->ticketSeller->queue_mutex));
	customer->ticketSeller->customerQueue.push_back(*customer);
	pthread_mutex_unlock(&(customer->ticketSeller->queue_mutex));
	pthread_mutex_lock(cout_mutex);
	cout << timer->currentTime() << " " << customer->name << " arrived\n";
	pthread_mutex_unlock(cout_mutex);
	
	// return nullptr because the compiler said so
	return nullptr;
}

void* Customer::checkWait(void *customerptr){
	Customer* customer = static_cast<Customer *>(customerptr);
	Timer* timer = customer->timer;

	// wait until arrival
	sleep(customer->arrivalTime);

	for(int i = 0; i < 10; i++){
			sleep(1);
		}

	pthread_mutex_lock(&(customer->ticketSeller->queue_mutex));
	customer->ticketSeller->customerQueue.remove(*customer);
	pthread_mutex_unlock(&(customer->ticketSeller->queue_mutex));

	pthread_mutex_lock(cout_mutex);
	cout << timer->currentTime() << " " << customer->name << " departed (impatient)\n";
	pthread_mutex_unlock(cout_mutex);


	return nullptr;
}
