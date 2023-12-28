/* ttc.c - simulates the Bloor-Danforth line of the TTC */
/* Elizabeth Patitsas + Ignacio Poggi, 2023 */

#include <stdio.h>
#include <stdlib.h>
#include "ttc.h"

void advance_time(struct station *kipling, struct train **first) {
	/* Simulates one minute of the Bloor-Danforth line */
	/* PRE: *kipling, *first, **first all are not null, there is more than one train on the track */
	/* POST: the stations and trains will be altered: trains will advance, stations' passengers will increase/decrease */

	if (kipling == NULL || first == NULL || *first == NULL || (*first)->next == NULL) {
		fprintf(stderr, "There is more than one train on the track.\n");
		
		exit(EXIT_FAILURE);
	}

	/* increment passenger waiting times */
	passengers_wait(kipling);

	/* add trains if appropriate */
	add_trains(first);

	/* passengers arrive */
	enter_passengers(kipling);

	/* load the trains */
	load_trains(kipling, first);

	/* first advance any trains that can move; delete any that advance into position 83 */
	advance_trains(kipling, first);
}

void passengers_wait(struct station *kipling) {
	struct station *curr_station = kipling;
	
	while (curr_station != NULL) {
		if (curr_station->passengers != NULL) {
			increment_passenger_list(curr_station->passengers);
		}
		
		curr_station = curr_station->next;
	}
}

void add_trains(struct train **first) {
	/* adds trains to the track every time the westmost train gets to position = TRAIN_GAP */
	/* PRE: *first != NULL */
	/* POST: first will be altered if a new train is added */
	
	if (*first == NULL) {
		fprintf(stderr, "First train is null.\n");
		
		exit(EXIT_FAILURE);
	}

	/* non-stochastic approach */
	/* if the newest train has gotten to TRAIN_GAP, then add a new one */
	if ((*first)->pos == TRAIN_GAP) {
		/* then we add a new train at pos 0. */
		int id = (*first)->id + TRAIN_GAP;
		
		struct train *new_train = make_train(id, 0);
		
		prepend_train(first, new_train);
	}
}

int num_arriving_passengers(struct station *curr_station) {
	/* Adds a number of new passengers */
	/* If downtown, adds between 1 and 300 passengers; else between 0 and 100. */
	/* PRE: none */
	/* POST: none */

	int max = 100; /* default (non-downtown) */
	int min = 0;

	/* if downtown, adjust the min/max of the random numbers */
	if (curr_station->pos >= SPADINA && curr_station-> pos <= YONGE) {
		max = 300;
		min = 1;
	}

	/* and return a value between (max, min) */
	return (rand() % max + min);
}

void enter_passengers(struct station *kipling) {
	struct station *curr_station = kipling;
	
	while (curr_station != NULL) {
		int pax_to_add = num_arriving_passengers(curr_station);
		
		add_n_passengers(curr_station, pax_to_add);
		
		curr_station = curr_station->next;
	}
}

void load_trains(struct station *kipling, struct train **first) {
	/* Loads at most MAX_LOAD many passengers from each station that has a train at it */
	/* PRE: none */
	/* POST: stations' passengers will have decreased */

	struct train *curr_train = *first;
	
	while (curr_train != NULL) {
		/* is there a station at this train's position? */
		struct station *curr_station = get_station_at_pos(curr_train->pos, kipling);	

		if (curr_station != NULL) {
			/* then we need to load our train */
			struct passenger **passgrs = &(curr_station->passengers);
			
			int num_passeng = num_passengers(*passgrs);

			if (*passgrs != NULL && num_passeng <= MAX_LOAD) {
				clear_passenger_list(passgrs);
			} else if (*passgrs != NULL) {
				/* remove MAX_LOAD many passengers */
				for(int i = 0; i < MAX_LOAD; i++) {
					remove_first_passenger(passgrs);
				}
			}
		}
	
		curr_train = curr_train->next;
	}
}

void advance_trains(struct station *kipling, struct train **first) {
	/* Advance every train on the track (if it can be advanced) */
	/* PRE: *first != NULL and there is more than one train on the track */
	/* POST: the trains' positions will be incremented */
	
	if (*first == NULL && (*first)->next == NULL) {
		fprintf(stderr, "First and second train are null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct train *curr_train = *first;
	struct train *prev_train = NULL;
	
	while (curr_train != NULL) {
		if (curr_train->pos >= MAX_POS + 1) {
			/* delete the train when it gets to position 83 */
			prev_train->next = NULL;
			
			free(curr_train);
			
			return;
		} else {
			/* otherwise, the train is on the track and we should advance it */
			int num_pass = 0;
			
			struct station *curr_station = get_station_at_pos(curr_train->pos, kipling);	
			
			if (curr_station != NULL) {
				num_pass = num_passengers(curr_station->passengers);
			}

			advance_train(curr_train, num_pass);

			prev_train = curr_train;
			curr_train = curr_train->next;
		}
	}
}

void print_track(struct station *first_station, struct train **first_train, int time, int print_track) {
	/* prints the TTC Bloor-Danforth Track */
	/* PRE: none */
	/* POST: none */

	struct station *curr_station = first_station;
	struct train *curr_train = *first_train;
	
	int i = 0;
	
	while (i <= MAX_POS && curr_station && print_track == 1) {
		printf("%2d: ", i);

		/* print a train */
		if (curr_train != NULL && curr_train->pos == i) {
			printf("   [t%3d] ", curr_train->id);
			
			curr_train = curr_train->next;
		} else {
			printf("     ||  ");
		}

		/* print a station */
		if (curr_station->pos == i) {
			int num_waiting = passengers_at_station(curr_station);
			
			printf("= (n = %d, avg = %.1lf) %s", num_waiting, average_passenger_list(curr_station->passengers), curr_station->name);
			
			curr_station = curr_station->next;
		}

		printf("%s", "\n");
		
		i++;
	}
	
	/* now print some information: average wait time of passengers, number of trains on track, average distance between trains */
	printf("%s\n", "---------- ANALYTICS --------");
	printf("Simulated time elapsed (min): %d \n", time);
	printf("Total number of passengers: %d \n", total_passengers(first_station));
	printf("Average wait time of passengers (in min): %lf \n", average_wait_time(first_station));
	printf("Total number of trains: %d \n", num_trains(*first_train));
	printf("Average distance between trains (in km): %lf \n\n", avg_train_dist(*first_train));
}