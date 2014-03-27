// Gestion de fichiers 
int creer(int dimensionX, int dimensionY, int typeComposante, int maxComposante);
int ouvrir(string nomFichier);
int sauver(string nomFichier);
int import(string nomFichier, int x, int y);

// Edition
int copier();
int couper();
int coller();
int annuler();
int refaire();

// Couleur
int teinte(int teinte);
int saturation(int saturation);
int luminosite(int luminosite);
int contraste(int contraste);

// Dessin
int trait(int x1, int y1, int x2, int y2);
int rectangle(int x1, int y1, int x2, int y2);
int cercle(int x, int y, int r);

// Geométrie
int zoom();
int pivoter();
int redimensionner();

// Modification couleur
int convBIN();
int convNIV();
int convRVB();

//Help
int aide();
