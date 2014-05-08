#include <vector>
#include <string>
#include <iostream>

int chaineVersEntier(string chaine) {
    return (int) chaine[0];
}

void afficherImage(Image image) {
    int x, y, r, v, b, dimensionX = image.g_dimensionX(), dimensionY = image.g_dimensionY(), typeComposantes = image.g_typeComposantes();

    float ratio = (255.0 / image.g_maxComposante());
    Pixel pixel;

    if (fenetreOuverte && (dimensionX != fenetreDimensionX || dimensionY != fenetreDimensionY)) {
        fermerFenetre();
    }

    ouvrirFenetre(dimensionX, dimensionY, "PILG - Test");

    for (x = 0; x < dimensionX; x++) {
        for (y = 0; y < dimensionY; y++) {
            image.g_pixel(x, y, pixel);
            switch (typeComposantes) {
            case PILG_BIN:
                r = v = b = (pixel.n ? 255 : 0);
                break;
            case PILG_NIV:
                r = v = b = pixel.g * ratio;
                break;
            case PILG_RVB:
                r = pixel.r * ratio;
                v = pixel.v * ratio;
                b = pixel.b * ratio;
                break;
            }
            pointFenetre(x, y, r, v, b);
        }
    }

    afficherFenetre();
}

void messageErreur(string message) {
    cerr << "Erreur : " << message << '.' << endl;
}

void decoupeCommande(string commande, vector< string > &decoupe) {
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

typedef struct Commande {
    string fonction;

    int x1, x2, y1, y2;
    string fichierEntree, fichierSortie;
    Pixel couleur;
    // ...

    vector< string > argumentsPresents;
} Commande;

int analyserDecoupe(Commande &commande, vector< string > decoupe, Image const &image) {
    // for (int i = 0; i < decoupe.size(); i++) { // DEBUG
    //     cout << "Argument " << i << " = " << decoupe[i] << endl;
    // }

    commande.couleur = image.g_pixelVide();
    commande.fonction = decoupe[0];

    // Analyse des arguments
    // for (int i = 1; i < decoupe.size(); i++) {
    //     ...
    // }

    return 0;
}

bool argumentPresent(Commande commande, string argumentVoulu) {
    for (int i = 0; i < commande.argumentsPresents.size(); i++) {
        if (commande.argumentsPresents[i] == argumentVoulu) {
            return true;
        }
    }
    return false;
}

int executerCommande(Commande commande, Image &image) {
    if (commande.fonction == "rectangle") {
        commande.couleur.v = image.g_maxComposante(); // DEBUG
        rectangle(image, image, 5, 5, 10, 10, commande.couleur); // DEBUG
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "x2")
                && argumentPresent(commande, "y1") && argumentPresent(commande, "y2")
                && argumentPresent(commande, "couleur")) {
            // TODO
        } else {
            return 2;
        }
    } else {
        return 1;
    }
    return 0;
}

void procederCommande(vector< string > decoupe, Image &image) {
    Commande commande;
    switch (analyserDecoupe(commande, decoupe, image)) {
    case 0:
        switch (executerCommande(commande, image)) {
        case 0:
            break;
        case 1:
            messageErreur("Fonction inconnue");
            break;
        case 2:
            messageErreur("Arguments manquants");
            break;
        default:
            messageErreur("Impossible d'éxecuter la fonction");
        }
        break;
    default:
        messageErreur("Impossible d'analyse de la commande");
        break;
    }
}

int boucleDeCommandes(Image image) { // REPL
    bool continuer = true;
    string commandeTexte;

    while (continuer) {
        cout << "$ ";
        getline(cin, commandeTexte);
        if (commandeTexte == "quitter" || commandeTexte == "exit") {
            continuer = false;
        } else {
            vector< string > decoupe;
            decoupeCommande(commandeTexte, decoupe);
            procederCommande(decoupe, image);
            afficherImage(image);
        }
    }
}
