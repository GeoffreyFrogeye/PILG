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

    cout << "PILG - Debug" << endl;  // Message d'entrée et de test

    int dimX = 640, dimY = 128;
    ouvrirFenetre(dimX, dimY, "PILG - Fenêtre de debug");

    // Création imageRoue
    Image imageRoue(dimX, dimY, 255, PILG_RVB);
    Pixel pointRoue = imageRoue.g_pixelVide();
    int x, y, step;
    float substep, lum;
    for (x = 0; x < dimX; x++) {
        for (y = 0; y < dimY; y++) {
            step = (x * 6.0) / dimX;
            substep = (x - step * (dimX / 6.0)) / (dimX / 6.0)*255;
            lum = 1-((float) y)/dimY;
            switch (step) {
            case 0:
                pointRoue.r = 255;
                pointRoue.v = substep;
                pointRoue.b = 0;
                break;
            case 1:
                pointRoue.r = 255-substep;
                pointRoue.v = 255;
                pointRoue.b = 0;
                break;
            case 2:
                pointRoue.r = 0;
                pointRoue.v = 255;
                pointRoue.b = substep;
                break;
            case 3:
                pointRoue.r = 0;
                pointRoue.v = 255-substep;
                pointRoue.b = 255;
                break;
            case 4:
                pointRoue.r = substep;
                pointRoue.v = 0;
                pointRoue.b = 255;
                break;
            case 5:
                pointRoue.r = 255;
                pointRoue.v = 0;
                pointRoue.b = 255-substep;
                break;
            }
            // Dégradé vers le noir
            pointRoue.r = pointRoue.r*lum;
            pointRoue.v = pointRoue.v*lum;
            pointRoue.b = pointRoue.b*lum;

            // // Ajout de luminosité
            // pointRoue.r = pointRoue.r + 50;
            // pointRoue.v = pointRoue.v + 50;
            // pointRoue.b = pointRoue.b + 50;

            // Remise dans l'intervalle
            pointRoue.r = (pointRoue.r > 255 ? 255 : pointRoue.r);
            pointRoue.v = (pointRoue.v > 255 ? 255 : pointRoue.v);
            pointRoue.b = (pointRoue.b > 255 ? 255 : pointRoue.b);

            if (imageRoue.s_point(x, y, pointRoue) == 1) {
                cerr << "Erreur : s_point() a été entré avec des valeurs incorrectes" << endl;
                cout << "X : " << x << " - Y: " << y << " - R : " << pointRoue.r << " - V : " << pointRoue.v << " - B : " << pointRoue.b << endl; // DEBUG
                return 1;
            }
            imageRoue.g_point(x, y, pointRoue);
            pointFenetre(x, y, pointRoue.r, pointRoue.v, pointRoue.b);
        }
    }
    afficherFenetre();

    // Cycle de couleurs avec utilisation d'Image
    // Image imageRoue(dimX, dimY, 255, PILG_RVB);
    // Pixel pointRoueRoue = imageRoue.g_pixelVide();
    // int x, y, c;
    // for (c = 0; c < 256; c++) {  // À peu près 28 FPS avec SDL
    //     for (x = 0; x < dimX; x++) {
    //         for (y = 0; y < dimY; y++) {
    //             point.r = c;
    //             point.v = image.g_maxComposante() - c;
    //             point.b = 0;
    //             if (image.s_point(x, y, point) == 1) {
    //                 cerr << "Erreur : s_point() a été entré avec des valeurs incorrectes" << endl;
    //                 cout << "X : " << x << " - Y: " << y << " - R : " << point.r << " - V : " << point.v << " - B : " << point.b << endl; // DEBUG
    //                 return 1;
    //             }
    //             image.g_point(x, y, point);
    //             pointFenetre(x, y, point.r, point.v, point.b);
    //         }
    //     }
    //     afficherFenetre();
    // }

    // // Cycle de couleurs sans utilisation d'Image
    // int x, y, c;
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
