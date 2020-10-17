#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include <vector>

void create_cache(uint32_t sets, uint32_t blocks, uint32_t blockBytes, cache *newCache) {
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
    newCache->sets.resize(numSets);
    /* Fill sets with blocks */
    for (int i = 0; i < sets; i++) {
        newCache->sets[0]->blocks.resize(newCache->blocksPerSet);
    }
    /* Initialize with values that were passed in */
    newCache->numSets = sets;
    newCache->blocksPerSet = blocks;
    newCache->bytesPerBlock = blockBytes;

    /* Infer last parameteres of cache with math */
    newCache->offsetWidth = log2(blockBytes);
    newcache->indexWidth = log2(numSets);
    newCache->tagWidth = uint32_t(MEM_ADDRESS_SIZE) - newCache->offsetWidth - 
        newCache->indexWidth;
    
}

void set_cache(Cache *c) {
  //If param % 2 == 0, do fifo
  //If param % 2 == 1 do lru

  //fifo
  /* if (cache->statistics.parameters % 2 == 0) {
    for (int i = 0; i > cache->blocksPerSet; i++) {
      if (cache->sets[].blocks[i].timestamp == cache->blocksPerSet - 1) {
	//do code to tkae */
     // }
      

    //}

    //lru
  //} else {
    //if block is accessed, make timestamp equal to 0
    //if block is old i.e == 3 set it to something else
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
