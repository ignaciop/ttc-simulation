#include <stdio.h>
#include <stdlib.h>
#include "station.h"

int main(void) {
	/* Test 1. Insert station after. */
	struct station *spadina = make_station("Spadina", 0);
	insert_station_after(spadina, make_station("Bay", 1));
	insert_station_after(spadina, make_station("StGeorge", 1));
	print_stations(spadina);
	/* should print
		The stations: 
			         Spadina (0)-> StGeorge     
		      Spadina -> StGeorge (0)-> Bay          
		      StGeorg -> Bay (0)

	*/

	/* Test 2. Read stations in from bloor_line.txt */
	struct station *kipling = read_stations();
	print_stations(kipling);
	/* should print:
		The stations: 
				 Kipling (0)-> Islington     
		      Kipling -> Islington (0)-> RoyalYork     
		    Islington -> RoyalYork (0)-> OldMill       
		    RoyalYork -> OldMill (0)-> Jane          
		      OldMill -> Jane (0)-> Runnymede     
			 Jane -> Runnymede (0)-> HighPark      
		    Runnymede -> HighPark (0)-> Keele         
		     HighPark -> Keele (0)-> DundasWest    
			Keele -> DundasWest (0)-> Lansdowne     
		   DundasWest -> Lansdowne (0)-> Dufferin      
		    Lansdowne -> Dufferin (0)-> Ossington     
		     Dufferin -> Ossington (0)-> Christie      
		    Ossington -> Christie (0)-> Bathurst      
		     Christie -> Bathurst (0)-> Spadina       
		     Bathurst -> Spadina (0)-> StGeorge      
		      Spadina -> StGeorge (0)-> Bay           
		     StGeorge -> Bay (0)-> Yonge         
			  Bay -> Yonge (0)-> Sherbourne    
			Yonge -> Sherbourne (0)-> CastleFrank   
		   Sherbourne -> CastleFrank (0)-> Broadview     
		  CastleFrank -> Broadview (0)-> Chester       
		    Broadview -> Chester (0)-> Pape          
		      Chester -> Pape (0)-> Donlands      
			 Pape -> Donlands (0)-> Greenwood     
		     Donlands -> Greenwood (0)-> Coxwell       
		    Greenwood -> Coxwell (0)-> Woodbine      
		      Coxwell -> Woodbine (0)-> MainStreet    
		     Woodbine -> MainStreet (0)-> VictioriaPark 
		   MainStreet -> VictoriaPark (0)-> Warden        
		VictoriaPark  -> Warden (0)-> Kennedy       
		       Warden -> Kennedy (0)
	*/

	/* Test 3. Append passenger */
	add_passenger(spadina);
	print_stations(spadina); /* Spadina should now have a passenger */
	add_passenger(spadina);
	add_passenger(spadina->next);
	print_stations(spadina); /* Spadina should have 2 passengers; St George 1; Bay 0 */
	increment_passenger_list(spadina->passengers);


	/* Test 4. Add n many passengers */
	add_n_passengers(spadina->next->next, 5);
	add_n_passengers(spadina, 0);
	add_n_passengers(spadina->next, -5);
	print_stations(spadina); /* Spadina should have 2 passengers; St George 1; Bay 5 */

	/* Test 5. Number of passengers waiting at a station. */
	printf("%d\n", total_passengers(spadina)); /* should be 8 */
	printf("%d\n", total_passengers(kipling)); /* should be 0 */
	printf("%d\n", total_passengers(NULL)); /* should be 0 */

	/* Test 6. Average wait time over the entire TTC. */
	increment_passenger_list(spadina->passengers);
	print_passenger_list(spadina->passengers);
	print_passenger_list(spadina->next->passengers);
	print_passenger_list(spadina->next->next->passengers);
	printf("%lf\n", average_wait_time(spadina)); /* should be 0.500000 */
	printf("%lf\n", average_wait_time(kipling)); /* should be -nan */
	printf("%lf\n", average_wait_time(NULL)); /* should be -nan */

	/* Test 7. Station at position */
	print_station(get_station_at_pos(42, kipling)); /* should be Yonge */
	/* assert( !get_station_at_pos(43, kipling)); */ /* should be NULL */

	/* Test 8. Remove all stations */
	remove_all_stations(&kipling); 
	print_stations(kipling); /* prints only "The stations:" */
	remove_all_stations(&spadina); 
	print_stations(spadina); /* prints only "The stations:" */

	return EXIT_SUCCESS;
}