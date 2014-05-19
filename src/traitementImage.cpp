#include <math.h>
#include <fstream>

#define PI 3.14159265359
#define MAXCOMPOSANTEDEFAUT 255

typedef enum {PILG_TYPE, PILG_DIMENSIONS, PILG_MAXCOMPOSANTE, PILG_IMAGE} PILG_OuvrirEtape;

// Gestion de fichiers
int creer(Image &sortie, unsigned int dimensionX, unsigned int dimensionY, unsigned int maxComposante, PILG_Comp typeComposantes) { // Créer une image de dimensions X et Y
    sortie = *new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
    return 0;
}

int ouvrir(Image &sortie, string nomFichier) { // Ouvrir une image existante à partir du nom du fichier ***Geoffrey
    // Ouverture du fichier
    ifstream streamFichier(nomFichier.c_str(), ios::in);
    if (streamFichier) {
        // Calcul de la taille (en octets) du fichier
        streamFichier.seekg(0, ios::end);
        int tailleFichier (streamFichier.tellg());

        // Stockage du fichier dans une chaîne
        streamFichier.seekg(0, ios::beg);
        char *caracteres = new char [tailleFichier];
        streamFichier.read(caracteres, tailleFichier);
        string fichier_caracteres(caracteres);
        delete[] caracteres;
        streamFichier.close();

        // Variables d'informations
        PILG_OuvrirEtape ouvrirEtape(PILG_TYPE);
        bool ASCII(false);
        int dimensionX;
        int dimensionY;
        int maxComposante;
        PILG_Comp typeComposantes;

        // Variables de traitement du fichier
        string element("");
        int x(0);
        int y(0);
        string pixelASCII;
        int RVBcomposante(0); // Composante actuelle pour RVB

        for (int c(0); c < tailleFichier; c++) {
            if (ouvrirEtape != PILG_IMAGE) {
                if (fichier_caracteres[c] ==  (char) 0x0a) { // En cas de nouvel élément
                    if (element[0] != '#') { // Si c'est un commentaire, on passe à l'élément suivant
                        switch (ouvrirEtape) {
                        case PILG_TYPE:
                            if (element.length() == 2 && element[0] == 'P') {
                                switch (element[1]) {
                                case '1':
                                case '4':
                                    typeComposantes = PILG_BIN;
                                    break;
                                case '2':
                                case '5':
                                    typeComposantes = PILG_NIV;
                                    break;
                                case '3':
                                case '6':
                                    typeComposantes = PILG_RVB;
                                    break;
                                default:
                                    return 3;
                                    break;
                                }
                                switch (element[1]) {
                                case '1':
                                case '2':
                                case '3':
                                    ASCII = true;
                                    break;
                                case '4':
                                case '5':
                                case '6':
                                    ASCII = false;
                                    break;
                                default:
                                    return 3;
                                    break;
                                }
                            } else {
                                return 3;
                            }

                            ouvrirEtape = PILG_DIMENSIONS;
#if DEBUG
                            cout << "Type de fichier : " << element << " (" << ((typeComposantes == 0) ? "Noir et Blanc" : ((typeComposantes == 1) ? "Niveaux de gris" : "Rouge / Vert / Bleu")) << ", " << (ASCII ? "ASCII" : "Brut") << ")" << endl;
#endif
                            break;

                        case PILG_DIMENSIONS: {
                            bool espaceDepasse(false);
                            string dimensionXchaine("");
                            string dimensionYchaine("");
                            for (int j(0); j < element.size(); j++) {
                                if (element[j] == ' ') {
                                    espaceDepasse = true;
                                } else if (espaceDepasse) {
                                    dimensionXchaine += element[j];
                                } else {
                                    dimensionYchaine += element[j];
                                }
                            }
                            chaineVersEntier(dimensionXchaine, dimensionX);
                            chaineVersEntier(dimensionYchaine, dimensionY);
                            if (!espaceDepasse || dimensionX == 0 || dimensionY == 0) {
                                return 5;
                            }
#if DEBUG
                            cout << "Dimensions : " << dimensionX << " px / " << dimensionY << "px" << endl;
#endif
                            if (typeComposantes == PILG_BIN) {
                                ouvrirEtape = PILG_IMAGE;
                            } else {
                                ouvrirEtape = PILG_MAXCOMPOSANTE;
                            }
                        }
                        break;
                        case PILG_MAXCOMPOSANTE:
                            chaineVersEntier(element, maxComposante);
#if DEBUG
                            cout << "Maximum de composante" << ((typeComposantes == 2) ? "s" : "") << " : " << maxComposante << endl;
#endif
                            ouvrirEtape = PILG_IMAGE;
                            break;

                        default:
                            return 4;
                            break;
                        }
                        element = "";
                        if (ouvrirEtape == PILG_IMAGE) {
                            sortie = *new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
                        }
                    }
                } else {
                    element += fichier_caracteres[c];
                }
            } else {
                // ...
            }
        }
    } else {
        return 1;
    }
#if DEBUG
    cout << endl << endl;
#endif

    return 0;
}

int sauver(Image entree, string nomFichier, bool ASCII, string commentaire) { // Sauvegarder l'image obtenue dans un nouveau fichier
    ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
#define FICHIER_SEPARATEUR (char) 0x0a
    if (entree.g_typeComposantes() == PILG_RVB && ASCII) {
        fichier << "P6";
    } else {
        return 1;
    }
    fichier << FICHIER_SEPARATEUR;
    // if (commentaire) {
    //     fichier << "#" << commentaire << FICHIER_SEPARATEUR;
    // }
    fichier << entree.g_dimensionX() << " " << entree.g_dimensionY() << FICHIER_SEPARATEUR;
    
    if (entree.g_typeComposantes() != PILG_BIN) {
        fichier << entree.g_maxComposante() << FICHIER_SEPARATEUR;;
    }
    Pixel pixel;
    for (int x = 0; x <= entree.g_dimensionX(); x++) {
        for (int y = 0; y <= entree.g_dimensionY(); y++) {
            if (entree.g_typeComposantes() == PILG_RVB && ASCII) {
                fichier << pixel.r << FICHIER_SEPARATEUR << pixel.v << FICHIER_SEPARATEUR << pixel.b << FICHIER_SEPARATEUR;
            }
        }
    }
    fichier.close();
    return 0;
}

int importer(Image entree, Image &sortie, string nomFichier, int x, int y) {
    // Image fichierImporte;
    // sortie = entree
    // ouvrir(fichierImporte, nomFichier)
    // Pour x1 = 0 to x1 = fichierImporte.g_dimensionX
    //     Pour y1 = 0 to y1 = fichierImporte.g_dimensionY
    //         sortie.s_pixel(x1 + x, y1 + y, fichierImporte.g_pixel(x1, x2));
    //     FinPour
    // FinPour

    return 1;
}

// Couleur


int teinte(Image entree, Image &sortie, float teinte) { // Change la teinte de l'image
    // for (int x = 0, x = image.g_DimensionX(), x++) {
    //     for (int y = 0, y = image.g_DimensionY(), y++) {
    //         rvbVersTsl();
    //         g_pixel(x, y);

    //     }
    // }
    // return 1;
}

int saturation(Image entree, Image &sortie, float saturation) { // Sature l'image
    // Utilisation de la méthode TSL
    return 1;
}

int luminosite(Image entree, Image &sortie, float luminosite) { // Augmente la luminosité de l'image
    // Utilisation de la méthode TSL
    return 1;
}

int contraste(Image entree, Image &sortie, float contraste) { // Accentue les contrastes de l'image
    // À voir
    return 1;
}

// Dessin
int trait(Image entree, Image &sortie, int x1, int y1, int x2, int y2, Pixel couleur) { // Dessine un trait d'un point (x1,y1) à un point (x2,y2)
    // int x, y, dx, dy;
    // float e, e(1, 0), e(0, 1) ; // valeur d’erreur et incréments
    // dy = y2 - y1 ;
    // dx = x2 - x1 ;
    // y = y1 ;  // rangée initiale
    // e = 0, 0 ; // valeur d’erreur initiale
    // e(1, 0) = dy / dx ;
    // e(0, 1) = -1.0 ;
    // for (x = x1; x <= x2; x++) {
    //     sortie.s_pixel(x, y, couleur);
    //     if ((e =  e + e(1, 0)) >= 0, 5) { // erreur pour le pixel suivant de même rangée
    //         y =  y + 1 ;  // choisir plutôt le pixel suivant dans la rangée supérieure
    //         e =  e + e(0, 1) ; // ajuste l’erreur commise dans cette nouvelle rangée
    //     }
    // }

    // return 0;
    return 1;
}

int rectangle(Image entree, Image &sortie, int x1, int y1, int x2, int y2, Pixel couleur) {
    sortie = entree;
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            sortie.s_pixel(x, y, couleur);
        }
    }

    return 0;
}

int cercle(Image entree, Image &sortie, int x0, int y0, int r, Pixel couleur) {
    sortie = entree;
    for (int x = 0; x <= entree.g_dimensionX(); x++) {
        for (int y = 0; y <= entree.g_dimensionY(); y++) {
            if (sqrt(pow(x - x0, 2) + pow(y - y0, 2)) == r) {
                sortie.s_pixel(x, y, couleur);
            }
        }
    }
    return 0;
}

int disque(Image entree, Image &sortie, int x0, int y0, int r, Pixel couleur) {

    sortie = entree;
    for (int x = 0; x <= entree.g_dimensionX(); x++) {
        for (int y = 0; y <= entree.g_dimensionY(); y++) {
            if (sqrt(pow(x - x0, 2) + pow(y - y0, 2)) <= r) {
                sortie.s_pixel(x, y, couleur);
            }
        }
    }
    return 0;
}

// Geométrie
int zoom(Image entree, Image &sortie) {

    return 1;
}

int pivoter(Image entree, Image &sortie, int x0, int y0, float angle) {
    sortie = entree.g_vide();
    float xF, yF, angleF, xI, yI, angleI, h;
    Pixel pixel = entree.g_pixelVide();
    for (xF = 0; xF < entree.g_dimensionX(); xF++) {
        for (yF = 0; yF < entree.g_dimensionY(); yF++) {
            if (xF == x0 && yF == y0) {
                xI = x0;
                yI = y0;
            } else {
                angleF = atan((yF - y0) / (xF - x0));
                angleF = (xF - x0 < 0 ? angleF + PI : angleF);
                angleI = angleF - angle;
                h = sqrt(pow(xF - x0, 2) + pow(yF - y0, 2));
                xI = cos(angleI) * h + x0;
                yI = sin(angleI) * h + y0;
            }
            entree.g_pixel((int) xI, (int) yI, pixel);
            sortie.s_pixel((int) xF, (int) yF, pixel);
        }
    }
    return 0;
}

int retourner(Image entree, Image &sortie, int rotation) {

    return 1;
}

int redimensionner(Image entree, Image &sortie, int x1, int x2, int y1, int y2) {

    sortie = *new Image(x2 - x1, y2 - y1, entree.g_maxComposante(), entree.g_typeComposantes());
    Pixel pixel = entree.g_pixelVide();
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            entree.g_pixel(x + x1, y + y1, pixel);
            sortie.s_pixel(x, y, pixel);
        }
    }
    return 0;
}

// Modification couleur
int convBIN(Image entree, Image &sortie) {
    if (entree.g_typeComposantes() == PILG_BIN) {
        sortie = entree;
    } else {
        sortie = *new Image(entree.g_dimensionX(), entree.g_dimensionY(), 0, PILG_BIN);
        Pixel pixelI, pixelF;
        pixelF = sortie.g_pixelVide();
        for (int x = 0; x <= entree.g_dimensionX(); x++) {
            for (int y = 0; y <= entree.g_dimensionY(); y++) {
                entree.g_pixel(x, y, pixelI);
                switch (entree.g_typeComposantes()) {
                case PILG_NIV:
                    pixelF.n = (pixelI.g > entree.g_maxComposante() / 2);
                    break;
                case PILG_RVB:
                    pixelF.n = ((pixelI.r + pixelI.v + pixelI.b) / 3 > entree.g_maxComposante() / 2);
                    break;
                default:
                    return 2;
                }
                sortie.s_pixel(x, y, pixelF);
            }
        }
    }
    return 0;
}

int convNIV(Image entree, Image &sortie) {
    if (entree.g_typeComposantes() == PILG_NIV) {
        sortie = entree;
    } else {
        sortie = *new Image(entree.g_dimensionX(), entree.g_dimensionY(), MAXCOMPOSANTEDEFAUT, PILG_NIV);
        Pixel pixelI, pixelF;
        pixelF = sortie.g_pixelVide();
        for (int x = 0; x <= entree.g_dimensionX(); x++) {
            for (int y = 0; y <= entree.g_dimensionY(); y++) {
                entree.g_pixel(x, y, pixelI);
                switch (entree.g_typeComposantes()) {
                case PILG_BIN:
                    pixelF.g = (pixelI.n ? sortie.g_maxComposante() : 0);
                    break;
                case PILG_RVB:
                    pixelF.g = (pixelI.r + pixelI.v + pixelI.b) / 3.0 / entree.g_maxComposante() * sortie.g_maxComposante();
                    break;
                default:
                    return 1;
                }
                sortie.s_pixel(x, y, pixelF);
            }
        }
    }
    return 0;
}

int convRVB(Image entree, Image &sortie) {
    return 1;
}

//Help
int aide() {
    //Afficher le texte suivant :
    return 1;
}
