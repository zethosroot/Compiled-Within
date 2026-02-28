#include <c64.h>
#include <conio.h>
#include "sound.h"

void play_click(void) {
    
    volatile int i;
    
    SID.amp = 8; // Lautstärke setzen (maximal ist 15)

    SID.v1.freq = 0x8000;  // Frequenz setzen
    SID.v1.ad = 0x00; // Schnell attack mit schnell decay setzen
    SID.v1.sr = 0x00; // Kein sustain mit schnell release
    SID.v1.pw = 0x0800; // 50% pulse width
    SID.v1.ctrl = 0x41; // Tor aus

    for (i = 0; i < 15; i++);

    SID.v1.ctrl = 0x40; // Tor einschalten

}