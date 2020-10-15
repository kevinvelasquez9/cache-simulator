#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include <vector>

Cache* create_cache(unsigned sets, unsigned blocks, unsigned blockBytes) {
    assert(sets >= 1);
    if (sets > 2) {
        assert(sets % 2 == 0);
    }
 
    assert(blocks >= 1);
    if (blocks > 2) {
        assert(blocks % 2 == 0);
    }
    
    assert (blockBytes >= 4);
    assert (blockBytes % 2 == 0);

    /*Allocate memory for cache */
    cache *newCache = (cache*)malloc(sizeof(cache));
    /* Create cache sets */
    newCache->numSets = sets;
    newCache->sets = (set*)malloc(sizeof(set) * sets);
    /* Fill sets with blocks */
    newCache->associativity = blocks;
    for (int i = 0; i < sets; i++) {
        newCache->sets[0]->blocks = 
            (block*)malloc(sizeof(block) * newCache->associativity);
    }
    newCache->bytesPerBlock = blockBytes;

    uint32_t totalSize = sets * blocks * blockBytes;

    newCache->offsetWidth = log2(blockBytes);
    newcache->indexWidth = log2(totalSize) - log2(associativity) - 
        newCache->offsetWidth;
    newCache->tagWidth = uint32_t(32) - newCache->offsetWidth - 
        newCache->indexWidth;
    

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
