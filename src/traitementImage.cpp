// Gestion de fichiers 
int creer(Image &sortie, int dimensionX, int dimensionY, int typeComposante, int maxComposante) { // Créer une image de dimensions X et Y

}
int ouvrir(Image &sortie, string nomFichier) { // Ouvrir une image existante à partir du nom du fichier

}
int sauver(Image entree, string nomFichier) { // Sauvegarder l'image obtenue dans un nouveau fichier

}
int import(Image entree, Image &sortie, string nomFichier, int x, int y) {

}

// Edition
int copier() { // Copie tous les pixels

}
int couper() { // Copie et remplace par du blanc tous les pixels

}
int coller() { // Coller les pixels copiés ou coupés.

}
int annuler() { // Annuler la dernière action.

}
int refaire() { // répeter la dernière action

}

// Couleur
int teinte(Image entree, Image &sortie, float teinte) { // Change la teinte de l'image
    // Si la teinte appartient à [0;1[
        // r1 = 0
        // r2 = 1
        // v1 = 1
        // v2 = 2
        // b1 = 2
        // b2 = 0
        // Valeur = Teinte
    // Sinon Si la teinte appartient à [1;2[
        // r1 = 1
        // r2 = 2
        // v1 = 2
        // v2 = 0
        // b1 = 0
        // b2 = 1
        // Valeur = Teinte-1
    // Sinon Si la teinte appartient à [2;3]
        // r1 = 2
        // r2 = 0
        // v1 = 0
        // v2 = 1
        // b1 = 1
        // b2 = 2
        // Valeur = Teinte-2
    // Fin Si
    // Pour x=0 à x=image.getDimensionX()
        // Pour y=0 à y=image.getDimensionY()
            //
            //
            //
            // pixel.r = r1+(r2-r1)*valeur
            // pixel.v = v1+(v2-v1)*valeur
            // pixel.b = b1+(b2-b1)*valeur
        // Fin Pour
    // Fin Pour
}

int saturation(Image entree, Image &sortie, float saturation) { // Sature l'image
    // Pour x = xMin to x = xMax
        // Pour y = yMin to y = yMax
            // Ajouter la variable saturation à chaque valeur de chaque pixel
            // Ne pas dépasser le seuil limite MaxComposante !!!
        // Fin Pour
    // Fin Pour
}
int luminosite(Image entree, Image &sortie, float luminosite) { // Augmente la luminosité de l'image
    // Pour x=0 à x=image.g_DimensionX()
        // Pour y=0 à y=image.g_DimensionY()
            // si image.g_typeComposante=1
                // pixel = image.g_point(x,y);
                // pixel.g = luminosite*10+pixel.g;
                // image.s_point(x, y, pixel);
            // sinon si image.g_typeComposante=2
                // pixel = image.g_point(x,y);
                // pixel.r = luminosite*10+pixel.r;
                // pixel.v = luminosite*10+pixel.v;
                // pixel.b = luminosite*10+pixel.b;
                // image.s_point(x, y, pixel);
            // Fin si
        // Fin Pour
    // Fin Pour
}
int contraste(Image entree, Image &sortie, float contraste) { // Accentue les contrastes de l'image
    // pour x=0 à x=image.g_dimensionX()
        //pour y=0 à x=image.g_DimensionY()
            //si image.g_typeComposante=1
                //pixel = image.g_point(x,y);
                //pixel.g = contraste*pixel.g;
                // if pixel.g > Image.g_maxComposante
                    // pixel.g = Image.g_maxComposante
                // end if


}

// Dessin
int trait(Image entree, Image &sortie, int x1, int y1, int x2, int y2, Pixel, pixel) { // Dessine un trait d'un point (x1,y1 à un point (x2,y2)

}
int rectangle(Image entree, Image &sortie, int x1, int y1, int x2, int y2) {

}
int cercle(Image entree, Image &sortie, int x, int y, int r) {

}

// Geométrie
int zoom(Image entree, Image &sortie) {

}
int pivoter(Image entree, Image &sortie) {

}
int redimensionner(Image entree, Image &sortie) {

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

}