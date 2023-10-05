CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
CODES_DIR = Codes
BUILD_DIR = Codes/Builds
RSDL = Codes/src/rsdl


all : checkFolder StarWars

checkFolder:
	if [ ! -d "./$(BUILD_DIR)" ]; then \
		mkdir -p ./$(BUILD_DIR); \
	fi

StarWars : $(BUILD_DIR)/StarWars.o $(BUILD_DIR)/rsdl.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/SpaceFighter.o $(BUILD_DIR)/Map.o $(BUILD_DIR)/LaserBullet.o
	$(CC) $(BUILD_DIR)/StarWars.o $(BUILD_DIR)/rsdl.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/SpaceFighter.o $(BUILD_DIR)/Map.o $(BUILD_DIR)/LaserBullet.o $(CCFLAGS) -o StarWars.out

$(BUILD_DIR)/StarWars.o: $(CODES_DIR)/StarWars.cpp $(CODES_DIR)/Game.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp $(CODES_DIR)/SpaceFighter.hpp $(CODES_DIR)/Interface.hpp $(CODES_DIR)/Map.hpp $(CODES_DIR)/LaserBullet.hpp
	$(CC) -c $(CODES_DIR)/StarWars.cpp -o $(BUILD_DIR)/StarWars.o

$(BUILD_DIR)/rsdl.o: $(CODES_DIR)/src/rsdl.cpp $(CODES_DIR)/src/rsdl.hpp
	$(CC) -c $(RSDL).cpp -o $(BUILD_DIR)/rsdl.o

$(BUILD_DIR)/Interface.o: $(CODES_DIR)/Interface.cpp $(CODES_DIR)/Interface.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp
	$(CC) -c $(CODES_DIR)/Interface.cpp -o $(BUILD_DIR)/Interface.o

$(BUILD_DIR)/SpaceFighter.o: $(CODES_DIR)/SpaceFighter.cpp $(CODES_DIR)/SpaceFighter.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp $(CODES_DIR)/LaserBullet.hpp 
	$(CC) -c $(CODES_DIR)/SpaceFighter.cpp -o $(BUILD_DIR)/SpaceFighter.o

$(BUILD_DIR)/Game.o: $(CODES_DIR)/Game.cpp $(CODES_DIR)/Game.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp $(CODES_DIR)/SpaceFighter.hpp $(CODES_DIR)/Interface.hpp $(CODES_DIR)/Map.hpp $(CODES_DIR)/LaserBullet.hpp
	$(CC) -c $(CODES_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o
	
$(BUILD_DIR)/Map.o: $(CODES_DIR)/Map.cpp $(CODES_DIR)/Map.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp $(CODES_DIR)/SpaceFighter.hpp
	$(CC) -c $(CODES_DIR)/Map.cpp -o $(BUILD_DIR)/Map.o

$(BUILD_DIR)/LaserBullet.o: $(CODES_DIR)/LaserBullet.cpp $(CODES_DIR)/LaserBullet.hpp $(CODES_DIR)/Defines.hpp $(RSDL).hpp
	$(CC) -c $(CODES_DIR)/LaserBullet.cpp -o $(BUILD_DIR)/LaserBullet.o
