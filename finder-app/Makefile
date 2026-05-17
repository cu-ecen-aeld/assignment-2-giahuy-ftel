CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -Werror
TARGET := writer
OBJS := writer.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

writer.o: writer.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
