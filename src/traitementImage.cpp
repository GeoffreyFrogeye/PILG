#include <math.h>

#define PI 3.14159265359
#define MAXCOMPOSANTEDEFAUT 255

// Gestion de fichiers
int creer(Image &sortie, unsigned int dimensionX, unsigned int dimensionY, unsigned int maxComposante, PILG_Comp typeComposantes) { // Créer une image de dimensions X et Y
    sortie = *new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
    return 0;
}

int ouvrir(Image &sortie, string nomFichier) { // Ouvrir une image existante à partir du nom du fichier ***Geoffrey

    return 1;
}

int sauver(Image entree, string nomFichier, bool ASCII, string commentaire) { // Sauvegarder l'image obtenue dans un nouveau fichier

    return 1;
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
    // Si la teinte appartient à [0;1[
    //     r1 = 0
    //     r2 = 1
    //     v1 = 1
    //     v2 = 2
    //     b1 = 2
    //     b2 = 0
    //     Valeur = Teinte
    // Sinon Si la teinte appartient à [1;2[
    //     r1 = 1
    //     r2 = 2
    //     v1 = 2
    //     v2 = 0
    //     b1 = 0
    //     b2 = 1
    //     Valeur = Teinte-1
    // Sinon Si la teinte appartient à [2;3]
    //     r1 = 2
    //     r2 = 0
    //     v1 = 0
    //     v2 = 1
    //     b1 = 1
    //     b2 = 2
    //     Valeur = Teinte-2
    // Fin Si
    // Pour x=0 à x=image.getDimensionX()
    //     Pour y=0 à y=image.getDimensionY()
    //
    //
    //
    //         pixel.r = r1+(r2-r1)*valeur
    //         pixel.v = v1+(v2-v1)*valeur
    //         pixel.b = b1+(b2-b1)*valeur
    //     Fin Pour
    // Fin Pour
    return 1;
}

int saturation(Image entree, Image &sortie, float saturation) { // Sature l'image
    // Pour x = image.g_DimensionX()
    //     Pour y = image.g_DimensionY()
    //         Ajouter la variable saturation à chaque valeur de chaque pixel
    //         Ne pas dépasser le seuil limite MaxComposante !!!
    //     Fin Pour
    // Fin Pour
    return 1;
}

int luminosite(Image entree, Image &sortie, float luminosite) { // Augmente la luminosité de l'image
    // Pour x=0 à x=image.g_DimensionX()
    //     Pour y=0 à y=image.g_DimensionY()
    //         si image.g_typeComposante=1
    //             pixel = image.g_pixel(x,y);
    //             pixel.g = luminosite*10+pixel.g;
    //             image.s_pixel(x, y, pixel);
    //         sinon si image.g_typeComposante=2
    //             pixel = image.g_pixel(x,y);
    //             pixel.r = luminosite*10+pixel.r;
    //             pixel.v = luminosite*10+pixel.v;
    //             pixel.b = luminosite*10+pixel.b;
    //             image.s_pixel(x, y, pixel);
    //         Fin si
    //     Fin Pour
    // Fin Pour
    return 1;
}

int contraste(Image entree, Image &sortie, float contraste) { // Accentue les contrastes de l'image
    // pour x=0 à x=image.g_dimensionX()
    //    pour y=0 à y=image.g_DimensionY()
    //        si image.g_typeComposante=1
    //            pixel = image.g_pixel(x,y);
    //            pixel.g = contraste*pixel.g;
    //             if pixel.g > Image.g_maxComposante
    //                 pixel.g = Image.g_maxComposante
    //             end if
    //        End If
    //    Fin Pour
    // Fin Pour


    return 1;
}

// Dessin
int trait(Image entree, Image &sortie, int x1, int y1, int x2, int y2, Pixel pixel) { // Dessine un trait d'un point (x1,y1) à un point (x2,y2)
    //    int x, y, dx, dy ;
    //    float e, e(1,0), e(0,1) ;  // valeur d’erreur et incréments
    //    dy ← y2 - y1 ;
    //    dx ← x2 - x1 ;
    //    y ← y1 ;  // rangée initiale
    //    e ← 0,0 ;  // valeur d’erreur initiale
    //    e(1,0) ← dy / dx ;
    //    e(0,1) ← -1.0 ;
    //          pour x variant de x1 jusqu’à x2 par incrément de 1 faire
    //              tracerPixel(x, y) ;
    //                  si (e ←  e + e(1,0)) ≥ 0,5 alors  // erreur pour le pixel suivant de même rangée
    //                      y ←  y + 1 ;  // choisir plutôt le pixel suivant dans la rangée supérieure
    //                      e ←  e + e(0,1) ;  // ajuste l’erreur commise dans cette nouvelle rangée
    //                  fin si ;
    //          fin pour ;

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
    // sortie=entree;
    // pour x=0 à x=image.g_dimensionX()
    //     pour y=0 à y=image.g_dimensionY()
    //         si sqrt(pow(x-x0, 2) + pow(y-y0, 2)) == r
    //             sortie.s_pixel(x, y, couleur);
    //         Fin si
    //     fin pour
    // fin pour
    return 1;
}

int disque(Image entree, Image &sortie, int x, int y, int r, Pixel couleur) {
    // sortie=entree;
    // pour x=0 à x=image.g_dimensionX()
    //     pour y=0 à y=image.g_dimensionY()
    //         si sqrt(pow(x-x0, 2) + pow(y-y0, 2)) <= r
    //             sortie.s_pixel(x, y, couleur);
    //         Fin si
    //     fin pour
    // fin pour
    return 1;
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
    // sortie = *new Image(x2-x1, y2-y1, entree.g_maxComposante(), entree.g_typeComposantes());
    // pour x=x1 à x=x2
    //    pour y=y1 à y=y2
    //         sortie.s_pixel(x, y, entree.g_pixel(x+x1, y+y1));
    //     FinPour
    // FinPour
    return 1;
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
