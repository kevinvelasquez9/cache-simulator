/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */

#include <stdint.h>

//You can change the array pointers to vectors if you so please
typedef struct {
    uint32_t tag;
    unsigned char validity;
    unsigned char timestamp;

} Block, *Line;


typedef struct {
    Block *initialBlock;
    unsigned setSize;
} Set;

typedef struct {
    set *sets;
    uint16_t tagWidth;
    uint16_t offsetWidth;
    uint16_t indexWidth;
} Cache;

typedef struct {
    uint64_t accesses;
    uint64_t reads;
    uint64_t writes;
    uint64_t read_misses;
    uint64_t write_misses;

} Stats, *cacheStats, *cache_stats;



void print_statistics();





