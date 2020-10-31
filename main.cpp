/* Christian Helgeson and Kevin Velasquez */
/* CSF Fall 2020 */
/* Assignment 3: Cache Simulator */

#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

int read_file(int tagBits, int indexBits, int offsetBits, Scan* cp, Cache *c) {
    /* Scan the first char to get an 's' or 'l'
    /I set char to 'z' since for some reason instr retains its
    /value even after we exit scope. */
    char instr = 'z';
    scanf(" %c", &instr);
    if (instr != 's' && instr != 'l') {
        return 1;
    }
    cp->instr = instr;
    if (cp->instr == 'l') {
        c->statistics->totalLoads += 1;
    } else if (cp->instr == 's') {
        c->statistics->totalStores += 1;
    }

    // Scan the second field for the 32-bit address
    uint32_t address = 0;
    scanf(" %x", &address);
    //char hex_buf[11];
    //scanf(" %s", hex_buf);
    //uint32_t address = (uint32_t) strtol(hex_buf, NULL, 0);

    // Scan the rest of the line as junk
    char junk[4];
    fgets(junk, 2, stdin);
    if (getc(stdin) == '\n') {
        fgets(junk, 1, stdin);
    } else {
        fgets(junk, 2, stdin);
    }

   uint32_t offset = address & (uint32_t) (pow(2.0, (double) offsetBits) - 1);
   address = address >> offsetBits;
   uint32_t index = address & (uint32_t) (pow(2.0, (double) indexBits) - 1);
   address = address >> indexBits;
   uint32_t tag = address & (uint32_t) (pow(2.0, (double) tagBits) - 1);
   cp->offset = offset;
   cp->index = index;
   cp->tag = tag;

    return 0;
}

int powerOf2(uint32_t x) {
    return (x & (x-1)) == 0;
}

int main(int argc, char* argv[]) {
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

    if (powerOf2(cache->numSets) == 0 || powerOf2(cache->blocksPerSet) == 0 || powerOf2(cache->bytesPerBlock) == 0) {
        return -1;
    }
    
    //Explanation from @Shreya Wadhaw
    /* 100 * (bytes in block)/4 to load block from memory (write-allocate)
       100 to write to cache and memory in parallel (write-through) */
    uint32_t memAccessCycles = cache->bytesPerBlock >> 2;
    memAccessCycles *= 100;

    Scan fields;
    int read = 0;
    read = read_file(cache->tagWidth, cache->indexWidth, 
        cache->offsetWidth, &fields, cache);
    while (read == 0) {
        //Exit program if index in trace is invalid
        if (fields.index > cache->numSets - 1) {
            printf("Invalid trace\n");
            return -1;
        }
        //Pointer to set at index. Easier than dereferencing hella structs
        Set *curSet = &cache->sets[fields.index];
        //Loading code
        if (fields.instr == 'l') {
            for (uint32_t i = 0; i < cache->blocksPerSet; i++) {
                //Checks if tag was found
                if (curSet->blocks[i].tag == fields.tag) {
                    cache->statistics->loadHits += 1;
                    cache->statistics->totalCycles += 1;
                    //LRU == 1, LRU set when param is odd
                    if (param & LRU) { 
                        //Rotates array. Block to be evicted at 0. Recent block on right
                        rotate_blocks_left(cache->blocksPerSet, curSet->blocks, curSet->numFilled, i);
                    }
                    //breaks from loop. we exit early if tag was pre-loaded into cache
                    break;
                } else if ((uint32_t) i == cache->blocksPerSet - 1) {
                    /* Load Miss registered */
                    cache->statistics->loadMisses += 1;
                    insert_new_block(cache, curSet, memAccessCycles, fields, false);
                }
                
            }
        //Storing code
        } else if (fields.instr == 's') {
            for (uint32_t i = 0; i < cache->blocksPerSet; i++) {
                if (curSet->blocks[i].tag == fields.tag) {
                    cache->statistics->storeHits += 1;
                    //Check for write through. Param second bit will be set (010) 
                    if (param & WRITE_THROUGH) {
                        //Write through will immediately access memory
                        cache->statistics->totalCycles += 100; //100
                    } else {
                        //Write back set dirty bit in hit block
                        cache->statistics->totalCycles += 1;
                        curSet->blocks[i].dirty = 1;
                    }
                    if (param & LRU) { 
                        //rotate blocks in array
                        rotate_blocks_left(cache->blocksPerSet, 
                            curSet->blocks, curSet->numFilled, i);
                    }
                    break;
                }
                if ((uint32_t) i == cache->blocksPerSet - 1) {
                    /* Store Miss registered */
                    cache->statistics->storeMisses += 1;
                    if (!(param & WRITE_ALLOCATE)) {
                        cache->statistics->totalCycles += 100;
                    } else {
                        bool writeBackBool = false;
                        if (!(param & WRITE_THROUGH)) {
                            writeBackBool = true;
                        } else {
                            cache->statistics->totalCycles += 100;
                        }
                        insert_new_block(cache, curSet, memAccessCycles, fields, writeBackBool);
                    }
                   
                }
                
            }          
        } else {      
            printf("Invalid inputs. Must choose to either load or store\n");
            return -1;
        }
        
        read = read_file(cache->tagWidth, cache->indexWidth, 
            cache->offsetWidth, &fields, cache);
    } //while (read == 0);

    print_statistics(cache);
    
    free_cache(cache);
}
