#include <vector>
#include <string>
#include <iostream>

void afficherImage(Image image) {
    int x, y, r, v, b, dimensionX = image.g_dimensionX(), dimensionY = image.g_dimensionY(), typeComposantes = image.g_typeComposantes();

    float ratio = (255.0 / image.g_maxComposante());
    Pixel pixel;

    if (fenetreOuverte && (dimensionX != fenetreDimensionX || dimensionY != fenetreDimensionY)) {
        fermerFenetre();
    }

    ouvrirFenetre(dimensionX, dimensionY, "PILG");

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
    float angle;
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

    // // Analyse des arguments
    for (int i = 1; i < decoupe.size(); i++) {
        if (decoupe[i].at(0) == '-') {
            if (decoupe[i] == "-x1" || decoupe[i] == "-x0" || decoupe[i] == "-x") {
                commande.argumentsPresents.push_back("x1");
                i++;
                if (chaineVersEntier(decoupe[i], commande.x1)) {
                    return 3;
                }
            } else if (decoupe[i] == "-y1" || decoupe[i] == "-y0" || decoupe[i] == "-y") {
                commande.argumentsPresents.push_back("y1");
                i++;
                if (chaineVersEntier(decoupe[i], commande.y1)) {
                    return 3;
                }
            } else if (decoupe[i] == "-x2") {
                commande.argumentsPresents.push_back("x2");
                i++;
                if (chaineVersEntier(decoupe[i], commande.x2)) {
                    return 3;
                }
            } else if (decoupe[i] == "-y2") {
                commande.argumentsPresents.push_back("y2");
                i++;
                if (chaineVersEntier(decoupe[i], commande.y2)) {
                    return 3;
                }
            } else if (decoupe[i] == "-couleur" || decoupe[i] == "-c") {
                commande.argumentsPresents.push_back("couleur");
                i++;
                commande.couleur = image.g_pixelVide();
                switch (image.g_typeComposantes()) {
                case PILG_BIN:
                    if (decoupe[i] == "b" || decoupe[i] == "1") {
                        commande.couleur.n = true;
                    } else if (decoupe[i] == "n" || decoupe[i] == "0") {
                        commande.couleur.n = false;
                    } else {
                        return 4;
                    }
                    break;
                case PILG_NIV:
                    int g;
                    if (!chaineVersEntier(decoupe[i], g)) {
                        return 3;
                    }
                    if (g > image.g_maxComposante()) {
                        return 5;
                    }
                    commande.couleur.g = g;
                    break;
                case PILG_RVB:
                    int composante = 0;
                    string chaineCourante = "";
                    int entierCourant = 0;
                    for (int iS = 0; iS <= decoupe[i].length(); iS++) {
                        if (decoupe[i][iS] == ':' || iS == decoupe[i].length()) {
                            if (chaineVersEntier(chaineCourante, entierCourant)) {
                                return 3;
                            }
                            if (entierCourant > image.g_maxComposante()) {
                                return 5;
                            }
                            switch (composante) {
                            case 0:
                                commande.couleur.r = entierCourant;
                                break;
                            case 1:
                                commande.couleur.v = entierCourant;
                                break;
                            case 2:
                                commande.couleur.b = entierCourant;
                                break;
                            default:
                                return 6;
                            }
                            chaineCourante = "";
                            entierCourant = 0;
                            composante++;
                        } else {
                            chaineCourante += decoupe[i][iS];
                        }
                    }
                    if (composante != 3) {
                        return 6;
                    }
                    break;
                }
                if (!image.v_pixel(commande.couleur)) {
                    return 7;
                }
            } else if (decoupe[i] == "-angle" || decoupe[i] == "-a") {
                commande.argumentsPresents.push_back("angle");
                i++;
                if (chaineVersFlottant(decoupe[i], commande.angle)) {
                    return 8;
                }
            } else {
                cout << decoupe[i] << endl;
                return 2;
            }
        } else {
            return 1;
        }
    }

    // for (int i = 0; i < commande.argumentsPresents.size(); i++) { // DEBUG
    //     cout << "Argument présent " << i << " = " << commande.argumentsPresents[i] << endl;
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
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "x2")
                && argumentPresent(commande, "y1") && argumentPresent(commande, "y2")
                && argumentPresent(commande, "couleur")) {
            if (rectangle(image, image, commande.x1, commande.y1, commande.x2, commande.y2, commande.couleur)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "pivoter") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "y1")
                && argumentPresent(commande, "angle")) {
            if (pivoter(image, image, commande.x1, commande.y1, commande.angle)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "convBIN") {
        if (convBIN(image, image)) {
            return 3;
        }
    } else if (commande.fonction == "convNIV") {
        if (convNIV(image, image)) {
            return 3;
        }
        // } else if (commande.fonction == "convRVB") {
        // convRVB(image, image);
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
        case 3:
            messageErreur("Erreur dans l'execution de la commande");
            break;
        default:
            messageErreur("Impossible d'éxecuter la fonction");
        }
        break;
    case 1:
        messageErreur("Un argument a été attendu et autre chose a été donné");
        break;
    case 2:
        messageErreur("Argument inconnu");
        break;
    case 3:
        messageErreur("Un entier a été attendu et n'a pas été donné");
        break;
    case 4:
        messageErreur("La couleur d'une image binaire doit être blanc (1) ou noir (0)");
        break;
    case 5:
        messageErreur("La valeur d'une composante de couleur donnée est superieure au maximum de composante de l'image");
        break;
    case 6:
        messageErreur("La couleur d'une image RVB possède trois composantes");
        break;
    case 7:
        messageErreur("La couleur donnée n'est pas valide, la raison en est inconnue");
        break;
    case 8:
        messageErreur("Un nombre décimal a été attendu et n'a pas été donné (le programme n'accepte que les points)");
        break;
    default:
        messageErreur("Impossible d'analyser la commande");
        break;
    }
}

void boucleDeCommandes(Image image) { // REPL
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
