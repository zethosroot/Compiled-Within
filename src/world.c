#include "world.h"

Room rooms[] = {
    { "COMPUTER LAB", "A lab for computer geeks", 255, 1, 255, 255 },
    { "OFFICE", "A place for doing office work", 0, 255, 2, 255 },
    { "HALLWAY", "Exit is south from here.", 255, 255, 255, 1 },
};

Item items[] = {
    {"INFOSETTE", "A computer program", 'R', 0},
    {"COMPUTER", "Play infosettes", 'U', '0'},
    {"CASSETTE", "A music track", 'R', 1},
};
