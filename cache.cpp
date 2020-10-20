#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



Cache *create_cache(uint32_t setCounter, uint32_t blocks, uint32_t blockBytes) {
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
  newCache->offsetWidth = easyLog2(blockBytes);
  newCache->indexWidth = easyLog2(setCounter);
  newCache->tagWidth = uint32_t(MEM_ADDRESS_SIZE) - newCache->offsetWidth - newCache->indexWidth;
  /* Create statistics object within cache */
  newCache->statistics = (Stats*)malloc(sizeof(Stats));
  return newCache;

}



void print_statistics(Cache *c) { 
    assert(c != NULL && c->statistics != NULL);
    printf("Total loads: %llu\n", (unsigned long long)c->statistics->totalLoads);
    printf("Total stores: %llu\n", (unsigned long long)c->statistics->totalStores);
    printf("Load hits: %llu\n", (unsigned long long)c->statistics->loadHits);
    printf("Load misses: %llu\n", (unsigned long long)c->statistics->loadMisses);
    printf("Store hits: %llu\n", (unsigned long long)c->statistics->storeHits);
    printf("Store misses: %llu\n", (unsigned long long)c->statistics->storeMisses);
    printf("Total cycles: %llu\n", (unsigned long long)c->statistics->totalCycles); 
}

void free_cache(Cache *c) {
    for (unsigned i = 0; i < c->numSets; i++) {
      free(c->sets[i].blocks);
    }
    free(c->sets);
    free(c->statistics);
    free(c);
}

unsigned return_oldest_block(Set *s, uint32_t bps) {
    unsigned oldest;
    for(unsigned i = 0; i < bps; i++) {
        if (s->blocks[i].timestamp > oldest) {
            oldest = s->blocks[i].timestamp;
        }
    }
    return oldest;
}

uint32_t easyLog2(uint32_t num) {
    uint32_t result;
    while (num != 1) {
        result++;
        num = num >> 1;
    }
    return result;
}
