/*
Luke Manzitto
11/23/2020
Lab8 - FIFO
Implements the FIFO algorithm for page replacement
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Invalid args");
        return -1;
    }
    int i;
    int cache_size = atoi(argv[1]);
    char page_cache[100];
    int total_faults = 0;
    int total_requests = 0;
    int place_in_array = 0;
    ref_page cache[cache_size];
    
    // Initializes the cache
    for(i=0;i<cache_size;i++) cache[i].pageno = -1;


    while(fgets(page_cache,100,stdin)){
        total_requests++;
        bool in_cache = false;
        int page_num = atoi(page_cache);
        // Checks to see if the fetched page is already in the cache
        for(i=0;i<cache_size;i++){
            if(cache[i].pageno == page_num){
                in_cache = true;
                break;
            }
        }
        // Replaces the appropriate element of the cache with the new page
        if(!in_cache){
            total_faults++;
            cache[place_in_array].pageno = page_num;
            place_in_array = (place_in_array+1)%cache_size;
        }
    }
    
    printf("%d total page faults\t%d total page requests\t%.6f hit rate\n",total_faults,total_requests,(total_requests-total_faults)/(float)total_requests);
    //float fault_rate = (total_faults / (float)total_requests);
    //printf("\t%.6f fault rate\n",fault_rate);
    return 0;
}