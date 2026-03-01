#include <conio.h>
#include <c64.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "sound.h"
#include "world.h"
#include "main.h"

#define INPUT_LENGTH 40 // Länge der Eingabe setzen 
#define PRINT_SPEED 300 // Tempo der Tekstanzeige

// Globale variablen
bool gameOpen = true;
bool hasStarted = false;
unsigned char current_room = 0;
unsigned char next_room = 255;

/**
 * Hauptfunktion
 */
int main(void) {
   
    // Eingang des Spielers speichern
    unsigned char inputText[INPUT_LENGTH];

    char *verb = NULL;
    char * noun = NULL;

    // Farbe setzen
    VIC.bordercolor = 0;
    VIC.bgcolor0 = 0;
    *(unsigned char*)0x0286 = 1;

    // Anzeige löschen
    clrscr();

    // Wilkommentekst anzeigen
    print_line("========== Feras the guy =========", true, true);
    print_line("=        A game by Zsombor       =", true, true);
    print_line("==========      2026     =========", true, true);
    cprintf("\r\n");
    print_line("Type 'start' to play", true, true);

    while(gameOpen) {
        if (hasStarted){
            print_line("WHAT DO YOU DO?", true, false);
        }
        cprintf("\r\n> "); // Prompt
        read_input(inputText); // Texteingabe lesen
        str_upper(inputText); // Text Großbuchstaben setzen

        // Tokenisierung
        verb = strtok(inputText, " ");
        noun = strtok(NULL, " ");

        parse(verb, noun);

        cprintf("\r\n");
    }

    // Anzeige löschen
    clrscr();

    print_line("Goodbye!", false, true);
    print_line("PRESS RUN/STOP + RESTORE", false, true);
    while(true) {}

    return 0;

}


/* Gibt eine Zeile aus, optional zentriert und/oder langsam */
void print_line(const char *text, bool slow, bool centered) {
    int i;
    if (centered) {
        unsigned char padding = (40 - strlen(text)) / 2;
        for (i = 0; i < padding; i++) cputc(' ');
    }
    if (slow) print_slow(text);
    else cprintf("%s", text);
    cprintf("\r\n");
}

void read_input(unsigned char *buf) {
    unsigned char i = 0;
    unsigned char c;

    while (true) { 
        
        c = cgetc();

        if (c == 0x0D) {
            // Enter - Eingabe beenden
            buf[i] = '\0';
            break;
        } else if (c == 0x14 && i > 0) {
            // Rücktaste - ein Zeichen löschen
            i--;
            buf[i] = '\0';
            gotoxy(wherex() - 1, wherey());  // Cursor zurück
            cputc(' ');                      // Zeichen löschen
            gotoxy(wherex() - 1, wherey());  // Cursor wieder zurück
        } else if (i < INPUT_LENGTH - 1 && c != 0x14) {
            // Normales Zeichen speichern
            buf[i] = c;
            cputc(c);
            i++;
        }
    }
}

void str_upper(unsigned char *s) {
    while (*s) { *s = toupper(*s); s++; }
}

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
    } else if (strcmp(verb, "INVENTORY") == 0) {
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

    } else {
        cprintf("\r\nUNKNOWN: %s\r\n", verb);
    }
}

// Basisfunction: Gibt Text langsam aus
void print_slow(const char *text) {
    volatile int i;
    static int j;
    for (j = 0; text[j] != '\0'; j++) {
        if (text[j] == ' ') {
            cputc(' ');
        } else {
            play_click();
            cputc(text[j]);
            for (i = 0; i < PRINT_SPEED; i++);
        }
    }
}

void start() {
    clrscr(); // Anzeige löschen

    if (hasStarted) {
        print_line("You have already started.", true, false);        
        return;
    }

    current_room = 0;
    hasStarted = true;
    parse("LOOK", NULL);
}

/* Gibt einen Absatz mit Zeilenumbruch aus, optional zentriert und/oder langsam */
void print_paragraph(const char *text, bool slow, bool centered) {
    static char buf[256];
    static char linebuf[41];
    char *word;
    unsigned char col = 0;
    unsigned char wordlen;

    strcpy(buf, text);
    linebuf[0] = '\0';
    word = strtok(buf, " ");

    while (word != NULL) {
        wordlen = strlen(word);

        if (col + wordlen > 38) {
            /* Leerzeichen am Ende entfernen */
            if (col > 0) linebuf[col - 1] = '\0';
            print_line(linebuf, slow, centered);
            linebuf[0] = '\0';
            col = 0;
        }       

        strcat(linebuf, word);
        strcat(linebuf, " ");
        col += wordlen + 1;

        word = strtok(NULL, " ");
    }

    if (col > 0) {
        linebuf[col - 1] = '\0';
        print_line(linebuf, slow, centered);
    }
}