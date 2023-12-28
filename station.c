/* station.c -- simulates a doubly-linked list of TTC stations */
/* Ignacio Poggi, 2023 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"

#define MAX_NAME_BUFFER 100

struct station* make_station(char *name, int pos) {
	/* Creates a new station node in our doubly-linked list, setting its name and position to name and pos. */
	/* The new node is unlinked (prev and next are both NULL). */
	/* PRE: none */
	/* POST: none */

	struct station *new_node = (struct station*)malloc(sizeof(struct station));
	
	if (new_node == NULL) {
		fprintf(stderr, "Cannot allocate memory for new station.\n");
		
		exit(EXIT_FAILURE);
	}
	
	new_node->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
	
	if (new_node->name == NULL) {
		fprintf(stderr, "Cannot allocate memory for new station name.\n");
		
		exit(EXIT_FAILURE);
	}
	
	strcpy(new_node->name, name);

	new_node->pos = pos;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->passengers = NULL;

	return new_node;
}

int passengers_at_station(struct station *curr_station) {
	/* Number of passengers waiting at a given station, curr_station. If station == NULL, returns 0. */
	/* PRE: none */
	/* POST: none */
	
	int total_pax = 0;

	if (curr_station != NULL && curr_station->passengers != NULL) {
		total_pax = num_passengers(curr_station->passengers);
	}

	return total_pax;
}

void print_station(struct station *current) {
	/* Prints a single station. If current == NULL, prints "No station. \n". */
	/* PRE: none */
	/* POST: none */
	
	if (current == NULL) {
		printf("%s \n", "No station.");
	} else {
		if (current->prev != NULL) {
			printf("%13s -> ", current->prev->name);
		} else {
			printf("%s", "                 ");
		}

		printf("%s (%d)", current->name, num_passengers(current->passengers));
		
		if (current->next != NULL) {
			printf("-> %-13s \n", current->next->name);
		} else {
			printf("%s", "\n");
		}
	}
}

void print_stations(struct station *first) {
	/* Prints all stations in a linked list */
	/* PRE: none */
	/* POST: none */

	printf("\n%s \n", "The stations:");
	
	struct station *curr_station = first;
	
	while (curr_station != NULL) {
		print_station(curr_station);
		
		curr_station = curr_station->next;
	}
}

void insert_station_after(struct station *node, struct station *new_node) {
	new_node->prev = node;

	if (node->next != NULL) {
		new_node->next = node->next;
        node->next->prev = new_node;
    }
    
	node->next = new_node;
}

struct station* read_stations() {
	FILE *station_file = fopen("bloor_line.txt", "r");
	
	if (station_file == NULL) {
		fprintf(stderr, "Cannot read stations input file.\n");
		
		exit(EXIT_FAILURE);
	}
	
	char tmp_st_name[MAX_NAME_BUFFER] = {'0'};
	int tmp_st_pos = 0;
	
	/* Make head and temp stations */
	struct station *new_station = NULL;
	struct station *first_station = NULL;
	struct station *prev_station = NULL;

	while (fscanf(station_file, "%s %d", tmp_st_name, &tmp_st_pos) != EOF) {
		new_station = make_station(tmp_st_name, tmp_st_pos);
		
		if (prev_station != NULL) {
			insert_station_after(prev_station, new_station);
		} else {
			first_station = new_station;
		}
		
		prev_station = new_station;
	}
	
	fclose(station_file);
	
	return first_station;
}

void add_passenger(struct station *curr_station) {
 	if (curr_station == NULL) {
		fprintf(stderr, "Cannot add passenger to NULL station.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct passenger *pax = make_passenger();
	
	if (curr_station->passengers == NULL) {
		curr_station->passengers = pax;
	} else {
		insert_passenger_after(curr_station->passengers, pax);
	}
}

void add_n_passengers(struct station *curr_station, int n) {
	for (int i = 1; i <= n; i++) {
		add_passenger(curr_station);
	}
}

int total_passengers(struct station *first) {
	int total_pax = 0;
	
	struct station *curr_station = first;
	
	while (curr_station != NULL) {
		total_pax += num_passengers(curr_station->passengers);
		
		curr_station = curr_station->next;
	}
	
	return total_pax;
}

double average_wait_time(struct station *first) {
	double avg = 0.0;
	
	int total_wait = 0;
	
	struct station *curr_station = first;
	
	int total_pax = total_passengers(curr_station);
	
	while (curr_station != NULL) {
		int acc_wait = 0;
		
		struct passenger *curr_pax = curr_station->passengers;
		
		while (curr_pax != NULL) {
			acc_wait += curr_pax->waiting;
			
			curr_pax = curr_pax->next;
		}
		
		total_wait += acc_wait;
		
		curr_station = curr_station->next;
	}
	
	avg = (double)total_wait / total_pax;
	
	return avg;
}

struct station* get_station_at_pos(int position, struct station *first) {
	struct station *ret_station = NULL;
	struct station *curr_station = first;
	
	while (curr_station != NULL) {
		if (curr_station->pos == position) {
			ret_station = curr_station;
			
			break;
		}
		
		curr_station = curr_station->next;
	}
	
	return ret_station;
}
    
void remove_all_stations(struct station **first) {
	struct station *next_station = (*first)->next;
	
	while (next_station != NULL) {
		struct station *tmp_station = next_station->next;
		
		free(next_station->name);
		next_station->name = NULL;
		
		if (next_station->passengers != NULL) {
		    clear_passenger_list(&next_station->passengers);
		}
		
		free(next_station);
		
		next_station = tmp_station;
	}
	
	free((*first)->name);
	(*first)->name = NULL;
	
	if ((*first)->passengers != NULL) {
	    clear_passenger_list(&(*first)->passengers);
	}
	
	free(*first);
	*first = NULL;
}