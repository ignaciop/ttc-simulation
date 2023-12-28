/* train.h -- header file of train.c */
/* Ignacio Poggi, 2023 */

#ifndef TRAIN_H
#define TRAIN_H

struct train {
    int id; /* id number of the train */
    int pos; /* position on track in km */
    struct train *next; /* a pointer to the next train */
};

int contains_train_id(struct train *first, int value);
struct train* make_train(int iden, int position);
void prepend_train(struct train **first, struct train *new_node);
void print_train(struct train *node);
void print_trains(struct train *first);
int can_advance(struct train *current, int passengers_on_platform);
void advance_train(struct train *current, int passengers_on_platform);
int num_trains(struct train *first);
double avg_train_dist(struct train *first);
void remove_train_after(struct train *node);
void clear_all_trains(struct train **first);
struct train* get_last_train(struct train *first);
int train_at_position(struct train *first, int pos);

#endif