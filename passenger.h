/* passenger.h -- header file of passenger.c */
/* Ignacio Poggi, 2023 */

#ifndef PASSENGER_H
#define PASSENGER_H

struct passenger {
	int waiting; /* how many minutes the person has been waiting */
	struct passenger *next;	
};

struct passenger* make_passenger(void);
void insert_passenger_after(struct passenger *node, struct passenger *new_node);
int num_passengers(struct passenger *first);
void print_passenger(struct passenger *node);
void print_passenger_list(struct passenger *first);
void remove_first_passenger(struct passenger **node);
void clear_passenger_list(struct passenger **first);
void increment_passenger_list(struct passenger *first);
double average_passenger_list(struct passenger *first);

#endif