#define NOMBREOR 1.61803398875

void presentation() {
    cout << " ____  ___  _      ____ "  << endl
         << "|  _ \\|_ _|| |    / ___|" << endl
         << "| |_) || | | |   | |  _ "  << endl
         << "|  __/ | | | |___| |_| |"  << endl
         << "|_|   |___||_____|\\____|" << endl;
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
