#ifndef WORLD_H
#define WORLD_H

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

// Nutzungsregeln
typedef struct {
    char* item;
    char* target;
    void (*action)(void);
} UseRule;

extern Room rooms[];
extern Item items[];
extern UseRule useRules[];

#endif