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
    unsigned char validity;
    unsigned char timestamp;

} Block, *Line;


typedef struct {
    Block *initialBlock;
    unsigned numBlocks;
} Set;

typedef struct {
    uint64_t totalLoads;
    uint64_t totalStores;
    uint64_t loadHits;
    uint64_t loadMisses;
    uint64_t storeHits;
    uint64_t storeMisses;

} Stats, *cacheStats, *cache_stats;

typedef struct {
    Set *sets;
    uint16_t tagWidth;
    uint16_t offsetWidth;
    uint16_t indexWidth;
    cache_stats *stats;
    unsigned char accessParams;
} Cache;

void print_statistics();





