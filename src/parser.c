#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "main.h"
#include "world.h"
#include "macros.h"
#include "print.h"

bool hintShown = false;

void parse(char *verb, char *noun) {
    
    unsigned char next_room = 255;
    int i; // Für die For-Schleife
    bool found = false; // Ist das Item gefunden?
    bool itemFound = false; // Etwas Items gefunden
    
    if (verb == NULL) return;
    
    if (strcmp(verb, "GO") == 0) {
        
        if (strcmp(noun, "EAST") == 0) {
            next_room = rooms[current_room].east;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL);
            }
        }
        else if (strcmp(noun, "WEST") == 0) {
            next_room = rooms[current_room].west;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL);
            }
        }
        else if (strcmp(noun, "NORTH") == 0) {
            next_room = rooms[current_room].north;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL);
            }
        } 
        else if (strcmp(noun, "SOUTH") == 0) {
            next_room = rooms[current_room].south;

            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL);
            }
        } else {
            clrscr();
            print_line("GO WHERE?", true, false);
        }

    } else if (strcmp(verb, "TAKE") == 0) {

        clrscr();
        
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == current_room && strcmp(items[i].name, noun) == 0) {
                items[i].room = 255; // In Inventar
                print_line("TAKEN", true, false);
                found = true;
                break;
            }
        }
        if (!found) {
            print_line("YOU DON'T SEE THAT HERE.", true, false);
        }

    } else if (strcmp(verb, "QUIT") == 0) {
        gameOpen = false; // Spiel stoppen

    } else if (strcmp(verb, "LOOK") == 0) {
        clrscr();
        print_line(rooms[current_room].name, true, true);
        cprintf("\r\n");
        print_paragraph(rooms[current_room].description, true, false);
        cprintf("\r\n");

        cprintf("ITEMS IN ROOM: ");

        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == current_room){
                cprintf("\r\n\r\n%s - %s\r\n", items[i].name, items[i].description);
                itemFound = true;
            }
        }

        if (!itemFound) {
            cprintf ("NONE\r\n\r\n");
        }

        if (!hintShown) {
            cprintf("\r\n(Type 'help' for available commands)\r\n");
            hintShown = true;
        }

        cprintf("\r\nEXITS: ");
        if (rooms[current_room].east != 255)  cprintf("EAST ");
        if (rooms[current_room].west != 255)  cprintf("WEST ");
        if (rooms[current_room].north != 255) cprintf("NORTH ");
        if (rooms[current_room].south != 255) cprintf("SOUTH ");
        if (rooms[current_room].north == 255 && rooms[current_room].south == 255 &&
            rooms[current_room].east == 255  && rooms[current_room].west == 255)
            cprintf("NONE");
        cprintf("\r\n");
    } else if (strcmp(verb, "START") == 0){
        start(); // Spiel starten
    } else if (strcmp(verb, "DROP") == 0){
        clrscr();
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == 255 && strcmp(items[i].name, noun) == 0) {
                items[i].room = current_room;
                found = true;
                cprintf("ITEM DROPPED\r\n\r\n");
                break;
            } 
        }

        if (!found) {
            cprintf("ITEM NOT IN INVENTORY\r\n\r\n");
        }
    } else if (strcmp(verb, "INV") == 0) {
        clrscr();
        found = false;
        print_line("INVENTORY: ", true, true);
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == 255) {
                cprintf("\r\n%s - %s\r\n", items[i].name, items[i].description);
                found = true;
            }
        }

        if (!found) {
            cprintf("\r\nNO ITEMS IN INVENTORY\r\n\r\n");
        }

    } else if (strcmp(verb, "HELP") == 0){
        clrscr();
        print_line("AVAILABLE COMMANDS\r\n", true, true);
        print_line("DROP <ITEM NAME>   -  Drop an item", true, false);
        print_line("GO   <LOCATION>    -  Go somewhere", true, false);
        print_line("INV                -  Show inventory", true, false);
        print_line("LOOK               -  Look around", true, false);
        print_line("DROP <ITEM>        -  Drop an item", true, false);
    } else {
        clrscr();
        cprintf("\r\nUNKNOWN: %s\r\n", verb);
    }
}