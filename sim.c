/* sim.c - simulates the Bloor-Danforth line of the TTC through ttc.c */
/* Elizabeth Patitsas + Ignacio Poggi, 2023 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ttc.h"

void test_cases_for_students(struct station *kipling, struct train *first);

int main(void) {
	/* Simulate the TTC! */
	/* To keep things consitent, we'll use a predefined seed of 1 */
	srand(1);

	int sim_time = 0;
	char debugging = '0';
	
	do {
		printf("%s ", "Run simulation in debug mode? (1 for yes, any other digit for no):");
		scanf(" %c", &debugging);
	} while (!isdigit(debugging));
	
	/* set up our first station and first two trains */
	struct station *kipling = read_stations();
	struct train *first = make_train(5, 0);
	struct train *second = make_train(0, 5);
	
	first->next = second;

	if (debugging == '1') {
		printf("\n%s\n\n", "Tests for debugging purposes");
		
		test_cases_for_students(kipling, first);
	} else {
		do {
			printf("\n%s ", "Enter a simulation time (in minutes):");
		
			scanf("%d", &sim_time);
		} while (sim_time < 0);
		
		/* we'll be outputting data to a file called data.csv */
		FILE *sim_file = fopen("data.csv","w+");
		
		if (sim_file == NULL) {
			fprintf(stderr, "Cannot write sim output file.\n");
			
			exit(EXIT_FAILURE);
		}
	
		/* if we're not debugging, then simulate! */
		fprintf(sim_file, "time, avg_wait, num_trains, avg_dist\n");
		
		for (int i = 0; i < sim_time; i++) {
			advance_time(kipling, &first);
			
			/* print data every half hour */
			if (i % 30 == 0) {
				fprintf(sim_file, "%d, %lf, %d, %lf\n", i, average_wait_time(kipling), num_trains(first), avg_train_dist(first));
			}
			
			printf("\rProgress: %d of %d min (%d%%)", i + 1, sim_time, ((i + 1) * 100) / sim_time);
		}
		
		printf("%s", "\n\n");
		
		print_track(kipling, &first, sim_time, 1);
		
		fclose(sim_file);
	}

	/* cleanup */
	clear_all_trains(&first);
	
	remove_all_stations(&kipling);
	
	return EXIT_SUCCESS;
}

void test_cases_for_students(struct station *kipling, struct train *first) {
	/* test cases for students */
	
	/* Test 1. enter passengers */
	enter_passengers(kipling);
	
	print_track(kipling, &first, 0, 1); /* if enter_passengers is working you should see something including: */
	/*
		38:      ||  = (n = 227, avg = 0.0) StGeorge
		39:      ||  
		40:      ||  = (n = 241, avg = 0.0) Bay
		41:      ||  
		42:      ||  = (n = 127, avg = 0.0) Yonge
		43:      ||  
		44:      ||  = (n = 72, avg = 0.0) Sherbourne
		45:      ||  
		46:      ||  = (n = 36, avg = 0.0) CastleFrank
		47:      ||  
	*/

	/* Test 2. passengers wait */
	passengers_wait(kipling);
		
	print_track(kipling, &first, 0, 1); /* you should see all passengers have waited one minute */
	
	enter_passengers(kipling);
	
	print_track(kipling, &first, 0, 1); /* now you should see something like: */
	/*
		38:      ||  = (n = 326, avg = 0.7) StGeorge
		39:      ||  
		40:      ||  = (n = 466, avg = 0.5) Bay
		41:      ||  
		42:      ||  = (n = 343, avg = 0.4) Yonge
		43:      ||  
		44:      ||  = (n = 142, avg = 0.5) Sherbourne
		45:      ||  
		46:      ||  = (n = 49, avg = 0.7) CastleFrank
		47:      ||  
	*/
}