CC = g++
CFLAGS = -std=c++11 -g -Wall -Wextra

EXECUTABLE = output

SRC_FILES = main.cpp dataset.cpp solver.cpp solution.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJ_FILES)

.PHONY: all clean
