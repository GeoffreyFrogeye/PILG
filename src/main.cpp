#include <iostream>
#include <string>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "traitementImage.cpp"
#include "analyserCommande.cpp"


int main(int argc, char *args[]) {
#if defined(WIN32)  // Permet de refaire fonctionner cin et cout sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

    cout << "PILG" << endl;  // Message d'entrée et de test

	if (argc > 1) {
        vector< string > decoupe;
        for (int i = 1; i < argc; i++) {
            decoupe.push_back(args[i]);
        }
        analyserDecoupe(decoupe);
    } else {
        boucleDeCommandes();
    }

    return 0;
}
