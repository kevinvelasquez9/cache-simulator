/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */

#define WRITE_ALLOCATE 1u
#define NO_WRITE_ALLOCATE 0u

#define WRITE_THROUGH = 2u
#define WRITE_BACK = 0

#define LRU = 4u
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
    unsigned tagSize;
    unsigned offsetSize;
    Set *sets;
    uint16_t tagWidth;
    uint16_t offsetWidth;
    uint16_t indexWidth;
    cache_stats *stats;
    unsigned char accessParams;
    unsigned associativity;
} cache, *Cache;

void print_statistics();

cache* create_cache(unsigned sets, unsigned blocks, unsigned blockBytes);





