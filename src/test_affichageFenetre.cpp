#include <iostream>
#include <string>

#include "affichageFenetreBGI.cpp"

using namespace std;


int main(int argc, char* args[]) {

#if defined(WIN32) // Permet de refaire fonctionner cin et cout sous Windows après démarrage de SDL
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
#endif

	cout << "TEST AFFICHAGE FENETRE" << endl; // Message d'entrée et de test

	int dimX = 640, dimY = 480;
	ouvrirFenetre(dimX, dimY, "Test affichage fenêtre");

	for (int c = 0; c <= 255; c++) { // À peu près 58 FPS
		for (int x = 0; x <= dimX; x++) {
			for (int y = 0; y <= dimY; y++) {
				pointFenetre(x, y, c, 255-c, 0);
			}
		}
		afficherFenetre();
	}

	cout << "Éxecution du programme terminée. Vous pouvez quitter la fenêtre." << endl;
	attendreFenetre();
	fermerFenetre();


    return 0;
}
