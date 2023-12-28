/* test_passenger.c -- test cases for passenger.c */
/* Elizabeth Patitsas; January 22, 2013 */

#include <stdio.h>
#include <stdlib.h>
#include "passenger.h"

int main(void) {

	/* Test 1: create a passenger */
	struct passenger *first = make_passenger();
	struct passenger *fake = NULL;

	/* Test 2: print passengers */
	print_passenger(first); /* should print 0 */
	print_passenger(fake); /* should print a NULL */

	/* Test 3: insert a passenger after first */
	struct passenger *second = make_passenger();
	insert_passenger_after(first, second);
	print_passenger(first->next); /* should print 0 */
	insert_passenger_after(second, make_passenger());
	print_passenger(first->next->next); /* should print 0 */
	print_passenger(second->next); /* should print 0 */

	/* Test 4: print an entire list */
	printf("%s \n", "The list:");
	print_passenger_list(first); /* should print three 0s on separate lines */
	print_passenger_list(NULL); /* should print nothing */

	/* Test 5: increment passenger */
	increment_passenger_list(first);
	increment_passenger_list(first);
	print_passenger_list(first); /* should print three 2s on separate lines */

	struct passenger *new_first = make_passenger();
	struct passenger *current = new_first;

	int i = 0;
	
	while (i < 5) {
		increment_passenger_list(new_first);
		insert_passenger_after(current, make_passenger());
		current = current->next;
		
		i++;
	}

	print_passenger_list(new_first); /* should print 5, 4, 3, 2, 1, 0 on new lines */

	printf("%s", "\n");
	/* Test 6: sum a list */
	printf("%d\n", num_passengers(new_first)); /* should be 6 */
	printf("%d\n", num_passengers(NULL)); /* should be 0 */

	/* Test 7: average a list */
	printf("%lf\n", average_passenger_list(NULL)); /* should be -1 */
	printf("%lf\n", average_passenger_list(first)); /* should be 2.000000 */
	printf("%lf\n", average_passenger_list(new_first)); /* should be 2.500000 */
	
	/* Test 8: remove passenger after */
	remove_first_passenger(&new_first);
	print_passenger_list(new_first); /* should print 4, 3, 2, 1, 0 on new lines */
	remove_first_passenger(&new_first);
	print_passenger_list(new_first); /* should print 3, 2, 1, 0 on new lines */

	/* Test 9: clear a whole list */
	clear_passenger_list(&new_first);
	print_passenger_list(new_first); /* should print nothing */
	clear_passenger_list(&first); 
	print_passenger_list(first); /* should also print nothing */

	return EXIT_SUCCESS;
}