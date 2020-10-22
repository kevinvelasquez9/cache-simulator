/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */

#define WRITE_ALLOCATE 4
#define NO_WRITE_ALLOCATE 0

#define WRITE_THROUGH 2
#define WRITE_BACK 0

#define LRU 1
#define FIFO 0

/* 000: No Write Allocate, Write Back, Fifo
   001: No Write Allocate, Write Back, LRU
   010: No Write Allocate, Write Through, Fifo
   011: No Write Allocate, Write Throguh, LRU
   100: Write Allocate, Write BAck, FIFO
   101: Write Allocate, Write Back, LRU
   110: Write Allocate, Write Through, FIFO
   111: Write Allocate, Write Through, LRU */

#define MEM_ADDRESS_SIZE 32

#define MEM_ACCESS_PER_4 100


#include <stdint.h>



//You can change the array pointers to vectors if you so please
typedef struct {
    uint32_t tag;
    /* Need to write back */
    uint32_t dirty;

} Block, *Line;


typedef struct {
    /* A vector of blocks with size blocksPerSet */
    Block *blocks;
    uint32_t numFilled;
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
void print_statistics(Cache *c);
void free_cache(Cache *c);
void rotate_blocks_left(Block *b, uint32_t numFilled, uint32_t recent);
uint32_t easyLog2(uint32_t num);







