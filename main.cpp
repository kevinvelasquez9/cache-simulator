/* Christian Helgeson and Kevin Velasquez */
/* CSF Fall 2020 */
/* Assignment 3: Cache Simulator */

#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>


int paramCheck(int *p, char *arg, int check) {
    assert(check >= 4 && check < 7);
    if (check == 4) {
        if (strcmp(arg, "write-allocate")) {
            *p += WRITE_ALLOCATE;
        } else if (strcmp(arg, "no-write-allocate")) {
            *p += NO_WRITE_ALLOCATE;
        } else {
            *p = -1;
        }
    }

    if (check == 5) {
        if (strcmp(arg, "write-through")) {
            *p += WRITE_THROUGH;
        } else if (strcmp(arg, "write-back")) {
            *p += WRITE_BACK;
        } else {
            *p = -1;
        }
    }

    if (check == 6) {
        if (strcmp(arg, "lru")) {
            *p += LRU;
        } else if (strcmp(arg, "fifo")) {
            *p += FIFO;
        } else {
            *p = -1;
        }
    }
    return 0;
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

    // Extract the tag, index, and offset
    cp->offset = address & (uint32_t) (pow(2.0, (double) offsetBits) - 1);
    address = address >> offsetBits;
    cp->index = address & (uint32_t) (pow(2.0, (double) indexBits) - 1);
    address = address >> indexBits;
    cp->tag = address & (uint32_t) (pow(2.0, (double) tagBits) - 1);

    return 0;
}

int main(int argc, char* argv[]) {
    assert(argc == 7);
    int param = 0;
    for (int i = 4; i < 7; i++) {
        paramCheck(&param, argv[i], i);
        assert(param >= 0);
    }
    assert(param <= 7);
    if (param < 2) {
        printf("Invalid inputs. Unable to write cache to store\n");
        return -1;
    }

    Cache cache;
    create_cache(uint32_t(atoi(argv[1])), uint32_t(atoi(argv[2])), 
        uint32_t(atoi(argv[3]), cache);
    
    int indexBits = log(atoi(argv[1]))/log(2);
    int offsetBits = log(atoi(argv[3])) / log(2);
    int tagBits = 32 - indexBits - indexBits;

    

    Scan fields;
    int read = 0;
    do {
        read = read_file(tagBits, indexBits, offsetBits, &fields);
        if (fields.instr == 'l') {
    
            if (fields.index > cache->numSets - 1 || fields.index < 0) {
                printf("Invalid trace\n");
                return -1;
            }
            
            cache.statistics->totalLoads += 1;
            for (int i = 0; i < cache.blocksPerSet; i++) {
                if (cache.sets[fields.index].blocks[i].tag == fields.tag) {
                    cache.statistics->loadHits += 1;
                    break; //breaks from loop. We exit early if tag was pre-loaded
                           //into cache
                }
                if (i == cache.blocksPerSet - 1) {
                    /* This means a cacheMiss was registered */
                    cache.statistics->loadMisses += 1;

                    /* We should now load this data from memory into cache */

                    //TODO: Code to load data into cache //
                    
                }
            }
        } else if (fields.instr == 's') {







        } else {
            printf("Invalid inputs. Must choose to either load or store\n");
            return -1;
        }
    } while (read == 0);

}
