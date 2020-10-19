#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include <vector>
#include <assert.h>



Cache *create_cache(uint32_t setCounter, uint32_t blocks, uint32_t blockBytes, Cache* newCache) {
  assert(setCounter >= 1);
  if (setCounter > 2) {
    assert(setCounter % 2 == 0);
  }
 
  assert(blocks >= 1);
  if (blocks > 2) {
    assert(blocks % 2 == 0);
  }
    
  assert (blockBytes >= 4);
  assert (blockBytes % 2 == 0);

  Cache *newCache = (Cache*)malloc(sizeof(Cache));

  /* Create cache sets */
  newCache->sets = (Set*)malloc(sizeof(Set) * setCounter);
  /* Fill sets with blocks */
  for (int i = 0; i < setCounter; i++) {
    newCache->sets[i].blocks = (Block*)malloc(sizeof(Block) * blocks);
  }
  /* Initialize with values that were passed in */
  newCache->numSets = setCounter;
  newCache->blocksPerSet = blocks;
  newCache->bytesPerBlock = blockBytes;

  /* Infer last parameteres of cache with math */
  newCache.offsetWidth = log2(blockBytes);
  newCache.indexWidth = log2(setCounter);
  newCache.tagWidth = uint32_t(MEM_ADDRESS_SIZE) - newCache->offsetWidth - 
      newCache->indexWidth;
  /* Create statistics object within cache */
  newCache->statistics = (Stats*)malloc(sizeof(Stats));

}

void set_cache(Cache *c) {
    return;
}


void print_statistics(Cache *c) { 
    assert(c != NULL && c->stats != NULL);
    printf("Total loads: %d\n", c->statistics.totalLoads);
    printf("Total stores: %d\n", c->statistics.stores);
    printf("Load hits: %d\n", c->statistics.loadHits);
    printf("Load misses: %d\n", c->statistics.loadMisses);
    printf("Store hits: %d\n", c->statistics.storeHits);
    printf("Store misses: %d\n", c->statistics.storeMisses);
    printf("Total cycles: %d\n", c->statistics.totalCycles); 
}

void free_cache(Cache *c) {
    for (unsigned i = 0; i < c->numSets; i++) {
      free(c->sets[i].blocks);
    }
    free(c->sets);
    free(c->statistics);
    free(c);
}
