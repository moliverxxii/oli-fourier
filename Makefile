CC = clang
SOURCE := $(wildcard *.c)
OBJECTS := $(SOURCE:%.c=%.o)
TARGET := Fourier


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): %.o: %.c %.h
	$(CC) -c -o $@ $<

