CC      = cl65
CFLAGS = -t c64 -O -C adventure.cfg
TARGET  = build/adventure.prg

SRC     = src/main.c src/sound.c src/world.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	x64sc $(TARGET)

clean:
	rm -f $(TARGET)
