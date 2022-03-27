CC = clang
SRC_DIR = source
OBJ_DIR = objects
INC_DIR = include
SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := Fourier


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -I$(INC_DIR) -o $@ $<

.PHONY: clean
clean:
	rm -fr $(OBJ_DIR) $(TARGET)



