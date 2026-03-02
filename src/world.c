#include <conio.h>
#include <string.h>
#include "world.h"
#include "print.h"

void playInfosette(void) {
    clrscr();
    print_line("INFOSETTE PLAYED.\r\n", true, false);
}

void playCassette(void) {
    clrscr();
    print_line("CASSETTE PLAYED.\r\n", true, false);
}


Room rooms[] = {
    { "COMPUTER LAB", "You look around in the computerlab. It is full of electronics, wires, and coffee mugs.", 255, 1, 255, 255 },
    { "OFFICE", "A place for doing office work", 0, 255, 2, 255 },
    { "HALLWAY", "Exit is south from here.", 255, 255, 255, 1 },
};

Item items[] = {
    {"INFOSETTE", "A computer program", 'U', 0},
    {"COMPUTER", "Play infosettes", 'S', 0}, // 'S' bedeudet "static"
    {"CASSETTE", "A music track", 'U', 1},
};

UseRule useRules[] = {
    {"INFOSETTE", "COMPUTER", playInfosette},
    {"CASSETTE", "DECK", playCassette},
};

