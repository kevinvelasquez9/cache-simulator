/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */

#define WRITE_ALLOCATE 1
#define NO_WRITE_ALLOCATE 0

#define WRITE_THROUGH 2
#define WRITE_BACK 0

#define LRU 4
#define FIFO 0

#define MEM_ADDRESS_SIZE 32

#include <stdint.h>
#include <vector>

//You can change the array pointers to vectors if you so please
typedef struct {
    uint32_t tag;
    /* Valid: is this line full of data? */
    unsigned valid;
    /* Need to write back */
    unsigned dirty;
    /* Timestamp: For Fifo/LRU ordering */
    unsigned timestamp;

} block, *Block, *line, *Line;


typedef struct {
    /* A vector of blocks with size blocksPerSet */
    std::vector<block> blocks;
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
    /* A vector of sets */
    std::vector<set> sets;
    /* Params passed in through the command line */
    uint32_t numSets;
    uint32_t blocksPerSet;
    uint32_t bytesPerBlock;
    /* Inferred bit widths from parameters */
    uint32_t tagWidth;
    uint32_t indexWidth;
    uint32_t offsetWidth;
    /* Cache statisitcs */
    stats *statistics;
} cache, *Cache;

typedef struct {
    /* Defines load or store instruction */
    char instr;
    /* tag | index | offset values */
    uint32_t tag;
    uint32_t index;
    uint32_t offset;
} Scan;

/* Initializes a new cache */
cache* create_cache(unsigned sets, unsigned blocks, unsigned blockBytes);
void set_cache(Cache *c);
/* Prints statistics related to successful stores and loads */
void print_statistics();

uint32_t log2(uint32_t cheeky) {
    uint32_t result;
    cheeky = cheeky >> 1;
    result++;
    if (cheeky == 1) {
        return result;
    } else {
        log2(cheeky);
    }

}






