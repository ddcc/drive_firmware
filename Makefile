CC=gcc
CFLAGS=-Wall -O2
SOURCES=samsung.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=samsung

all: $(SOURCES) $(TARGET)
    
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	$(RM) $(TARGET)
