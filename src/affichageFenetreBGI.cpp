#include <graphics.h>

int ouvrirFenetre(int dimensionX, int dimensionY, const char* nom) {  // Crée une fenêtre
    initwindow(dimensionX, dimensionY, nom, 0, 0);
	return 0;
}

int setNomFenetre(const char* nom) { // Change le nom de la fenêtre
	return 0;
}

int pointFenetre(int x, int y, int r, int v, int b) {
    putpixel(x, y, COLOR(r, v, b));
	return 0;
}

int afficherFenetre() {

	return 0;
}

int attendreFenetre() {
    while (kbhit()) {
    	delay(100);
    }
}

int fermerFenetre() {
    closegraph(ALL_WINDOWS);
}
