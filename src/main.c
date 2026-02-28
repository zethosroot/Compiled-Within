#include <conio.h>
#include <c64.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "sound.h"

#define INPUT_LENGTH 40 // Länge der Eingabe setzen 
#define PRINT_SPEED 300 // Tempo der Tekstanzeige

// Funktionen deklarieren
void print_slow(const char *text);
void print_line(const char *text, bool slow, bool centered);
void print_paragraph(const char *text, bool slow, bool centered);
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
    print_line("========== Feras the guy =========", true, true);
    print_line("=        A game by Zsombor       =", true, true);
    print_line("==========      2026     =========", true, true);
    cprintf("\r\n");
    print_line("Type 'start' to play", true, true);

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

/* Basisfunction: Gibt Text langsam aus */
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

    print_paragraph("This feature is not implemented yet. Please check back later when it has been completed by the developer. :)", true, false);
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