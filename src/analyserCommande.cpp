#include <vector>
#include <string>
#include <iostream>

void decoupeCommande(string commande, vector< string > &decoupe) {
    // Boucle de découpage
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
        
        if (commande[i] == ' ' && !(echape || entreSimplesGuillemets ||
                                    entreDoublesGuillemets)) {
            if (!dansLeVide) {
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            }
        } else if (commande[i] == '\\' && !echape) {
            vaEchapper = true;
        } else if (commande[i] == '\'' && !(echape || entreDoublesGuillemets)) {
            if (entreSimplesGuillemets) {
                entreSimplesGuillemets = false;
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            } else {
                entreSimplesGuillemets = true;
            }
        } else if (commande[i] == '"' && !(echape || entreSimplesGuillemets)) {
            if (entreDoublesGuillemets) {
                entreDoublesGuillemets = false;
                decoupe.push_back(elementCourrant);
                elementCourrant = "";
                dansLeVide = true;
            } else {
                entreDoublesGuillemets = true;
            }
        } else {
            elementCourrant += commande[i];
            dansLeVide = false;
        }
    }
    
    if (!dansLeVide) {
        decoupe.push_back(elementCourrant);
    }
}

typedef struct Commande {
    string fonction;
    
    int x1, x2, y1, y2;
    float v1;
    bool b1;
    string t1;
    string fichier, entree, sortie;
    Pixel couleur;
    PILG_Comp composante;
    
    vector< string > argumentsPresents;
} Commande;

int analyserDecoupe(Commande &commande, vector< string > decoupe,
                    Image const &image) {
    // for (int i = 0; i < decoupe.size(); i++) { // DEBUG
    //     cout << "Argument " << i << " = " << decoupe[i] << endl;
    // }
    commande.couleur = image.g_pixelVide();
    commande.fonction = decoupe[0];
    
    // // Analyse des arguments
    for (int i = 1; i < decoupe.size(); i++) {
        if (decoupe[i].at(0) == '-') {
            /*  */ if (decoupe[i] == "-x1" || decoupe[i] == "-x0" || decoupe[i] == "-x") {
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
            } else if (decoupe[i] == "-x2" || decoupe[i] == "-X") {
                commande.argumentsPresents.push_back("x2");
                i++;
                
                if (chaineVersEntier(decoupe[i], commande.x2)) {
                    return 3;
                }
            } else if (decoupe[i] == "-y2" || decoupe[i] == "-Y") {
                commande.argumentsPresents.push_back("y2");
                i++;
                
                if (chaineVersEntier(decoupe[i], commande.y2)) {
                    return 3;
                }
            } else if (decoupe[i] == "-v1" || decoupe[i] == "-v" || decoupe[i] == "-a"
                       || decoupe[i] == "-r") {
                commande.argumentsPresents.push_back("v1");
                i++;
                
                if (chaineVersFlottant(decoupe[i], commande.v1)) {
                    return 3;
                }
            } else if (decoupe[i] == "-b1" || decoupe[i] == "-b") {
                commande.argumentsPresents.push_back("b1");
                i++;
                
                if (decoupe[i] == "1" || decoupe[i] == "vrai" || decoupe[i] == "oui") {
                    commande.b1 = true;
                } else if (decoupe[i] == "0" || decoupe[i] == "faux" || decoupe[i] == "non") {
                    commande.b1 = false;
                } else {
                    return 8;
                }
            } else if (decoupe[i] == "-t1" || decoupe[i] == "-t") {
                commande.argumentsPresents.push_back("t1");
                i++;
                commande.t1 = decoupe[i];
            } else if (decoupe[i] == "-f1" || decoupe[i] == "-f") {
                commande.argumentsPresents.push_back("fichier");
                i++;
                commande.fichier = decoupe[i];
            } else if (decoupe[i] == "-e") {
                commande.argumentsPresents.push_back("entree");
                i++;
                commande.entree = decoupe[i];
            } else if (decoupe[i] == "-s") {
                commande.argumentsPresents.push_back("sortie");
                i++;
                commande.sortie = decoupe[i];
            } else if (decoupe[i] == "-p") {
                commande.argumentsPresents.push_back("composante");
                i++;
                
                /*  */ if (decoupe[i] == "0" || decoupe[i] == "BIN") {
                    commande.composante = PILG_BIN;
                } else if (decoupe[i] == "1" || decoupe[i] == "NIV") {
                    commande.composante = PILG_NIV;
                } else if (decoupe[i] == "2" || decoupe[i] == "RVB") {
                    commande.composante = PILG_RVB;
                } else {
                    return 10;
                }
            } else if (decoupe[i] == "-c") {
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
            } else {
                cout << decoupe[i] << endl;
                return 2;
            }
        } else {
            return 1;
        }
    }
    
    journal << endl;
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
    if (argumentPresent(commande, "entree")) {
        if (ouvrir(image, commande.entree)) {
            return 4;
        }
    }
    
    /*  */ if (commande.fonction == "creer") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "y1")
                && argumentPresent(commande, "v1") && argumentPresent(commande, "composante")) {
            if (creer(image, commande.x1, commande.y1, commande.v1, commande.composante)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "ouvrir") {
        if (argumentPresent(commande, "fichier")) {
            if (ouvrir(image, commande.fichier)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "sauver") {
        if (argumentPresent(commande, "fichier")) {
            if (!argumentPresent(commande, "b1")) {
                commande.b1 = false;
            }
            
            if (!argumentPresent(commande, "t1")) {
                commande.t1 = "Fichier généré par PILG";
            }
            
            if (sauver(image, commande.fichier, commande.b1, commande.t1)) {
                return 3;
            }
        } else {
            return 2;
        }
        
        // } else if (commande.fonction == "importer") {
        //     if (argumentPresent(commande, "fichier")) {
        //         if (!argumentPresent(commande, "x1")) {
        //             commande.x1 = 0;
        //         }
        //         if (!argumentPresent(commande, "y1")) {
        //             commande.y1 = 0;
        //         }
        //         if (importer(image, image, commande.fichier,)) {
        //             return 3;
        //         }
        //     } else {
        //         return 2;
        //     }
    } else if (commande.fonction == "teinte") {
        if (image.g_typeComposantes() == PILG_RVB) {
            if (argumentPresent(commande, "v1")) {
                if (teinte(image, image, commande.v1)) {
                    return 3;
                }
            } else {
                return 2;
            }
        } else {
            return 11;
        }
    } else if (commande.fonction == "saturation") {
        if (image.g_typeComposantes() == PILG_RVB) {
            if (argumentPresent(commande, "v1")) {
                if (saturation(image, image, commande.v1)) {
                    return 3;
                }
            } else {
                return 2;
            }
        } else {
            return 11;
        }
    } else if (commande.fonction == "luminosite") {
        if (image.g_typeComposantes() == PILG_RVB) {
            if (argumentPresent(commande, "v1")) {
                if (luminosite(image, image, commande.v1)) {
                    return 3;
                }
            } else {
                return 2;
            }
        } else {
            return 11;
        }
        
        // } else if (commande.fonction == "contraste") {
        //     if (argumentPresent(commande, "v1")) {
        //         if (contraste(image, image, commande.v1)) {
        //             return 3;
        //         }
        //     } else {
        //         return 2;
        //     }
    } else if (commande.fonction == "trait") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "x2")
                && argumentPresent(commande, "y1") && argumentPresent(commande, "y2")
                && argumentPresent(commande, "couleur")) {
            if (trait(image, image, commande.x1, commande.y1, commande.x2, commande.y2,
                      commande.couleur)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "rectangle") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "x2")
                && argumentPresent(commande, "y1") && argumentPresent(commande, "y2")
                && argumentPresent(commande, "couleur")) {
            if (rectangle(image, image, commande.x1, commande.y1, commande.x2, commande.y2,
                          commande.couleur)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "cercle") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "y1")
                && argumentPresent(commande, "v1") && argumentPresent(commande, "couleur")) {
            if (cercle(image, image, commande.x1, commande.y1, commande.v1,
                       commande.couleur)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "disque") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "y1")
                && argumentPresent(commande, "v1") && argumentPresent(commande, "couleur")) {
            if (disque(image, image, commande.x1, commande.y1, commande.v1,
                       commande.couleur)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "pivoter") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "y1")
                && argumentPresent(commande, "v1")) {
            if (pivoter(image, image, commande.x1, commande.y1, commande.v1)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "retourner") {
        if (argumentPresent(commande, "v1")) {
            if (retourner(image, image, commande.v1)) {
                return 3;
            }
        } else {
            return 2;
        }
    } else if (commande.fonction == "redimensionner") {
        if (argumentPresent(commande, "x1") && argumentPresent(commande, "x2")
                && argumentPresent(commande, "y1") && argumentPresent(commande, "y2")) {
            if (redimensionner(image, image, commande.x1, commande.y1, commande.x2,
                               commande.y2)) {
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
    } else if (commande.fonction == "convRVB") {
        if (convRVB(image, image)) {
            return 3;
        }
    } else {
        return 1;
    }
    
    if (argumentPresent(commande, "sortie")) {
        if (sauver(image, commande.sortie, false, "Fichier généré par PILG")) {
            return 4;
        }
    }
    
    return 0;
}

int procederCommande(vector< string > decoupe, Image &image) {
    journal << "Commande : ";
    
    for (int i = 0; i < decoupe.size(); i++) {
        journal << "«" << decoupe[i] << "» ";
    }
    
    Commande commande;
    int code;
    code = analyserDecoupe(commande, decoupe, image);
    
    switch (code) {
    case 0:
        code = executerCommande(commande, image);
        
        switch (code) {
        case 0:
            journal << "Succès" << endl;
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
            
        case 4:
            messageErreur("Impossible d'ouvrir l'entrée");
            
        default:
            messageErreur("Impossible d'éxecuter la fonction");
            break;
        }
        
        return code;
        
    case 1:
        messageErreur("Un argument a été attendu et autre chose a été donné");
        break;
        
    case 2:
        messageErreur("Argument inconnu");
        break;
        
    case 3:
        messageErreur("Un nombre a été attendu et n'a pas été donné");
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
        messageErreur("Un booléen (vrai/faux) a été attendu mais n'a pas été donné");
        break;
        
    case 9:
        messageErreur("Une chaine de caractères a été attendue mais n'a pas été donnée");
        break;
        
    case 10:
        messageErreur("La composante donnée n'est pas valide");
        break;
        
    case 11:
        messageErreur("Il est nécessaire d'avoir une image en mode RVB pour executer cette commande");
        break;
        
    default:
        messageErreur("Impossible d'analyser la commande");
        break;
    }
    
    return code;
}

void boucleDeCommandes(Image image) { // REPL
    bool continuer = true;
    string commandeTexte;
    
    while (continuer) {
        cout << "$ ";
        getline(cin, commandeTexte);
        
        if (commandeTexte == "quitter") {
            continuer = false;
        } else {
            vector< string > decoupe;
            decoupeCommande(commandeTexte, decoupe);
            procederCommande(decoupe, image);
            afficherImage(image);
        }
    }
}
