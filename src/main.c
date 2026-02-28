#include <conio.h>
#include <c64.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "sound.h"

#define INPUT_LENGTH 40 // Länge der Eingabe setzen 
#define PRINT_SPEED 300 // Tempo der Tekstanzeige

// Funktionen deklarieren
void print_centered(const char *text, bool slow);
void read_input(unsigned char *buf);
void str_upper(unsigned char *s);
void parse(char *verb, char*noun);
void start();

// Globale variablen
bool gameOpen = true;

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
    print_centered("========== Feras the guy =========", true);
    print_centered("=        A game by Zsombor       =", true);
    print_centered("==========      2026     =========", true);
    cprintf("\r\n");
    print_centered("Type 'start' to play", true);

    while(gameOpen) {
        cprintf("> "); // Prompt
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

    print_centered("Goodbye!", false);
    print_centered("PRESS RUN/STOP + RESTORE", false);
    while(true) {}

    return 0;

}


void print_centered(const char *text, bool slow) {
    
    // Center berechnen
    unsigned int len = strlen(text);
    unsigned char padding = (40 - len) / 2;

    // Variabel für for-schleife erstellen
    int i = 0;
    
    // Leerzeichen zum Text hinzufügen
    for (i = 0; i < padding; i++) {
        cprintf(" ");
    }


    if (slow) {
        volatile int i; // Keine Optimierung
        int j;
        
        for (j = 0; text[j] != '\0'; j++) {
            
            if (text[j] == ' ') {
                cputc(' ');
            } else {
                play_click();
                cputc(text[j]);
                for (i = 0; i < PRINT_SPEED; i++); // Leer For-Schleife 
            }
        }
        cprintf("\r\n"); // Newline setzen

    } else {
        cprintf("%s\r\n", text); // Newline setzen
    } 
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
    if (verb == NULL) return;
    
    if (strcmp(verb, "GO") == 0) {
        cprintf("\r\nGO: %s\r\n", noun ? noun : "WHERE?");
    } else if (strcmp(verb, "TAKE") == 0) {
        cprintf("\r\nTAKE: %s\r\n", noun ? noun : "WHAT?");
    } else if (strcmp(verb, "QUIT") == 0) {
        gameOpen = false; // Spiel stoppen
    } else if (strcmp(verb, "START") == 0){
        start(); // Spiel starten
    } else {
        cprintf("\r\nUNKNOWN: %s\r\n", verb);
    }
}

void print_slow(const char *text) {
    volatile int i; // Keine Optimierung
    int j;
    
    for (j = 0; text[j] != '\0'; j++) {
            
        if (text[j] == ' ') {
            cputc(' ');
        } else {
            play_click();
            cputc(text[j]);
            for (i = 0; i < PRINT_SPEED; i++); // Leer For-Schleife 
        }
    }
}

void start() {
    clrscr(); // Anzeige löschen

    print_slow("This feature is not implemented yet.\r\n");
    print_slow("Please check back later when it has\r\n");
    print_slow("been completed.\r\n");
}