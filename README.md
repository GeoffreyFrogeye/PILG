#Projet d'ISN de Lucas et Geoffrey

##À propos

###Le dépôt
Ce dépôt a été crée pour faciliter le développement du projet. Son caractère public n'est que lié aux nécessité de GitHub. Si vous ne savez pas de quel projet il s'agit, vous perdez votre temps ici. L'absence de licence (du moins jusqu'aux épreuves) vous interdit de distribuer ou de réutiliser le code, qui de toute façon ne vous aurait pas été utile. 

###Le projet
Ceci est la création de Lucas et de Geoffrey pour l'option Informatique et Sciences du Numérique qui sera présenté lors du Baccalauréat 2013/2014.
Nos noms complets et le nom du lycée sont masqués pour des raisons d'intimité. Les personnes devant nous reconnaître nous reconnaîtront.

###Le programme
Ce programme est un éditeur basique d'images [PBM/PGM/PPM](http://fr.wikipedia.org/wiki/Portable_pixmap) s’exécutant en ligne de commande.

*Version :* v1.0.1

*Status :* [![Build Status](https://travis-ci.org/GeoffreyFrogeye/PILG.svg?branch=master)](https://travis-ci.org/GeoffreyFrogeye/PILG)

##Compilation
Il n'existe pas de fichier binaire à télécharger pour le moment, le seul moyen d'avoir un aperçu du programme est de le compiler.

Téléchargement : ```git clone https://github.com/GeoffreyFrogeye/PILG.git```

###Windows
1. Télécharger et installer [MinGW](http://www.mingw.org/)
2. Inclure **MinGW** dans la variable d'environnement ```%PATH%``` : ```set path=%path%;C:\MinGW\bin```
3. Télécharger la [bibliothèque de développement SDL 1.2.15](http://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz), copier le contenu des dossier *lib* et *include* de l'archive téléchargée dans le dossier de **MinGW**
4. Télécharger la [bibliothèque d’exécution de SDL 1.2.15](http://www.libsdl.org/release/SDL-1.2.15-win32.zip) et placer *SDL.dll* dans le dossier *bin*
5. Compiler : ```mingw32-make -f Makefile.win```

L’exécutable se trouvera dans le dossier *bin*

###Debian / Linux
1. Installer le nécessaire à la compilation ainsi que la **bibliothèque de développement SDL 1.2** : ```sudo apt-get install build-essential libsdl1.2-dev```
2. Compiler : ```make```

L’exécutable se trouvera dans le dossier *bin*


----------
*Copyright 2014 Lucas et Geoffrey*
