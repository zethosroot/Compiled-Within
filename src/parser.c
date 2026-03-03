#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "main.h"
#include "world.h"
#include "config.h"
#include "print.h"

bool hintShown = false;

void parse(char *verb, char *object, char *noun) {
    
    unsigned char next_room = 255;
    int i; // Für die For-Schleife
    bool found      = false; // Ist das Item gefunden?
    bool hasItem    = false; // Spieler hat das item
    bool ruleFound  = false; // Regel gefunden
    bool targetHere = false; // Ziel ist im aktuell Zimmer
    
    if (verb == NULL) return;
    
    if (strcmp(verb, "GO") == 0) {

        if (!noun) {
            clrscr();
            print_line("GO WHERE?", true, false);
            return;
        }

        if (noun && strcmp(noun, "EAST") == 0) {
            next_room = rooms[current_room].east;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL, NULL);
            }
        }
        else if (noun && strcmp(noun, "WEST") == 0) {
            next_room = rooms[current_room].west;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL, NULL);
            }
        }
        else if (noun && strcmp(noun, "NORTH") == 0) {
            next_room = rooms[current_room].north;
            
            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL, NULL);
            }
        } 
        else if (noun && strcmp(noun, "SOUTH") == 0) {
            next_room = rooms[current_room].south;

            if (next_room == 255) {
                clrscr();
                print_line("YOU CAN'T GO THAT WAY", true, false);
            } else {
                current_room = next_room;
                parse("LOOK", NULL, NULL);
            }
        }

    } else if (strcmp(verb, "TAKE") == 0) {
        clrscr();
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == current_room && strcmp(items[i].name, noun) == 0) {
                if (items[i].type == 'U') {
                    items[i].room = 255; // In Inventar
                    print_line("ITEM TAKEN", true, false);
                    found = true;
                    break;
                } else {
                    print_line("YOU CAN'T TAKE THAT", true, false);
                    return;
                }
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
                found = true;
            }
        }

        if (!found) {
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
        print_line("drop <ITEM NAME>   -  Drop an item", true, false);
        print_line("go   <LOCATION>    -  Go somewhere", true, false);
        print_line("inv                -  Show inventory", true, false);
        print_line("look               -  Describe room", true, false);
        print_line("quit               -  Quit the game", true, false);
        print_line("use <item> <target>-  Use item on item", true, false);

    } else if (strcmp(verb, "USE") == 0){

        clrscr();

        if (!noun) {
            print_line("USE WHAT?", true, false);
            return;
        }

        if (!object) {
            print_line("USE ON WHAT?", true, false);
            return;
        }

        hasItem = false;
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == 255 && strcmp(items[i].name, noun) == 0) {
                hasItem = true;
                break;
            }
        }

        if (!hasItem) {
            print_line("YOU DON'T HAVE THAT.", true, false);
            return;
        }

        targetHere = false;
        for (i = 0; i < NUM_ITEMS; i++) {
            if (items[i].room == current_room && strcmp(items[i].name, object) == 0) {
                targetHere = true;
                break;
            }
        }

        if (!targetHere) {
            print_line("YOU DON'T SEE THAT HERE.", true, false);
            return;
        }

        ruleFound = false;
        for (i = 0; i < NUM_USE_RULES; i++) {
            if (strcmp(noun, useRules[i].item) == 0 &&
                strcmp(object, useRules[i].target) == 0) {
                useRules[i].action();
                ruleFound = true;
                break;
            }
        }

        if (!ruleFound) {
            print_line("THAT DOESN'T WORK.", true, false);
        }
    } else {
        clrscr();
        cprintf("\r\nUNKNOWN: %s\r\n", verb);
    }
}
