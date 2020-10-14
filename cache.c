#include <stdio.h>
#include <stdlib.h>
#include "cache.h"




void print_statistics(Cache *c) {
    assert(c != NULL && c->stats != NULL);
    printf("Total loads: %d\n", c->stats.loads);
    printf("Total stores: %d\n", c->stats.stores);
    printf("Load hits: %d\n", c->stats.loadHits);
    printf("Load misses: %d\n", c->stats.loadMisses);
    printf("Store hits: %d\n", c->stats.storeHits);
    printf("Store misses: %d\n", c->stats.storeMisses);
    printf("Total cycles: %d\n", c->stats.totalCycles);
}
