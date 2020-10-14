/* Christian Helgeson and Kevin Velasquez 
CSF Fall 2020
cache.h */



typedef struct {
    uint32_t memAddress;
    unsigned char validity;
    unsigned tag;
    unsigned offset;

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
