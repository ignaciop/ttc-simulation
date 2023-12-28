/* station.h -- header file of station.c */
/* Elizabeth Patitsas; January 22, 2013 */

#ifndef STATION_H
#define STATION_H

#include "passenger.h"

struct station {
	char *name;
	int pos; /* position on track. Should not change. */
	struct passenger *passengers; /* pointer to first element in list */
	struct station *next; /* next station on the track (east) */
	struct station *prev; /* next station on the track (west) */
};

struct station* make_station(char *name, int pos);
void print_station(struct station *current);
void print_stations(struct station *first);
int passengers_at_station(struct station *curr);
void insert_station_after(struct station *node, struct station *new_node); 
struct station* read_stations(void);
void add_passenger(struct station *curr_station);
void add_n_passengers(struct station *curr_station, int n);
int total_passengers(struct station *first);
double average_wait_time(struct station *first);
struct station* get_station_at_pos(int position, struct station *first);
void remove_all_stations(struct station **first);

#endif