CC=gcc
CFLAGS=-Wall -O2
SOURCES=wdc.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=wdc

all: $(SOURCES) $(TARGET)
    
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	$(RM) $(TARGET)
