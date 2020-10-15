/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */

#define WRITE_ALLOCATE 1
#define NO_WRITE_ALLOCATE 0

#define WRITE_THROUGH = 2
#define WRITE_BACK = 0

#define LRU = 4
#define FIFO = 0

#include <stdint.h>

//You can change the array pointers to vectors if you so please
typedef struct {
    uint32_t tag;
    /* Valid: is this line full of data? */
    unsigned valid;
    /* Need to write back */
    unsigned dirty;

} block, *Block, *line, *Line;


typedef struct {
    block *blocks;
} set, *Set;

typedef struct {
    uint64_t totalLoads;
    uint64_t totalStores;
    uint64_t loadHits;
    uint64_t loadMisses;
    uint64_t storeHits;
    uint64_t storeMisses;

} stats, *cacheStats, *cache_stats;

typedef struct {
    set *sets;
    uint32_t numSets;
    uint32_t associativity;
    uint32_t tagWidth;
    uint32_t indexWidth;
    uint32_t offsetWidth;
    uint32_t bytesPerBlock;
} cache, *Cache;

void print_statistics();
cache* create_cache(unsigned sets, unsigned blocks, unsigned blockBytes);

uint32_t log2(uint32_t cheeky) {
    uint32_t result;
    cheeky = cheeky >> 1;
    result++
    if (cheeky == 1) {
        return result;
    } else {
        log2(cheeky);
    }

}





