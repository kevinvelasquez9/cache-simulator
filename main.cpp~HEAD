/* Christian Helgeson and Kevin Velasquez */
/* CSF Fall 2020 */
/* Assignment 3: Cache Simulator */

#include "cache.h"
#include <stdio.h>
#include <string.h>


paramCheck(int *p, char *arg, int check) {
    assert(check >= 4 && check < 7)
    if (check == 4) {
        if (strcmp(arg, "write-allocate")) {
        
            *p += WRITE_ALLOCATE;
        } else if (strcmp(arg, "no-write-allocate") {
            *p += NO_WRITE_ALLOCATE;
        } else {
            *p = -1;
        }
    }

    if (check == 5) {
        if (strcmp(arg, "write-through")) {
            *p += WRITE_THROUGH;
        } else if (strcmp(arg, "write-back") {
            *p += WRITE_BACK;
        } else {
            *p = -1;
        }
    }

    if (check == 6) {
        if (strcmp(arg, "lru")) {
            *p += LRU;
        } else if (strcmp(arg, "fifo") {
            *p += FIFO;
        } else {
            *p = -1;
        }
    }
    
}



int main(int argc, char argv[]) {
    if (argc != 7) {
        return -1;
    }

    assert(argc == 7);
    int param = 0;
    for (int i = 4; i < 7; i++) {
        paramCheck(&param, argv[i], i);
        assert(param >= 0);
    }

    if (param < 2) {
        printf("Invalid inputs. Unable to write cache to store\n");
        return -1;
    }
    
    
    




}
