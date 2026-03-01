# Compiled Within

![Platform](https://img.shields.io/badge/platform-Commodore%2064-blue)
![Language](https://img.shields.io/badge/language-C%20%2F%206502%20ASM-lightgrey)
![Compiler](https://img.shields.io/badge/compiler-cc65-orange)
![Status](https://img.shields.io/badge/status-in%20development-yellow)
![License](https://img.shields.io/badge/license-MIT-green)

> *A text adventure game for the Commodore 64.*

You are a programmer. Something has gone terribly wrong. You have been **compiled within your own code** — trapped inside the very program you wrote. Navigate the strange digital world of your own creation, find the tools you need, and escape before the process terminates.

---

## Features

- Classic text adventure parser (`GO`, `TAKE`, `DROP`, `LOOK`, `INV`, `USE`, `HELP`)
- Typewriter-style text output with SID chip sound effects
- Black & white CRT-friendly display
- Room navigation with items and inventory system
- Built with modern tooling, runs on real hardware

---

## Requirements

- [cc65](https://cc65.github.io/) — C compiler for 6502 targets
- [VICE](https://vice-emu.sourceforge.io/) — Commodore 64 emulator (for testing)
- A real Commodore 64 (optional, but highly recommended 😄)

---

## Building

```bash
git clone https://github.com/zethosroot/compiled-within.git
cd compiled-within
make
```

This produces `build/adventure.prg`.

---

## Running

**In VICE:**
```bash
make run
```

**On real hardware:**
Transfer `build/adventure.prg` to a `.d64` disk image or use a device like an SD2IEC or 1541 Ultimate.

---

## Commands

| Command | Description |
|---|---|
| `GO <direction>` | Move in a direction (NORTH, SOUTH, EAST, WEST) |
| `TAKE <item>` | Pick up an item |
| `DROP <item>` | Drop an item |
| `LOOK` | Describe current room |
| `INV` | Show inventory |
| `HELP` | List available commands |
| `QUIT` | Quit the game |

---

## Project Structure

```
compiled-within/
├── src/
│   ├── main.c       — Entry point and game loop
│   ├── parser.c     — Command parser and handlers
│   ├── print.c      — Text output functions
│   ├── input.c      — Keyboard input handler
│   ├── sound.c      — SID chip sound effects
│   ├── world.c      — Room and item data
│   └── macros.h     — Shared constants
├── assets/          — Bitmap art (WIP)
├── adventure.cfg    — cc65 linker configuration
└── Makefile
```

---

## Author

Made with ❤️ and a 1MHz CPU by **zethosroot**

*Built on Arch Linux. Tested on a real Commodore 64.*

---

## License

MIT