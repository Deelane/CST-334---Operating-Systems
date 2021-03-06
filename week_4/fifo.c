// CST 334 Lab 4  FIFO Page Replacement Simulation File I/O Template

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.c"

typedef struct {
  //to 
  int pageno;
} ref_page;


int main(int argc, char *argv[]){
  int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user 
  //ref_page cache[CACHE_SIZE]; // Cache that stores pages 
  
  struct queue* cache = queue_create();
  
  printf("Cache size: %d\n", CACHE_SIZE);
  
  char pageCache[100]; // Cache that holds the input from test file

  int i;
  int totalFaults = 0; // keeps track of the total page faults
  int requestCount = 0; // keep track of page requests

  /*for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
	 }*/

  //initialise cache queue  
  for (i = 0; i < CACHE_SIZE; i++)
    {
      struct node* currentPage = enqueue(cache, -1);
    }
  queue_traverse(cache);
  printf("\n");

  while (fgets(pageCache, 100, stdin)){
    int page_num = atoi(pageCache); //Stores number read from file as int
    printf("\nlooking up page_num %d...\n", page_num);
    
    //#increment page/block request counter
    requestCount++;
    
    //#check cache for page with page_num
    if (queue_find(cache, page_num))
      {
	printf("Cache hit!\n\n");

	//print unchanged cache state
	printf("Cache state: \n");
	queue_traverse(cache);
	printf("\n");
      }
    else
      {
	//increment totalFaults
	printf("Cache miss. \n\n");
	totalFaults++;
	
	/**update cache via FIFO policy**/
	//enqueue new page 
	enqueue(cache, page_num);
	//dequeue "first in" page
	dequeue(cache);
	
	//print new cache state
	printf("New cache state: \n");
	queue_traverse(cache);
	printf("\n");
      }    
  }
  int totalHit = requestCount - totalFaults;
  printf("%d Total Page Faults\n", totalFaults);
  printf("Hit rate: %f%\n", (float)totalHit/requestCount * 100);
  return 0;

}
