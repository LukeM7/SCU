/*
Luke Manzitto
11/23/2020
Lab8 - LRU
Implements the LRU algorithm for page replacement
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// Each page is given an age member to help determine which is the oldest
typedef struct {
    int pageno;
    int age;
} ref_page;

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Invalid args\n");
        return -1;
    }
    int i,j,cache_index;
    int cache_size = atoi(argv[1]);
    char page_cache[100];
    int total_faults = 0, total_requests = 0, place_in_array = 0;
    int oldest;
    ref_page cache[cache_size];
    
    // Initializes the cache
    for(i=0;i<cache_size;i++){
        cache[i].pageno = -1;
        cache[i].age = 0;
    }

    while(fgets(page_cache,100,stdin)){
        total_requests++;
        bool in_cache = false;
        int page_num = atoi(page_cache);
        oldest = cache[0].age;
        // Determines whether the fetched page is in the cache. If so, that page's age is reset to 0
        for(i=0;i<cache_size;i++){
            if(cache[i].pageno == page_num){
                for(j=0;j<cache_size;j++){
                    if(cache[j].age < cache[i].age)
                        cache[j].age++; 
                }
                cache[i].age=0;
                in_cache = true;
                break;
            }
        }
        if(!in_cache){
            total_faults++;
            // Increases the age of all elements
            for(i=0;i<cache_size;i++){
                cache[i].age++;
            }
            // The oldest element is replaced
            for(i=0;i<cache_size;i++){
                if(oldest < cache[i].age){
                    oldest = cache[i].age;
                    cache_index = i;
                }
            }
            cache[cache_index].pageno = page_num;
            cache[cache_index].age = 0; // The newest element is given an age of 0
        }
    }
    printf("%d total page faults\t%d total page requests\t%.6f hit rate\n", total_faults, total_requests,(total_requests-total_faults)/(float)total_requests);
    //float fault_rate = (total_faults / (float)total_requests);
    //printf("\t%.6f fault rate\n",fault_rate);
    return 0;
}