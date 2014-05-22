#include <iostream>

using namespace std;

#include "affichageFenetre.cpp"
#include "image.h"
#include "utilitaires.cpp"
#include "traitementImage.cpp"
#include "analyserCommande.cpp"

int main(int argc, char *args[]) {
    #if defined(WIN32)  // Permet de refaire fonctionner cout et cerr sous Windows après démarrage de SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
    presentation();
    cout << endl;
    Image image = imageDefaut();
    int code;
    
    if (argc > 1) { // Si la commande a été entrée avec des arguments
        vector< string > decoupe;
        
        for (int i = 1; i < argc; i++) {
            decoupe.push_back(args[i]);
        }
        
        code = procederCommande(decoupe, image);
    } else {
        actualiserDimensionsEcran();
        afficherImage(image);
        boucleDeCommandes(image);
        code = 0;
    }
    
    journal.close();
    return code;
}
