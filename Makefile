# Variables
## Pour make
.PHONY: clean, mrproper
## Compilation
CXX = g++
CXXFLAGS = -lSDL -lSDLmain
CXXFLAGSDEBUG = -lSDL -lSDLmain -DDEBUG
## Chemins
EXEPATH = bin/
OBJPATH = obj/
SRCPATH = src/

# Programmes possibles
main: $(EXEPATH)main
testing: $(EXEPATH)testing

# Éxecutables
$(EXEPATH)main: $(OBJPATH)main.o $(OBJPATH)image.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(EXEPATH)testing: $(OBJPATH)testing.o $(OBJPATH)image.o
	$(CXX) $^ -o $@ $(CXXFLAGSDEBUG)

# Dépendances
## Fichiers executables
$(OBJPATH)main.o: $(SRCPATH)main.cpp $(SRCPATH)affichageFenetre.cpp $(SRCPATH)image.cpp $(SRCPATH)utilitaires.cpp $(SRCPATH)traitementImage.cpp $(SRCPATH)analyserCommande.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJPATH)testing.o: $(SRCPATH)testing.cpp $(SRCPATH)affichageFenetre.cpp $(SRCPATH)image.cpp $(SRCPATH)utilitaires.cpp $(SRCPATH)traitementImage.cpp $(SRCPATH)analyserCommande.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGSDEBUG)
## Bibliothèques
$(OBJPATH)image.o: $(SRCPATH)image.cpp
	$(CXX) -c $< -o $@

# Meta
clean:
	rm -rf $(OBJPATH)*.o