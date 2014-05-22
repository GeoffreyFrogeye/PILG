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

typedef struct {
    double t;
    double s;
    double l;
} TSL;

int rvb2tsl(Pixel entree, TSL &sortie) {
    double min, max, r = (float) entree.r / entree.maxComposante,
                     v = (float) entree.v / entree.maxComposante,
                     b = (float) entree.b / entree.maxComposante;
    min = r < v ? r : v;
    min = min  < b ? min : b;
    max = r > v ? r : v;
    max = max  > b ? max : b;
    sortie.l = (max + min) / 2;
    
    if (max == min) {
        sortie.s = 0;
        sortie.t = NAN;
    } else {
        sortie.s = sortie.l < 0.5 ? (max - min) / (max + min) : (max - min) /
                   (2 - max - min);
    }
    
    if (r == max) {
        sortie.t = (v - b) / (max - min);
    } else if (v == max) {
        sortie.t = 2 + (b - r) / (max - min);
    } else if (b == max) {
        sortie.t = 4 + (r - v) / (max - min);
    }
    
    sortie.t *= 60;
    
    if (sortie.t < 0) {
        sortie.t += 360;
    }
    
    return 0;
}

int tsl2rvb(TSL entree, Pixel &sortie) {
    double t3[3], c[3], t2, t1;
    
    while (entree.t < 0.0) {
        entree.t += 360.0;
    }
    
    while (entree.t > 360.0) {
        entree.t += -360.0;
    }
    
    if (entree.s == 0) {
        fill_n(c, 3, entree.l);
    } else {
        fill_n(t3, 3, 0);
        fill_n(c, 3, 0);
        t2 = entree.l < 0.5 ? entree.l * (1 + entree.s) : entree.l + entree.s - entree.l
             * entree.s;
        t1 = 2 * entree.l - t2;
        entree.t /= 360.0;
        t3[0] = entree.t + 1 / 3.0;
        t3[1] = entree.t;
        t3[2] = entree.t - 1 / 3.0;
        
        for (int i = 0; i <= 2; i++) {
            if (t3[i] < 0) {
                t3[i] += 1;
            }
            
            if (t3[i] > 1) {
                t3[i] -= 1;
            }
            
            if (6 * t3[i] < 1) {
                c[i] = t1 + (t2 - t1) * 6 * t3[i];
            } else if (2 * t3[i] < 1) {
                c[i] = t2;
            } else if (3 * t3[i] < 2) {
                c[i] = t1 + (t2 - t1) * ((2 / 3.0) - t3[i]) * 6;
            } else {
                c[i] = t1;
            }
        }
    }
    
    sortie.r = c[0] * sortie.maxComposante;
    sortie.v = c[1] * sortie.maxComposante;
    sortie.b = c[2] * sortie.maxComposante;
    return 0;
}

Image imageDefaut() {
    int dimY = 256, dimX = dimY * NOMBREOR, maxComposante = 255;
    Image imageRoue(dimX, dimY, maxComposante, PILG_RVB);
    int x, y;
    TSL tsl;
    Pixel pointRoue = imageRoue.g_pixelVide();
    tsl.s = 1;
    
    for (x = 0; x < dimX; x++) {
        for (y = 0; y < dimY; y++) {
            tsl.t = ((float) x / dimX) * 360;
            tsl.l = 1 - ((float) y / dimY);
            tsl2rvb(tsl, pointRoue);
            imageRoue.s_pixel(x, y, pointRoue);
        }
    }
    
    return imageRoue;
}

void afficherImage(Image image) {
#define MARGE 100
    int x, y, r, v, b, eX, eY, echelle, contenableX, contenableY,
        dimensionX = image.g_dimensionX(),
        dimensionY = image.g_dimensionY(),
        typeComposantes = image.g_typeComposantes();
    float ratio = (255.0 / image.g_maxComposante());
    Pixel pixel;
    // Calcul de l'échelle
    contenableX = (ecranX - MARGE) / dimensionX;
    contenableY = (ecranY - MARGE) / dimensionY;
    echelle = (contenableX > contenableY ? contenableY : contenableX);
    echelle = (echelle > 0 ? echelle : 1);
    dimensionX = dimensionX * echelle;
    dimensionY = dimensionY * echelle;
    // journal << "Fenêtre: Image(" << image.g_dimensionX() << ";" <<
    // image.g_dimensionY() << "), Echelle(" << echelle << "), Fenetre(" <<
    // dimensionX << ";" << dimensionY << ")" << endl;
    
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
            
            for (eX = 0; eX < echelle; eX++) {
                for (eY = 0; eY < echelle; eY++) {
                    pointFenetre(x * echelle + eX, y * echelle + eY, r, v, b);
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
