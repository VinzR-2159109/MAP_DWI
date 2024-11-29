PROJECT_NAME = MAP_DWI_Picking_Bin

ARDUINO_CORE = C:/Users/vinzr/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino
WIRE_LIB = C:/Users/vinzr/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/libraries/Wire
ARDUINO_HARDWARE = C:/Users/vinzr/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/variants/standard

CC = avr-gcc
CXX = avr-g++
CFLAGS = -mmcu=atmega328p -DF_CPU=16000000UL -Wall -Os
CPPFLAGS = $(CFLAGS) -std=c++17

INCLUDE_PATHS = -I$(ARDUINO_CORE) -I$(WIRE_LIB) -I$(ARDUINO_HARDWARE)

SRC_DIR = src
BUILD_DIR = build
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

OUTPUT_FILE = $(BUILD_DIR)/$(PROJECT_NAME).elf

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

