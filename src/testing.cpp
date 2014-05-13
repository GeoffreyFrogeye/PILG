#include <iostream>
#include <string>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "traitementImage.cpp"
#include "analyserCommande.cpp"

#define PI 3.14159265359

Image genererRoue(int dimX, int dimY, int maxComposante) {
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

            // // Remise dans l'intervalle
            // pointRoue.r = (pointRoue.r > maxComposante ? maxComposante : pointRoue.r);
            // pointRoue.v = (pointRoue.v > maxComposante ? maxComposante : pointRoue.v);
            // pointRoue.b = (pointRoue.b > maxComposante ? maxComposante : pointRoue.b);

            if (imageRoue.s_pixel(x, y, pointRoue) == 1) {
                cerr << "Erreur : s_pixel() a été entré avec des valeurs incorrectes" << endl;
                cout << "X : " << x << " - Y: " << y << " - R : " << pointRoue.r << " - V : " << pointRoue.v << " - B : " << pointRoue.b << endl; // DEBUG
            }
            imageRoue.g_pixel(x, y, pointRoue);
        }
    }
    return imageRoue;
}

Image genererDegrade(int dimX, int dimY, int maxComposante) {
    Image image(dimX, dimY, maxComposante, PILG_NIV);
    Pixel pixel = image.g_pixelVide();
    int x, y;
    for (x = 0; x < dimX; x++) {
        for (y = 0; y < dimY; y++) {
            pixel.g = (float) x * maxComposante / dimX;
            image.s_pixel(x, y, pixel);
        }
    }
    return image;
}

Image genererBruit(int dimX, int dimY) {
    Image image(dimX, dimY, 0, PILG_BIN);
    Pixel pixel = image.g_pixelVide();
    int x, y;
    for (x = 0; x < dimX; x++) {
        for (y = 0; y < dimY; y++) {
            pixel.n = ((float) rand() / RAND_MAX) < ((float) x / dimX);
            image.s_pixel(x, y, pixel);
        }
    }
    return image;
}

int main(int argc, char *args[]) {
#if defined(WIN32) // Permet de refaire fonctionner cout et cerr sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

    cout << "PILG - Test" << endl;  // Message d'entrée et de test

    // Image image = genererRoue(256, 128, 255);

    #define DIMENSIONS 256

    Image imageOriginale = genererRoue(DIMENSIONS, DIMENSIONS, 255);
    Image image = imageOriginale.g_vide();
    for (float i = 0; i < 2 * PI; i += 0.1) {
        pivoter(imageOriginale, image, DIMENSIONS/2, DIMENSIONS/2, i);
        afficherImage(image);
    }


    // // Neige en dégradé
    // for (int i; i < 300; i++) {
    //     afficherImage(genererBruit(200, 200));
    // }

    // Cycle de couleurs avec utilisation d'Image
    // Image imageRoue(dimX, dimY, 255, PILG_RVB);
    // Pixel pointRoueRoue = imageRoue.g_pixelVide();
    // int x, y, c;
    // for (c = 0; c < 256; c++) {  // À peu près 28 FPS avec SDL
    //     for (x = 0; x < dimX; x++) {
    //         for (y = 0; y < dimY; y++) {
    //             pixel.r = c;
    //             pixel.v = image.g_maxComposante() - c;
    //             pixel.b = 0;
    //             if (image.s_pixel(x, y, pixel) == 1) {
    //                 cerr << "Erreur : s_pixel() a été entré avec des valeurs incorrectes" << endl;
    //                 cout << "X : " << x << " - Y: " << y << " - R : " << pixel.r << " - V : " << pixel.v << " - B : " << pixel.b << endl; // DEBUG
    //                 return 1;
    //             }
    //             image.g_pixel(x, y, pixel);
    //             pointFenetre(x, y, pixel.r, pixel.v, pixel.b);
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

    // cout << "Éxecution du programme terminée. Vous pouvez quitter la fenêtre." << endl;
    fermerFenetre();

    return 0;
}
