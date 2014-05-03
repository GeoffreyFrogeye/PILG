# Variables
## Pour make
.PHONY: clean, mrproper
## Compilation
CXX = g++
CXXFLAGS = -lSDL -lSDLmain -DDEBUG
## Chemins
EXEPATH = bin/
OBJPATH = obj/
SRCPATH = src/

# Programmes possibles
main: main.o image.o
	$(CXX) $(OBJPATH)main.o $(OBJPATH)image.o -o $(EXEPATH)$@ $(CXXFLAGS)

testing: test.o image.o
	$(CXX) $(OBJPATH)test.o $(OBJPATH)image.o -o $(EXEPATH)$@ $(CXXFLAGS)

# Dépendances
main.o: $(SRCPATH)main.cpp $(SRCPATH)image.h
	$(CXX) -c $< -o $(OBJPATH)$@ $(CXXFLAGS)

test.o: $(SRCPATH)test.cpp $(SRCPATH)image.cpp
	$(CXX) -c $< -o $(OBJPATH)$@ $(CXXFLAGS)

image.o: $(SRCPATH)image.cpp
	$(CXX) -c $< -o $(OBJPATH)$@

# Meta
clean:
	rm -rf $(OBJPATH)*.o