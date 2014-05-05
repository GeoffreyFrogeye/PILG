#include <vector>
#include <string>

using namespace std;

int messageErreur(string message) {
    cerr << "Erreur : " << message << endl;
}

int decoupeCommande(string commande, vector< string > &decoupe) {
    // Boucle de découpage
    // vector< string > decoupe;
    string elementCourrant = "";
    bool dansLeVide = false;
    bool echape = false;
    bool vaEchapper = false;
    bool entreSimplesGuillemets = false;
    bool entreDoublesGuillemets = false;
    for (int i = 0; i < commande.length(); i++) {
        echape = false;
        if (vaEchapper) {
            vaEchapper = false;
            echape = true;
        }
        if (commande[i] == ' ' && !(echape || entreSimplesGuillemets || entreDoublesGuillemets)) {
            // cout << i << " : " << "espace" << endl;
            if (!dansLeVide) {
                // cout << "Ajout de " << elementCourrant << endl;
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            }
        } else if (commande[i] == '\\' && !echape) {
            vaEchapper = true;
        } else if (commande[i] == '\'' && !(echape || entreDoublesGuillemets)) {
            if (entreSimplesGuillemets) {
                entreSimplesGuillemets = false;
                // cout << "Ajout de " << elementCourrant << endl;
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            } else {
                entreSimplesGuillemets = true;
            }
        } else if (commande[i] == '"' && !(echape || entreSimplesGuillemets)) {
            if (entreDoublesGuillemets) {
                entreDoublesGuillemets = false;
                // cout << "Ajout de " << elementCourrant << endl;
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            } else {
                entreDoublesGuillemets = true;
            }
        } else {
            // cout << i << " : " << "else" << endl;
            elementCourrant += commande[i];
            dansLeVide = false;
        }
    }
    if (!dansLeVide) {
        // cout << "Ajout de " << elementCourrant << endl;
        decoupe.push_back(elementCourrant);
    }
}

int analyserDecoupe(vector< string > decoupe) {
    for (int i = 0; i < decoupe.size(); i++) { // DEBUG
        cout << "Argument " << i << " = " << decoupe[i] << endl;
    }
}

int boucleDeCommandes() {
    bool continuer = true;
    string commande;

    while (continuer) {
        cout << "$ ";
        getline(cin, commande);
        if (commande == "exit" || commande == "quitter") {
            continuer = false;
        } else {
            vector< string > decoupe;
            decoupeCommande(commande, decoupe);
            analyserDecoupe(decoupe);
        }
    }
    return 0;
}