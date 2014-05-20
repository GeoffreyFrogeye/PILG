#include <iostream>
#include <string>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "utilitaires.cpp"
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
                journal << "Erreur : s_pixel() a été entré avec des valeurs incorrectes" <<
                        endl;
                journal << "X : " << x << " - Y: " << y << " - R : " << pointRoue.r << " - V : "
                        <<
                        pointRoue.v << " - B : " << pointRoue.b << endl;
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

int appliquer(Image &image, string nomFichier, bool ASCII) {
    ouvrir(image, "tests/" + nomFichier);
    Pixel pixel;
    image.g_pixel(image.g_dimensionX() / 2, image.g_dimensionY() / 2, pixel);
    // trait(image, image, image.g_dimensionX() / 4, image.g_dimensionY() / 4,
    //       image.g_dimensionX() - image.g_dimensionX() / 4,
    //       image.g_dimensionY() - image.g_dimensionY() / 4, pixel);
    // cercle(image, image, image.g_dimensionX() / 2, image.g_dimensionY() / 2,
    //        image.g_dimensionY() / 4, pixel);
    // disque(image, image, image.g_dimensionX() / 2, image.g_dimensionY() / 2,
    //        image.g_dimensionY() / 4, pixel);
    // redimensionner(image, image, image.g_dimensionX() / 4, image.g_dimensionY() / 4,
    //                image.g_dimensionX() - image.g_dimensionX() / 4,
    //                image.g_dimensionY() - image.g_dimensionY() / 4);
    // redimensionner(image, image, 0, 0, image.g_dimensionY(), image.g_dimensionY());
    // retourner(image, image, 3);
    // convBIN(image, image);
    // convNIV(image, image);
    // convRVB(image, image);
    sauver(image, "tests/E_" + nomFichier, ASCII, nomFichier);
    afficherImage(image);
    attendreFenetre();
}

int main(int argc, char *args[]) {
    #if defined(WIN32) // Permet de refaire fonctionner cout et cerr sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
    presentation();
    cout << "Éxecution des instructions dans testing.cpp." << endl << endl;
#define DIMENSIONS 50
    Image image1 = genererRoue(DIMENSIONS * 2, DIMENSIONS, 255);
    Image image2 = genererRoue(DIMENSIONS * 2, DIMENSIONS, 255);
    // Image image1; // Tester si ça marche
    // afficherImage(image1);
    // attendreFenetre();
    // // Roue
    // Image image = image1.g_vide();
    // for (float i = 0; i < 2 * PI; i += 0.1) {
    //     pivoter(image1, image, DIMENSIONS/2, DIMENSIONS/2, i);
    //     afficherImage(image);
    // }
    // Ouvrir fichier
    appliquer(image1, "PikachuP1.pbm", true);
    appliquer(image1, "PikachuP2.pgm", true);
    appliquer(image1, "PikachuP3.ppm", true);
    appliquer(image1, "PikachuP4.pbm", false);
    appliquer(image1, "PikachuP5.pgm", false);
    appliquer(image1, "PikachuP6.pgm", false);
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
