#include <fstream>

#define PI 3.14159265359
#define MAXCOMPOSANTEDEFAUT 255
#define FICHIER_SEPARATEUR (char) 0x0a

typedef enum {PILG_TYPE, PILG_DIMENSIONS, PILG_MAXCOMPOSANTE, PILG_IMAGE} PILG_OuvrirEtape;

// Gestion de fichiers
int creer(Image &sortie, int dimensionX, int dimensionY, int maxComposante,
          PILG_Comp typeComposantes) {  // Créer une image de dimensions X et Y
    sortie = *new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
    return 0;
}

int ouvrir(Image &sortie,
           string nomFichier) {   // Ouvrir une image existante à partir du nom du fichier
    // Ouverture du fichier
    journal << "→ " << nomFichier << endl;
    ifstream streamFichier(nomFichier.c_str(), ios::in);
    
    if (streamFichier) {
        // Calcul de la taille (en octets) du fichier
        streamFichier.seekg(0, ios::end);
        int tailleFichier(streamFichier.tellg());
        // Stockage du fichier dans une chaîne
        streamFichier.seekg(0, ios::beg);
        char *fichier_caracteres = new char [tailleFichier];
        streamFichier.read(fichier_caracteres, tailleFichier);
        streamFichier.close();
        // Variables d'informations
        char cara;
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
        int i(0);
        Pixel pixel;
        string tmpASCII;
        char RVBcomposante(0);   // Composante actuelle pour RVB
        
        for (int c(0); c < tailleFichier; c++) {
            cara = fichier_caracteres[c];
            
            if (ouvrirEtape != PILG_IMAGE) {
                if (cara == FICHIER_SEPARATEUR) {   // En cas de nouvel élément
                    if (element[0] !=
                            '#') {   // Si c'est un commentaire, on passe à l'élément suivant
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
                            journal << "Type de fichier : " << element << " (" << ((
                                        typeComposantes == 0) ? "Noir et Blanc" : ((typeComposantes == 1) ?
                                                "Niveaux de gris" : "Rouge / Vert / Bleu")) << ", " << (ASCII ? "ASCII" :
                                                        "Brut") << ")" << endl;
                            break;
                            
                        case PILG_DIMENSIONS: {
                            bool espaceDepasse(false);
                            string dimensionXchaine("");
                            string dimensionYchaine("");
                            
                            for (int j(0); j < element.size(); j++) {
                                if (element[j] == ' ') {
                                    espaceDepasse = true;
                                } else if (espaceDepasse) {
                                    dimensionYchaine += element[j];
                                } else {
                                    dimensionXchaine += element[j];
                                }
                            }
                            
                            chaineVersEntier(dimensionXchaine, dimensionX);
                            chaineVersEntier(dimensionYchaine, dimensionY);
                            
                            if (!espaceDepasse || dimensionX == 0 || dimensionY == 0) {
                                return 5;
                            }
                            
                            journal << "Dimensions : " << dimensionX << " px / " << dimensionY << "px" <<
                                    endl;
                                    
                            if (typeComposantes == PILG_BIN) {
                                ouvrirEtape = PILG_IMAGE;
                            } else {
                                ouvrirEtape = PILG_MAXCOMPOSANTE;
                            }
                        }
                        break;
                        
                        case PILG_MAXCOMPOSANTE:
                            chaineVersEntier(element, maxComposante);
                            journal << "Maximum de composante" << ((typeComposantes == 2) ? "s" : "") <<
                                    " : "
                                    << maxComposante << endl;
                            ouvrirEtape = PILG_IMAGE;
                            break;
                            
                        default:
                            return 4;
                            break;
                        }
                        
                        if (ouvrirEtape == PILG_IMAGE) {
                            sortie = *new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
                            pixel = sortie.g_pixelVide();
                        }
                    }
                    
                    element = "";
                } else {
                    element += cara;
                }
            } else {
                if (ASCII) {
                    if (typeComposantes == PILG_BIN) {
                        if (cara != FICHIER_SEPARATEUR) {
                            pixel.n = (cara == 0x31) ? false : true;
                            sortie.s_pixel(x, y, pixel);
                            x++;
                        }
                    } else {
                        if (cara == FICHIER_SEPARATEUR) {
                            if (typeComposantes == PILG_RVB) {
                                switch (RVBcomposante) {
                                case 0:
                                    chaineVersEntier(tmpASCII, pixel.r);
                                    RVBcomposante = 1;
                                    break;
                                    
                                case 1:
                                    chaineVersEntier(tmpASCII, pixel.v);
                                    RVBcomposante = 2;
                                    break;
                                    
                                case 2:
                                    chaineVersEntier(tmpASCII, pixel.b);
                                    RVBcomposante = 0;
                                    sortie.s_pixel(x, y, pixel);
                                    x++;
                                    break;
                                }
                            } else {
                                chaineVersEntier(tmpASCII, pixel.g);
                                sortie.s_pixel(x, y, pixel);
                                x++;
                            }
                            
                            tmpASCII = "";
                        } else {
                            tmpASCII += cara;
                        }
                    }
                } else {
                    if (typeComposantes == PILG_BIN) {
                        for (i = 7; i >= 0; i--) {
                            pixel.n = !((cara >> i) & 0x01);
                            sortie.s_pixel(x, y, pixel);
                            x++;
                            
                            if (x >= dimensionX) {
                                y++;
                                x = 0;
                            }
                        }
                    } else {
                        if (typeComposantes == PILG_RVB) {
                            switch (RVBcomposante) {
                            case 0:
                                pixel.r = caraVersEntier(cara);
                                RVBcomposante = 1;
                                break;
                                
                            case 1:
                                pixel.v = caraVersEntier(cara);
                                RVBcomposante = 2;
                                break;
                                
                            case 2:
                                pixel.b = caraVersEntier(cara);
                                RVBcomposante = 0;
                                sortie.s_pixel(x, y, pixel);
                                x++;
                                break;
                            }
                        } else {
                            pixel.g = caraVersEntier(cara);
                            sortie.s_pixel(x, y, pixel);
                            x++;
                        }
                    }
                }
                
                if (x >= dimensionX) {
                    y++;
                    x += -dimensionX;
                }
            }
        }
    } else {
        return 1;
    }
    
    journal << endl;
    return 0;
}

int sauver(Image entree, string nomFichier, bool ASCII,
           string commentaire) {   // Sauvegarder l'image obtenue dans un nouveau fichier
    ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
    char numero;
    
    switch (entree.g_typeComposantes()) {
    case PILG_BIN:
        numero = ASCII ? '1' : '4';
        break;
        
    case PILG_NIV:
        numero = ASCII ? '2' : '5';
        break;
        
    case PILG_RVB:
        numero = ASCII ? '3' : '6';
        break;
        
    default:
        return 1;
    }
    
    fichier << "P" << numero << FICHIER_SEPARATEUR;
    
    if (commentaire != "") {
        fichier << "# " << commentaire << FICHIER_SEPARATEUR;
    }
    
    fichier << entree.g_dimensionX() << " " << entree.g_dimensionY() <<
            FICHIER_SEPARATEUR;
            
    if (entree.g_typeComposantes() != PILG_BIN) {
        fichier << entree.g_maxComposante() << FICHIER_SEPARATEUR;;
    }
    
    Pixel pixel;
    char brutBINpixel;
    int brutBINpixelRang = 7;
    
    for (int y = 0; y < entree.g_dimensionY(); y++) {
        for (int x = 0; x < entree.g_dimensionX(); x++) {
            entree.g_pixel(x, y, pixel);
            
            switch (entree.g_typeComposantes()) {
            case PILG_BIN:
                if (ASCII) {
                    if (pixel.n) {
                        fichier << '0';
                    } else {
                        fichier << '1';
                    }
                } else {
                    if (pixel.n) {
                        brutBINpixel &= ~(1 << brutBINpixelRang);
                    } else {
                        brutBINpixel |= 1 << brutBINpixelRang;
                    }
                    
                    brutBINpixelRang--;
                    
                    if (brutBINpixelRang < 0) {
                        fichier << brutBINpixel;
                        brutBINpixelRang = 7;
                    }
                }
                
                break;
                
            case PILG_NIV:
                if (ASCII) {
                    fichier << pixel.g << FICHIER_SEPARATEUR;
                } else {
                    fichier << (char) pixel.g;
                }
                
                break;
                
            case PILG_RVB:
                if (ASCII) {
                    fichier << pixel.r << FICHIER_SEPARATEUR
                            << pixel.v << FICHIER_SEPARATEUR
                            << pixel.b << FICHIER_SEPARATEUR;
                } else {
                    fichier << (char) pixel.r
                            << (char) pixel.v
                            << (char) pixel.b;
                }
                
                break;
                
            default:
                return 1;
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


int teinte(Image entree, Image &sortie,
           float teinte) {   // Change la teinte de l'image
    // for (int x = 0, x = image.g_dimensionX(), x++) {
    //     for (int y = 0, y = image.g_dimensionY(), y++) {
    //         rvbVersTsl();
    //         g_pixel(x, y);
    //     }
    // }
    // return 1;
}

int saturation(Image entree, Image &sortie,
               float saturation) {   // Sature l'image
    // Utilisation de la méthode TSL
    return 1;
}

int luminosite(Image entree, Image &sortie,
               float luminosite) {   // Augmente la luminosité de l'image
    // Utilisation de la méthode TSL
    return 1;
}

int contraste(Image entree, Image &sortie,
              float contraste) {   // Accentue les contrastes de l'image
    // À voir
    return 1;
}

// Dessin
int trait(Image entree, Image &sortie, int x1, int y1, int x2, int y2,
          Pixel couleur) {  // Dessine un trait d'un point (x1,y1) à un point (x2,y2)
    int x;
    sortie = entree;
    
    for (x = 0; x <= x2 - x1; x++) {
        // cout << "(" << x << ";__) a=" << ((float) x / (x2 - x1)) << " yD=" <<
        //      (y2 - y1) * ((float)x / (x2 - x1)) << endl;
        sortie.s_pixel(x1 + x, y1 + (y2 - y1) * ((float) x / (x2 - x1)), couleur);
    }
    
    return 0;
}

int rectangle(Image entree, Image &sortie, int x1, int y1, int x2, int y2,
              Pixel couleur) {
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
            if ((int) sqrt(pow(x - x0, 2) + pow(y - y0, 2)) == r) {
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
            if ((int) sqrt(pow(x - x0, 2) + pow(y - y0, 2)) <= r) {
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
    rotation = rotation % 4;
    int x, y;
    Pixel pixel;
    
    if (rotation == 0) {
        sortie = entree;
    } else {
        if (rotation == 2) {
            sortie = entree.g_vide();
        } else {
            sortie = *new Image(entree.g_dimensionY(), entree.g_dimensionX(),
                                entree.g_maxComposante(), entree.g_typeComposantes());
        }
        
        for (x = 0; x < entree.g_dimensionX(); x++) {
            for (y = 0; y < entree.g_dimensionY(); y++) {
                entree.g_pixel(x, y, pixel);
                
                switch (rotation) {
                case 1:
                    sortie.s_pixel(entree.g_dimensionY() - y - 1, x, pixel);
                    break;
                    
                case 2:
                    journal << "5";
                    sortie.s_pixel(entree.g_dimensionX() - x - 1, entree.g_dimensionY() - y - 1,
                                   pixel);
                    break;
                    
                case 3:
                    sortie.s_pixel(y, entree.g_dimensionX() - x - 1, pixel);
                    break;
                    
                default:
                    journal << "6";
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int redimensionner(Image entree, Image &sortie, int x1, int y1, int x2,
                   int y2) {
    sortie = *new Image(x2 - x1, y2 - y1, entree.g_maxComposante(),
                        entree.g_typeComposantes());
    Pixel pixel;
    
    for (int x = 0; x <= x2 - x1; x++) {
        for (int y = 0; y <= y2 - y1; y++) {
            entree.g_pixel(x1 + x, y1 + y, pixel);
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
                    pixelF.n = (pixelI.g > (entree.g_maxComposante() / 2));
                    break;
                    
                case PILG_RVB:
                    pixelF.n = ((pixelI.r + pixelI.v + pixelI.b) / 3 > (entree.g_maxComposante() /
                                2));
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
        sortie = *new Image(entree.g_dimensionX(), entree.g_dimensionY(),
                            MAXCOMPOSANTEDEFAUT, PILG_NIV);
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
                    pixelF.g = (pixelI.r + pixelI.v + pixelI.b) / 3.0 / entree.g_maxComposante() *
                               sortie.g_maxComposante();
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
    if (entree.g_typeComposantes() == PILG_RVB) {
        sortie = entree;
    } else {
        sortie = *new Image(entree.g_dimensionX(), entree.g_dimensionY(),
                            MAXCOMPOSANTEDEFAUT, PILG_RVB);
        Pixel pixelI, pixelF;
        pixelF = sortie.g_pixelVide();
        
        for (int x = 0; x <= entree.g_dimensionX(); x++) {
            for (int y = 0; y <= entree.g_dimensionY(); y++) {
                entree.g_pixel(x, y, pixelI);
                
                switch (entree.g_typeComposantes()) {
                case PILG_BIN:
                    pixelF.r = pixelF.v = pixelF.b = (pixelI.n ? sortie.g_maxComposante() : 0);
                    break;
                    
                case PILG_NIV:
                    pixelF.r = pixelF.v = pixelF.b = (float) pixelI.g / entree.g_maxComposante() *
                                                     sortie.g_maxComposante();
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

// Aide
int aide() {
    // Afficher le texte suivant :
    return 1;
}
