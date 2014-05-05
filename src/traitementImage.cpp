// Gestion de fichiers 
int creer(Image &sortie, unsigned int dimensionX, unsigned int dimensionY, unsigned int maxComposante, PILG_Comp typeComposantes) { // Créer une image de dimensions X et Y
    Image *nouvelle = new Image(dimensionX, dimensionY, maxComposante, typeComposantes);
    sortie = *nouvelle;
}

int ouvrir(Image &sortie, string nomFichier) { // Ouvrir une image existante à partir du nom du fichier ***Geoffrey

}

int sauver(Image entree, string nomFichier, bool ASCII, string commentaire) { // Sauvegarder l'image obtenue dans un nouveau fichier

}

int import(Image entree, Image &sortie, string nomFichier, int x, int y) {
    // Image fichierImporte;
    // sortie = entree
    // ouvrir(fichierImporte, nomFichier)
    // Pour x1 = 0 to x1 = fichierImporte.g_dimensionX
    //     Pour y1 = 0 to y1 = fichierImporte.g_dimensionY
    //         sortie.s_pixel(x1 + x, y1 + y, fichierImporte.g_pixel(x1, x2));
    //     FinPour
    // FinPour 

}

// Edition ***Geoffrey

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
}

int saturation(Image entree, Image &sortie, float saturation) { // Sature l'image
    // Pour x = image.g_DimensionX()
    //     Pour y = image.g_DimensionY()
    //         Ajouter la variable saturation à chaque valeur de chaque pixel
    //         Ne pas dépasser le seuil limite MaxComposante !!!
    //     Fin Pour
    // Fin Pour
}

int luminosite(Image entree, Image &sortie, float luminosite) { // Augmente la luminosité de l'image
    // Pour x=0 à x=image.g_DimensionX()
    //     Pour y=0 à y=image.g_DimensionY()
    //         si image.g_typeComposante=1
    //             pixel = image.g_point(x,y);
    //             pixel.g = luminosite*10+pixel.g;
    //             image.s_point(x, y, pixel);
    //         sinon si image.g_typeComposante=2
    //             pixel = image.g_point(x,y);
    //             pixel.r = luminosite*10+pixel.r;
    //             pixel.v = luminosite*10+pixel.v;
    //             pixel.b = luminosite*10+pixel.b;
    //             image.s_point(x, y, pixel);
    //         Fin si
    //     Fin Pour
    // Fin Pour
}

int contraste(Image entree, Image &sortie, float contraste) { // Accentue les contrastes de l'image
    // pour x=0 à x=image.g_dimensionX()
    //    pour y=0 à y=image.g_DimensionY()
    //        si image.g_typeComposante=1
    //            pixel = image.g_point(x,y);
    //            pixel.g = contraste*pixel.g;
    //             if pixel.g > Image.g_maxComposante
    //                 pixel.g = Image.g_maxComposante
    //             end if


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
    //fin procédure ;

}

int rectangle(Image entree, Image &sortie, int x1, int y1, int x2, int y2, Pixel couleur) {
    // sortie = entree    
    // pour x=x1 à x=x2
    //    pour y=y1 à y=y2
    //        sortie.s_pixel(x, y, couleur)
    //     FinPour
    // FinPour

}

int cercle(Image entree, Image &sortie, int x, int y, int r, Pixel couleur) {

}

int disque(Image entree, Image &sortie, int x, int y, int r, Pixel couleur) {

}

// Geométrie
int zoom(Image entree, Image &sortie) {

}

int pivoter(Image entree, Image &sortie) {

}

int retourner(Image entree, Image &sortie, int rotation) {

}

int redimensionner(Image entree, Image &sortie, int x1, int x2, int y1, int y2) {
    // Image *nouvelle = new Image(x2-x1, y2-y1, entree.g_maxComposante(), entree.g_typeComposantes());
    // sortie = *nouvelle;
    // pour x=x1 à x=x2
    //    pour y=y1 à y=y2
    //         sortie.s_pixel(x, y, entree.g_pixel(x+x1, y+y1));
    //     FinPour
    // FinPour
}

// Modification couleur
int convBIN(Image entree, Image &sortie) {

}

int convNIV(Image entree, Image &sortie) {

}

int convRVB(Image entree, Image &sortie) {

}

//Help
int aide() {
    //Afficher le texte suivant :
}
