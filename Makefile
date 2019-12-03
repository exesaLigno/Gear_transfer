CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=transfer.cpp gear.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=transfer.out

all: $(SOURCES) $(EXECUTABLE)

install: $(SOURCES) $(EXECUTABLE)
	echo "Installing application"
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
.PHONY: clean
clean:
	rm -rf *.o "$(EXECUTABLE)"
	
.PHONY: run
run:
	./"$(EXECUTABLE)" 
