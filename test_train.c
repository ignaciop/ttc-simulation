/* test_train.c -- test cases for train.c */
/* Elizabeth Patitsas; January 22, 2013 */

#include <stdio.h>
#include <stdlib.h>
#include "train.h"

int main(void) {

	/* Test 1: make and print some trains */
	struct train *first = make_train(0, 16);
	print_train(first); /* this should print Train 0 at 16 */

	/* Test 2: test contains */
	printf("%d\n", contains_train_id(NULL, 0)); /* should be 0 */
	printf("%d\n", contains_train_id(first, 0)); /* should be 1 */
	printf("%d\n", contains_train_id(first, 5)); /* should be 0 */

	/* Test 3: prepend train to list */
	int max = 5;
	
	for(int i = max; i > 0; i--) {
		prepend_train(&first, make_train(max - i + 1, 3 * i));
	}

	print_train(first->next); /* should be: Train 4 at 6; next is 3 at 9 */
	print_train(first->next->next); /* should be: Train 3 at 9; next is 2 at 12 */
	print_train(first->next->next->next); /* should be: Train 2 at 12; next is 1 at 15 */
	
	/* the following lines test asserts; (un)comment them one by one
	prepend_train(&first, make_train(4, 10)); // should abort as id=4 taken
	prepend_train(&first, make_train(0, 12)); // should abort as train in pos=12
	prepend_train(&(first->next), make_train(0, 5)); // should abort as out of order
    */

	/* Test 4: print trains */
	print_trains(first);
	/* This should print:
		---------- The trains: ---------- 
		Train 5 at 3; next is 4 at 6
		Train 4 at 6; next is 3 at 9
		Train 3 at 9; next is 2 at 12
		Train 2 at 12; next is 1 at 15
		Train 1 at 15; next is 0 at 16
		Train 0 at 16
	*/	

	/* Test 5: can advance */
	prepend_train(&first, make_train(6, 2));
	printf("%d\n", can_advance(first, 0)); /* should be 0 */
	printf("%d\n", can_advance(first, 5)); /* should be 0 */
	printf("%d\n", can_advance(first->next, 0)); /* should be 1 */
	printf("%d\n", can_advance(first->next, 3)); /* should be 0 */
	
	/* check asserts -- comment/uncomment these one by one
	printf("%d\n", can_advance(first, -1) ); // should abort
	printf("%d\n", can_advance(NULL, 0) ); // should abort
	*/

	/* Test 6: advance train */
	advance_train(first, 10); /* shouldn't advance */
	advance_train(first->next, 0); /* should advance */
	advance_train(first->next, 0); /* shouldn't advance */
	advance_train(first->next->next, 15); /* shouldn't advance */
	print_trains(first);
	/* This should print:
		---------- The trains ---------- 
		Train 6 at 2; next is 5 at 5
		Train 5 at 5; next is 4 at 6
		Train 4 at 6; next is 3 at 9
		Train 3 at 9; next is 2 at 12
		Train 2 at 12; next is 1 at 15
		Train 1 at 15; next is 0 at 16
		Train 0 at 16
	*/

	/* Test 7: num trains */
	printf("%d\n", num_trains(first)); /* should be 7 */
	printf("%d\n", num_trains(NULL)); /* should be 0 */

	/* Test 8: avg distance between trains */
	printf("%lf\n", avg_train_dist(first)); /* should be 1.333333 */
	printf("%lf\n", avg_train_dist(NULL)); /* should be 0.0000 */

	/* Test 9: remove train */
	remove_train_after(first);
	remove_train_after(first->next);
	print_trains(first);
	/* This should print:
		---------- The trains ---------- 
		Train 6 at 2; next is 4 at 6
		Train 4 at 6; next is 2 at 12
		Train 2 at 12; next is 1 at 15
		Train 1 at 15; next is 0 at 16
		Train 0 at 16
	*/

	/* Test 10: remove all trains */
	clear_all_trains(&first);
	print_trains(first);
	/* This should print:
		---------- The trains ---------- 
	*/

	return EXIT_SUCCESS;
}