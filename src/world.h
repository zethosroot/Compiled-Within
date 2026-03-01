#ifndef WORLD_H
#define WORLD_H

#define NUM_ROOMS 3
#define NUM_ITEMS 3
#define MAX_INV   5

// Raum
typedef struct {
    const char *name;
    const char *description;
    unsigned char north;
    unsigned char south;
    unsigned char east;
    unsigned char west;
} Room;

// Item
typedef struct {
    const char *name;
    const char *description;
    unsigned char type; // U - Verwendbar, R - Lesbar, usw...
    unsigned char room; // Raum-Index, 255 = im Inventar
} Item;

extern Room rooms[];
extern Item items[];

#endif