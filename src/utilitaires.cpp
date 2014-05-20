#include <math.h>
#include <fstream>

#define NOMBREOR 1.61803398875

ofstream journal("PILG-log.txt", ios::out | ios::trunc);

void presentation() {
    cout << " ____   ___   _       ____ "  << endl
         << "|  _ \\ |_ _ || |     / ___|" << endl
         << "| |_) | | |  | |    | |  _ "  << endl
         << "|  __/  | |  | |___ | |_| |"  << endl
         << "|_|    |___| |_____| \\____|" << endl;
}

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
                
            default:
                pointRoue.r = pointRoue.v = pointRoue.b = 0;
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

void afficherImage(Image image) {
#define ECHELLE 1
    int x, y, r, v, b, eX, eY, dimensionX = image.g_dimensionX() * ECHELLE,
                               dimensionY = image.g_dimensionY() * ECHELLE,
                               typeComposantes = image.g_typeComposantes();
    float ratio = (255.0 / image.g_maxComposante());
    Pixel pixel;
    
    if (fenetreOuverte && (dimensionX != fenetreDimensionX ||
                           dimensionY != fenetreDimensionY)) {
        fermerFenetre();
    }
    
    ouvrirFenetre(dimensionX, dimensionY, "PILG");
    
    for (x = 0; x < image.g_dimensionX(); x++) {
        for (y = 0; y < image.g_dimensionY(); y++) {
            image.g_pixel(x, y, pixel);
            
            switch (typeComposantes) {
            case PILG_BIN:
                r = v = b = (pixel.n ? 255 : 0);
                break;
                
            case PILG_NIV:
                r = v = b = pixel.g * ratio;
                break;
                
            case PILG_RVB:
                r = pixel.r * ratio;
                v = pixel.v * ratio;
                b = pixel.b * ratio;
                break;
            }
            
            for (eX = 0; eX < ECHELLE; eX++) {
                for (eY = 0; eY < ECHELLE; eY++) {
                    pointFenetre(x * ECHELLE + eX, y * ECHELLE + eY, r, v, b);
                }
            }
        }
    }
    
    afficherFenetre();
}

void messageErreur(string message) {
    cerr << "Erreur : " << message << '.' << endl;
    journal << "Erreur : " << message << '.' << endl;
}

int chaineVersEntier(string chaine, int &entier) {
    entier = atoi(chaine.c_str());
    
    if (entier == 0 && chaine != "0") {
        return 1;
    }
    
    return 0;
}

int chaineVersFlottant(string chaine, float &flottant) {
    flottant = atof(chaine.c_str());
    
    if (flottant == 0 && chaine != "0") {
        return 1;
    }
    
    return 0;
}

int caraVersEntier(char cara) {
    // int entier = (int) (0 << 8) + cara;
    // entier = entier > 0 ? entier : 256+entier;
    int i, entier = 0;
    
    for (i = 0; i < 8; i++) {
        entier += ((cara >> i) & 0x01) ? pow(2, i) : 0;
    }
    
    return entier;
}
