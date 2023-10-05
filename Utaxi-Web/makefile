CC1 = g++
CC2 = -std=c++11
CC = $(CC1) $(CC2)

BUILD_DIR = Builds
CODE_DIR = Codes


all: checkFolder myserver

checkFolder:
	if [ ! -d "./$(BUILD_DIR)" ]; then \
		mkdir -p ./$(BUILD_DIR); \
	fi

myserver: $(BUILD_DIR)/main.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Web.o $(BUILD_DIR)/Utaxi.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Exceptions.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/Location.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Web.o $(BUILD_DIR)/Utaxi.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Exceptions.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/Location.o -o myserver.out


$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp $(CODE_DIR)/Utaxi.hpp
	$(CC) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o $(BUILD_DIR)/route.o



$(BUILD_DIR)/Web.o: $(CODE_DIR)/Web.cpp $(CODE_DIR)/Web.hpp $(CODE_DIR)/Handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp $(CODE_DIR)/Utaxi.hpp $(CODE_DIR)/User.hpp $(CODE_DIR)/Location.hpp $(CODE_DIR)/Trip.hpp $(CODE_DIR)/Exceptions.hpp
	$(CC) -c $(CODE_DIR)/Web.cpp -o $(BUILD_DIR)/Web.o

$(BUILD_DIR)/Handlers.o: $(CODE_DIR)/Handlers.cpp $(CODE_DIR)/Handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp $(CODE_DIR)/Utaxi.hpp $(CODE_DIR)/User.hpp $(CODE_DIR)/Location.hpp $(CODE_DIR)/Trip.hpp $(CODE_DIR)/Exceptions.hpp
	$(CC) -c $(CODE_DIR)/Handlers.cpp -o $(BUILD_DIR)/Handlers.o

$(BUILD_DIR)/main.o: $(CODE_DIR)/main.cpp $(CODE_DIR)/Web.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp $(CODE_DIR)/Handlers.hpp $(CODE_DIR)/Utaxi.hpp $(CODE_DIR)/User.hpp $(CODE_DIR)/Location.hpp $(CODE_DIR)/Trip.hpp $(CODE_DIR)/Utaxi.hpp $(CODE_DIR)/User.hpp $(CODE_DIR)/Location.hpp $(CODE_DIR)/Trip.hpp $(CODE_DIR)/Exceptions.hpp
	$(CC) -c $(CODE_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Utaxi.o: $(CODE_DIR)/Utaxi.cpp $(CODE_DIR)/Utaxi.hpp $(CODE_DIR)/User.hpp $(CODE_DIR)/Location.hpp $(CODE_DIR)/Trip.hpp $(CODE_DIR)/Exceptions.hpp
	$(CC) -c $(CODE_DIR)/Utaxi.cpp -o $(BUILD_DIR)/Utaxi.o

$(BUILD_DIR)/User.o: $(CODE_DIR)/User.cpp $(CODE_DIR)/User.hpp
	$(CC) -c $(CODE_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Location.o: $(CODE_DIR)/Location.cpp $(CODE_DIR)/Location.hpp
	$(CC) -c $(CODE_DIR)/Location.cpp -o $(BUILD_DIR)/Location.o

$(BUILD_DIR)/Trip.o: $(CODE_DIR)/Trip.cpp $(CODE_DIR)/Trip.hpp
	$(CC) -c $(CODE_DIR)/Trip.cpp -o $(BUILD_DIR)/Trip.o

$(BUILD_DIR)/Exceptions.o: $(CODE_DIR)/Exceptions.cpp $(CODE_DIR)/Exceptions.hpp
	$(CC) -c $(CODE_DIR)/Exceptions.cpp -o $(BUILD_DIR)/Exceptions.o

