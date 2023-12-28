/* train.c -- implements a linked list of TTC subway trains */
/* Ignacio Poggi, 2023 */

#include <stdio.h>
#include <stdlib.h>
#include "train.h"

struct train* make_train(int iden, int position) {
	struct train *tn = (struct train *)malloc(sizeof(struct train));
	
	if (tn == NULL) {
		fprintf(stderr, "Cannot allocate memory for new train.\n");
		
		exit(EXIT_FAILURE);
	}
	
	tn->id = iden;
	tn->pos = position;
	tn->next = NULL;
	
	return tn;
}

int contains_train_id(struct train *first, int value) {
	int contain_id = 0;
	
	struct train *curr_tn = first;
	
	while (curr_tn != NULL) {
		if (curr_tn->id == value) {
			contain_id = 1;
			
			//break;
		}
		
		curr_tn = curr_tn->next;
	}
	
	return contain_id;
}

int train_at_position(struct train *first, int pos) {
	/* Returns 1 iff there exists a train at position pos (given to students) */
	/* PRE: none */
	/* POST: none */
	
	struct train *curr_tn = first;
	
	int contains_pos = 0;
	
	while (curr_tn != NULL) {
		if(curr_tn->pos == pos) {
			contains_pos = 1;
			
			break;
		}
		
		curr_tn = curr_tn->next;
	}
	
	return contains_pos;
}

void prepend_train(struct train **first, struct train *new_node) {
	if (*first == NULL || new_node == NULL) {
		fprintf(stderr, "One or both trains are null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct train *curr_tn = *first;
	
	int can_prepend = 1;
	
	while (curr_tn != NULL && curr_tn->next != NULL) {
		if ((new_node->pos < curr_tn->pos) && (contains_train_id(curr_tn, new_node->id) == 0)) {
			curr_tn = curr_tn->next;
		} else {
			can_prepend = 0;
			
			break;
		}
	}
	
	if (can_prepend == 1) {
		new_node->next = *first;
		*first = new_node;
	}
}

void print_train(struct train *node) {
	/* Prints a single train, and what it points to (if it points to another train) */
	/* PRE: node != NULL */
	/* POST: none */
	
	if (node == NULL) {
		fprintf(stderr, "Train is null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	printf("Train %d at %d", node->id, node->pos);
	
	if (node->next) {
		printf("; next is %d at %d", node->next->id, node->next->pos);
	}
	
	printf("%s", "\n");
}

void print_trains(struct train *first) {
	printf("\n%s\n", "---------- The trains ----------");
	
	struct train *curr_tn = first;
	
	while (curr_tn != NULL) {
		print_train(curr_tn);
		
		curr_tn = curr_tn->next;
	}
}

int can_advance(struct train *current, int passengers_on_platform) {
	int advance = 0;
	
	if (current == NULL || passengers_on_platform < 0 ) {
		fprintf(stderr, "Train is null or there are 0 passengers on platform.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct train *next_tn = current->next;
	
	if (next_tn == NULL || ((next_tn->pos > current->pos + 1) && (passengers_on_platform == 0))) {
		advance = 1;
	}
	
	return advance;
}

void advance_train(struct train *current, int passengers_on_platform) {
	if (current != NULL && (can_advance(current, passengers_on_platform) == 1)) {
		current->pos += 1;
	}
}

int num_trains(struct train *first) {
	int num = 0;
	
	struct train *curr_tn = first;
	
	while (curr_tn != NULL) {
		num++;
		
		curr_tn = curr_tn->next;
	}
	
	return num;
}

double avg_train_dist(struct train *first) {
	struct train *curr_tn = first;
	
	if (curr_tn == NULL) {
		return 0.0;
	}
	
	int total_distance = 0;
	int total_trains = num_trains(curr_tn);
	
	while (curr_tn != NULL && curr_tn->next != NULL) {
		total_distance += (curr_tn->next->pos - curr_tn->pos - 1);
		
		curr_tn = curr_tn->next;
	}
	
	double avg = (double)total_distance / (total_trains - 1);
	
	return avg;
}

void remove_train_after(struct train *node) {
	if (node == NULL) {
		fprintf(stderr, "Train is null.\n");
		
		exit(EXIT_FAILURE);
	}
	
	struct train *tn_after_after = node->next->next;
	
	free(node->next);
	
	node->next = tn_after_after;
}

void clear_all_trains(struct train **first) {
	struct train *next_tn = (*first)->next;
	
	while (next_tn != NULL) {
		struct train *tmp_tn = next_tn->next;
		
		free(next_tn);
		
		next_tn = tmp_tn;
	}
	
	free(*first);
	*first = NULL;
}