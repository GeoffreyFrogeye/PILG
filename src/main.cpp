#include <iostream>
#include <string>
#include "SDL/SDL.h"

using namespace std;

int main(int argc, char* args[]) {

#if defined(WIN32) // Permet de refaire fonctionner cin et cout sous Windows après démarrage de SDL
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
#endif

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Quit();

    return 0;
}

int analyserCommande(string commande) {

}
