/*
Luke Manzitto
11/23/2020
Lab8 - Second Chance
Implements the second chance algorithm for page replacement
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

//contains page number and whether the page has a second chance
typedef struct{
    int pageno;
    bool second_chance;
} ref_page;

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Invalid args\n");
        return -1;
    }
    int i;
    int cache_size = atoi(argv[1]);
    char page_cache[100];
    int total_faults = 0, total_requests = 0, place_in_array = 0;
    ref_page cache[cache_size];

    // Initializes the cache
    for(i=0;i<cache_size;i++){
        cache[i].pageno = -1;
        cache[i].second_chance = false;
    }

    while(fgets(page_cache,100,stdin)){
        total_requests++;
        int page_num = atoi(page_cache);
        bool in_cache = false;
        // checks whether the fetched page exists in the cache. If so, that page is given a second chance
        for(i=0;i<cache_size;i++){
            if(cache[i].pageno == page_num){
                cache[i].second_chance = true; // second chance marked
                in_cache = true;
                break;
            }
        }
        if(!in_cache){
            total_faults++;
            // finds the index of the cache where the element does not have a second chance
            for(i=place_in_array;i<cache_size;i++){
                if(cache[i].second_chance == true){ // if the element in index i has a second chance it will not be replaced but will lose its second chance
                    cache[i].second_chance = false;
                    place_in_array++;
                    if(place_in_array == cache_size){
                        place_in_array = 0;
                        i = -1;
                    }
                }
                // replaces the element with the fetched page
                else{
                    cache[place_in_array].pageno = page_num;
                    cache[place_in_array].second_chance = false;
                    place_in_array = (place_in_array+1)%cache_size;
                    break;
                }
            }
        }
    }
    printf("%d total page faults\t%d total page requests\t%.6f hit rate\n", total_faults, total_requests, (total_requests - total_faults) / (float)total_requests);
    //float fault_rate = (total_faults / (float)total_requests);
    //printf("\t%.6f fault rate\n",fault_rate);
    return 0;
}