#include <iostream>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "utilitaires.cpp"
#include "traitementImage.cpp"
#include "analyserCommande.cpp"

#define NOMBREOR 1.61803398875

int main(int argc, char *args[]) {
    #if defined(WIN32)  // Permet de refaire fonctionner cout et cerr sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
    presentation();
    cout << endl;
    Image image = imageDefaut();
    
    if (argc > 1) { // Si la commande a été entrée avec des arguments
        vector< string > decoupe;
        
        for (int i = 1; i < argc; i++) {
            decoupe.push_back(args[i]);
        }
        
        procederCommande(decoupe, image);
    } else {
        afficherImage(image);
        boucleDeCommandes(image);
    }
    
    return 0;
}
