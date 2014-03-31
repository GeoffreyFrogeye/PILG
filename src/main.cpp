#include <iostream>
#include <string>

#include "affichageFenetreSDL.cpp" // Devrait charger le .h mais le programme est relativement simple (sans Makefile) donc on assemble tout en même temps


using namespace std;

// Insertion des ensembles de fonctions massives séparés pour plus de clarté
#include "analyserCommande.cpp"
#include "traitementImage.cpp"

int main(int argc, char* args[]) {

#if defined(WIN32) // Permet de refaire fonctionner cin et cout sous Windows après démarrage de SDL
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
#endif

	cout << "PILG" << endl; // Message d'entrée et de test

    return 0;
}
