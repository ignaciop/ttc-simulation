/* ttc.h -- header file of ttc.c */
/* Elizabeth Patitsas + Ignacio Poggi, 2023 */

#ifndef TTC_H
#define TTC_H

#include "train.h"
#include "station.h"

#define SPADINA 36
#define YONGE 42

#define MAX_POS 82

#define MAX_LOAD 500
#define TRAIN_GAP 5

void advance_time(struct station *kipling, struct train **first);
void passengers_wait(struct station *kipling);
void add_trains(struct train **first);
int num_arriving_passengers(struct station *curr);
void enter_passengers(struct station *kipling);
void load_trains(struct station *kipling, struct train **first); 
void advance_trains(struct station *kipling, struct train **first);
void print_track(struct station *first_station, struct train **first_train, int time, int print_track);

#endif