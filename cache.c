#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include <vector>

Cache* create_cache(unsigned sets, unsigned blocks, unsigned blockBytes) {
    asssert(sets >= 1);
    if (sets > 2) {
        assert(sets % 2 == 0);
    }
 
    assert(blocks >= 1);
    if (blocks > 2) {
        assert(blocks % 2 == 0);
    }
    
    assert (blockBytes >= 4);
    assert (blockBytes % 2 == 0);

    cache *newCache = (cache*)malloc(sizeof(cache));
    newCache->associativity = blocks;
    newCache->sets.resize(sets, NULL);
    newCache->

}


void print_statistics(Cache *c) {
    /* 
    assert(c != NULL && c->stats != NULL);
    printf("Total loads: %d\n", c->stats.loads);
    printf("Total stores: %d\n", c->stats.stores);
    printf("Load hits: %d\n", c->stats.loadHits);
    printf("Load misses: %d\n", c->stats.loadMisses);
    printf("Store hits: %d\n", c->stats.storeHits);
    printf("Store misses: %d\n", c->stats.storeMisses);
    printf("Total cycles: %d\n", c->stats.totalCycles); */
    
}
