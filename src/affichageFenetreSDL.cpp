#include <SDL/SDL.h>
#include <string>

int fenetreDimensionX; // Stocke les dimensions X de la fenêtre
int fenetreDimensionY; // Stocke les dimensions Y de la fenêtre
SDL_Surface *fenetreEcran;
SDL_Surface *fenetreImage;


void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /*Ici p est l'adresse du pixel que l'on veut modifier*/
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch (nbOctetsParPixel) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        /*Suivant l'architecture de la machine*/
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void setNomFenetre(std::string nom) { // Change le nom de la fenêtre
    SDL_WM_SetCaption(nom.c_str(), NULL);
}

void pointFenetre(int x, int y, int r, int v, int b) {
    // std::cout << "(" << x << ";" << y << ") = (" << r << ";" << v << ";" << b << ")" << std::endl; // DEBUG

    Uint32 pixel;

    Uint8 u_r, u_v, u_b, u_a;
    u_r = (r > 255 ? 0xff : (Uint8) r);
    u_v = (v > 255 ? 0xff : (Uint8) v);
    u_b = (b > 255 ? 0xff : (Uint8) b);
    u_a = 0xff;

    pixel = SDL_MapRGBA(fenetreImage->format, u_r, u_v, u_b, u_a);

    definirPixel(fenetreImage, x, y, pixel);
    
}

void afficherFenetre() {
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_UnlockSurface(fenetreImage);
    SDL_BlitSurface(fenetreImage, NULL, fenetreEcran, &position);
    SDL_Flip(fenetreEcran);
    SDL_LockSurface(fenetreImage);
}

void attendreFenetre() {
    SDL_Event evenement;

    while (evenement.type != SDL_QUIT) {
        SDL_WaitEvent(&evenement);
    }
}

void fermerFenetre() {
    SDL_UnlockSurface(fenetreImage);
    SDL_FreeSurface(fenetreImage);
    SDL_Quit();
}

void ouvrirFenetre(int dimensionX, int dimensionY, std::string nom) {  // Crée une fenêtre
    SDL_Init(SDL_INIT_VIDEO);
    fenetreDimensionX = dimensionX;
    fenetreDimensionY = dimensionY;
    fenetreEcran = SDL_SetVideoMode(fenetreDimensionX, fenetreDimensionY, 32, SDL_HWSURFACE);
    fenetreImage = SDL_CreateRGBSurface(SDL_HWSURFACE, fenetreDimensionX, fenetreDimensionX, 32, 0, 0, 0, 0);
    SDL_FillRect(fenetreImage, NULL, SDL_MapRGB(fenetreEcran->format, 0, 0, 0));
    setNomFenetre(nom);
    SDL_LockSurface(fenetreImage);
}
