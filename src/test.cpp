#include <iostream>
#include <string>

#include "affichageFenetreSDL.cpp"
#include "image.h"

using namespace std;


int main(int argc, char *args[]) {
#if defined(WIN32) // Permet de refaire fonctionner cin et cout sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

    cout << "TEST AFFICHAGE FENETRE" << endl;  // Message d'entrée et de test

    int dimX = 640, dimY = 480;
    ouvrirFenetre(dimX, dimY, "Test affichage fenêtre");

    Image image(dimX, dimY, 255, PILG_RVB);
    int x, y, c;
    Pixel point;
    point = image.g_pixelVide();
    // cout << "R : " << point.r << " - V : " << point.v << " - B : " << point.b << endl; // DEBUG


    // Cycle de couleurs avec utilisation d'Image
    for (c = 0; c < 256; c++) {  // À peu près 28 FPS avec SDL
        for (x = 0; x < dimX; x++) {
            for (y = 0; y < dimY; y++) {
                point.r = c;
                point.v = image.g_maxComposante() - c;
                point.b = 0;
                if (image.s_point(x, y, point) == 1) {
                    cerr << "Erreur : s_point() a été entré avec des valeurs incorrectes" << endl;
                    cout << "X : " << x << " - Y: " << y << " - R : " << point.r << " - V : " << point.v << " - B : " << point.b << endl; // DEBUG
                    return 1;
                }
                image.g_point(x, y, point);
                pointFenetre(x, y, point.r, point.v, point.b);
            }
        }
        afficherFenetre();
    }

    // // Cycle de couleurs sans utilisation d'Image
    // for (c = 0; c < 256; c++) {  // À peu près 75 FPS avec SDL
    //     for (x = 0; x < dimX; x++) {
    //         for (y = 0; y < dimY; y++) {
    //             pointFenetre(x, y, c, 255 - c, 0);
    //         }
    //     }
    //     afficherFenetre();
    // }



    cout << "Éxecution du programme terminée. Vous pouvez quitter la fenêtre." << endl;
    attendreFenetre();
    fermerFenetre();

    return 0;
}
