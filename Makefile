CC      = cl65
CFLAGS  = -t c64 -O
TARGET  = build/adventure.prg

SRC     = src/main.c src/sound.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	x64sc $(TARGET)

clean:
	rm -f $(TARGET)
