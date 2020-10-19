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

//You can change the array pointers to vectors if you so please
typedef struct {
    uint32_t tag;
    /* Valid: is this line full of data? */
    unsigned valid;
    /* Need to write back */
    unsigned dirty;
    /* Timestamp: For Fifo/LRU ordering */
    unsigned timestamp;

} Block, *Line;


typedef struct {
    /* A vector of blocks with size blocksPerSet */
    Block *blocks;
} Set;

typedef struct {
    uint64_t totalLoads;
    uint64_t totalStores;
    uint64_t loadHits;
    uint64_t loadMisses;
    uint64_t storeHits;
    uint64_t storeMisses;
    uint64_t totalCycles;
} Stats;

typedef struct {
    /* A vector of sets */
    Set *sets;
    /* Params passed in through the command line */
    uint32_t numSets;
    uint32_t blocksPerSet;
    uint32_t bytesPerBlock;
    /* Inferred bit widths from parameters */
    uint32_t tagWidth;
    uint32_t indexWidth;
    uint32_t offsetWidth;
    /* Cache statisitcs */
    Stats *statistics;
} Cache;

typedef struct {
    /* Defines load or store instruction */
    char instr;
    /* tag | index | offset values */
    uint32_t tag;
    uint32_t index;
    uint32_t offset;
} Scan;

Cache *create_cache(uint32_t setCounter, uint32_t blocks, uint32_t blockBytes);
void set_cache(Cache *c);
void print_statistics(Cache *c);
void free_cache(Cache *c);
uint32_t easyLog2(uint32_t num);







