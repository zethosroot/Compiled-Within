#include <conio.h>
#include <c64.h>
#include <stdbool.h>
#include <string.h>
#include "sound.h"
#include "world.h"
#include "main.h"
#include "parser.h"
#include "print.h"
#include "input.h"
#include "macros.h"

// Globale variablen
bool gameOpen = true;
unsigned char current_room = 0;
bool hasStarted = false;
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
            print_line("Type 'help' for a available commands\r\n", false, false);
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

