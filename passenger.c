/* passenger.c -- simulates a linked list of passengers */
/* Ignacio Poggi, 2023 */

#include <stdio.h>
#include <stdlib.h>
#include "passenger.h"

struct passenger* make_passenger() {
	struct passenger *pax = (struct passenger *)malloc(sizeof(struct passenger));
	
	if (pax == NULL) {
		fprintf(stderr, "Cannot allocate memory for new passenger.\n");
		
		exit(EXIT_FAILURE);
	}
	
	pax->waiting = 0;
	pax->next = NULL;
	
	return pax;
}

void insert_passenger_after(struct passenger *node, struct passenger *new_node) {
	if (node == NULL || new_node == NULL) {
		fprintf(stderr, "One or both passengers are null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	new_node->next = node->next;
	node->next = new_node;
}

void print_passenger(struct passenger *node) {
	if (node != NULL) {
		printf("%d\n", node->waiting);
	} else {
		printf("%s\n", "NULL");
	}
}

void print_passenger_list(struct passenger *first) {
	printf("\n%s \n", "Waiting times:");
	
	struct passenger *curr_pax = first;
	
	while (curr_pax != NULL) {
		printf("%d\n", curr_pax->waiting);
		
		curr_pax = curr_pax->next;
	}
}

void remove_first_passenger(struct passenger **node) {
	if (*node == NULL) {
		fprintf(stderr, "First passenger is null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct passenger *second_pax = (*node)->next;
	
	free(*node);
	*node = second_pax;
}

void clear_passenger_list(struct passenger **first) {
	struct passenger *next_pax = (*first)->next;
	
	while (next_pax != NULL) {
		struct passenger *tmp_pax = next_pax->next;
		
		free(next_pax);
		
		next_pax = tmp_pax;
	}
	
	free(*first);
	*first = NULL;
}

void increment_passenger_list(struct passenger *first) {
	struct passenger *curr_pax = first;
	
	while (curr_pax != NULL) {
		curr_pax->waiting += 1;
		
		curr_pax = curr_pax->next;
	}
}

double average_passenger_list(struct passenger *first) {
	struct passenger *curr_pax = first;
	
	if (curr_pax == NULL) {
		return -1.0;
	}
	
	int total_minutes = 0;
	int total_pax = num_passengers(curr_pax);
	
	while (curr_pax != NULL) {
		total_minutes += curr_pax->waiting;
		
		curr_pax = curr_pax->next;
	}
	
	double avg = (double)total_minutes / total_pax;
	
	return avg;
}

int num_passengers(struct passenger *first) {
	int num = 0;
	
	struct passenger *curr_pax = first;
	
	while (curr_pax != NULL) {
		num++;
		
		curr_pax = curr_pax->next;
	}
	
	return num;
}