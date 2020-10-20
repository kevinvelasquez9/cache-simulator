/* Christian Helgeson and Kevin Velasquez */
/* CSF Fall 2020 */
/* Assignment 3: Cache Simulator */

#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>


void paramCheck(int *p, char *arg, int check) {
    assert(check >= 4 && check < 7);
    if (check == 4) {
        if (strcmp(arg, "write-allocate") == 0) {
            *p += WRITE_ALLOCATE;
        } else if (strcmp(arg, "no-write-allocate") == 0) {
            *p += NO_WRITE_ALLOCATE;
        } else {
            *p = -1;
        }
        return;
    }

    if (check == 5) {
        if (strcmp(arg, "write-through") == 0) {
            *p += WRITE_THROUGH;
        } else if (strcmp(arg, "write-back") == 0) {
            *p += WRITE_BACK;
        } else {
            *p = -1;
        }
        return;
    }

    if (check == 6) {
        if (strcmp(arg, "lru") == 0) {
            *p += LRU;
        } else if (strcmp(arg, "fifo") == 0) {
            *p += FIFO;
        } else {
            *p = -1;
        }
        return;
    }
    return;
}

int read_file(int tagBits, int indexBits, int offsetBits, Scan* cp) {
    // Scan the first char to get an 's' or 'l'
    char instr;
    scanf(" %c", &instr);
    if (instr != 's' && instr != 'l') {
        return 1;
    }
    cp->instr = instr;

    // Scan the second field for the 32-bit address
    char hex_buf[11];
    scanf(" %s", hex_buf);
    uint32_t address = (uint32_t) strtol(hex_buf, NULL, 0);

    // Scan the rest of the line as junk
    char junk[4];
    fgets(junk, 4, stdin);

    uint32_t temp = 32 - offsetBits;
    uint32_t currentMax = UINT32_MAX >> temp;
    // Extract the tag, index, and offset
    cp->offset = address & currentMax;
    address = address >> offsetBits;
    
    temp = 32 - offsetBits;
    currentMax = UINT32_MAX >> temp;
    cp->index = address & currentMax;
    address = address >> indexBits;

    temp = 32 - tagBits;
    currentMax = UINT32_MAX >> temp;
    cp->tag = address & currentMax;

    return 0;
}

int main(int argc, char* argv[]) {
    //Every time we load or store it's one cycle
    //MAin memory. Every time you load from memory, i.e load miss, that is 100 cycles
    assert(argc == 7);
    int param = 0;
    //Checks write parameters and exits program if 
    //incorrect parameters are passed
    for (int i = 4; i < 7; i++) {
        paramCheck(&param, argv[i], i);
        assert(param >= 0);
    }
    assert(param <= 7 && param >= 0);
    //We exit if no-write-allocate and write-back are combined
    if (param < 2) {
        printf("Invalid inputs. Unable to write cache to store\n");
        return -1;
    }

    Cache *cache = create_cache((uint32_t)atoi(argv[1]), (uint32_t)atoi(argv[2]), (uint32_t)atoi(argv[3]));
    
    //int indexBits = log(atoi(argv[1]))/log(2);
    //int offsetBits = log(atoi(argv[3])) / log(2);
    //int tagBits = 32 - indexBits - indexBits;
    
    //Scan holds values from each trace line
    Scan fields;
    int read = 0;
    do {
        read = read_file(cache->tagWidth, cache->indexWidth, cache->offsetWidth, &fields);
        //Loading code
        if (fields.instr == 'l') {
            //Exit program if index in trace is invalid
            if (fields.index > cache->numSets - 1 || fields.index < 0) {
                printf("Invalid trace\n");
                return -1;
            }
            //We are attempting to load, therefore, our totalLoads increase.
            cache->statistics->totalLoads += 1;
            Set *curSet = &cache->sets[fields.index];
            for (int i = 0; i < cache->blocksPerSet; i++) {
                if (curSet->blocks[i].tag == fields.tag) {
                    cache->statistics->loadHits += 1;
                    //LRU == 1, LRU set when param is odd
                    if (param % 2 == 1) { 
                        curSet->blocks[i].timestamp = 0;
                        //TODO: Update the other timestamps/order
                    //don't change timestamp for FIFO
                    } else {
                        //TODO: Not in this loop, BUT UPDATE timestamps for FIFO linearly
                        //First block timestamp 0, second block 1, etc
                    }
                    //breaks from loop. we exit early if tag was pre-loaded into cache
                    break;
                }
                //TODO: Bring if statement below out of for loop and delete it
                if (i == cache->blocksPerSet - 1) {
                    /* This means a cacheMiss was registered */
                    cache->statistics->loadMisses += 1;
                    /* We should now load this data from memory into cache */
                    //TODO: Code to load data into cache //
                    /*First check if there are blocks available */
                    if (curSet->numFilled == cache->blocksPerSet) {
                        unsigned swapIdx = return_oldest_block(curSet, cache->blocksPerSet);
                        curSet->blocks[swapIdx].tag = fields.tag;
                        curSet->blocks[swapIdx].valid = 1;
                        if (curSet->blocks[swapIdx].dirty == 1) {
                           //100 * size of Block/4 
                        }
                        curSet->blocks[swapIdx].dirty = 0;
                        /* Perhaps perform some code if the evicted block was dirty
                        and we need to adjust statistics to register the write */
                        curSet->blocks[swapIdx].timestamp = 0;
                    } else {
                        curSet->blocks[curSet->numFilled].tag == fields.tag;
                        /*TODO: Maybe check tag validity, though not something we can do */
                        curSet->blocks[curSet->numFilled].valid = 1;
                        curSet->numFilled++;
                    }
                    /* Add some function within the cache to update timestamps
                    In blocks. Perhaps consider putting it within the if else statement */
                }
            }
        //Storing code
        } else if (fields.instr == 's') {



        } else { 
                     
            printf("Invalid inputs. Must choose to either load or store\n");
            return -1;
        }
    } while (read == 0);
    
    free_cache(cache);
}
