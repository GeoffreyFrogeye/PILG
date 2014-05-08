#include <iostream>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "traitementImage.cpp"
#include "analyserCommande.cpp"

#define NOMBREOR 1.61803398875

Image imageDefaut() {
    int dimY = 256, dimX = dimY * NOMBREOR, maxComposante = 255;
    Image imageRoue(dimX, dimY, maxComposante, PILG_RVB);
    Pixel pointRoue = imageRoue.g_pixelVide();
    int x, y, step;
    float substep, lum;
    for (x = 0; x < dimX; x++) {
        for (y = 0; y < dimY; y++) {
            step = (x * 6.0) / dimX;
            substep = (x - step * (dimX / 6.0)) / (dimX / 6.0) * maxComposante;
            lum = 1 - ((float) y) / dimY;
            switch (step) {
            case 0:
                pointRoue.r = maxComposante;
                pointRoue.v = substep;
                pointRoue.b = 0;
                break;
            case 1:
                pointRoue.r = maxComposante - substep;
                pointRoue.v = maxComposante;
                pointRoue.b = 0;
                break;
            case 2:
                pointRoue.r = 0;
                pointRoue.v = maxComposante;
                pointRoue.b = substep;
                break;
            case 3:
                pointRoue.r = 0;
                pointRoue.v = maxComposante - substep;
                pointRoue.b = maxComposante;
                break;
            case 4:
                pointRoue.r = substep;
                pointRoue.v = 0;
                pointRoue.b = maxComposante;
                break;
            case 5:
                pointRoue.r = maxComposante;
                pointRoue.v = 0;
                pointRoue.b = maxComposante - substep;
                break;
            }

            // Dégradé vers le noir
            pointRoue.r = pointRoue.r * lum;
            pointRoue.v = pointRoue.v * lum;
            pointRoue.b = pointRoue.b * lum;

            imageRoue.s_pixel(x, y, pointRoue);
        }
    }
    return imageRoue;
}

int main(int argc, char *args[]) {
#if defined(WIN32)  // Permet de refaire fonctionner cout et cerr sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

    cout << "PILG" << endl;  // Message d'entrée et de test

    Image image = imageDefaut();

    if (argc > 1) { // Si la commande a été entrée avec des arguments
        vector< string > decoupe;
        for (int i = 1; i < argc; i++) {
            decoupe.push_back(args[i]);
        }
        procederCommande(decoupe, image);
    } else {
        afficherImage(image);
        boucleDeCommandes(image);
    }

    return 0;
}
