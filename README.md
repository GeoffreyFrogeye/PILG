#Projet d'ISN de Lucas et Geoffrey

##À propos...

###De ce dépôt
Ce dépôt a été crée pour faciliter le développement du projet. Son caractère public n'est que lié aux nécessité de GitHub. Si vous ne savez pas de quel projet il s'agit, vous perdez votre temps ici. L'absence de license (du moins jusqu'aux épreuves) vous interdit de distribuer ou de réutiliser le code, qui de toute façon ne vous aurait pas été utile. 

###De ce projet
Ceci est la création de Lucas et de Geoffrey pour l'option Informatique et Sciences du Numérique qui sera présenté lors du Baccalauréat 2013/2014.
Nos noms complets et le nom du lycée sont masqués pour des raisons d'intimité. Les personnes devant nous reconnaître nous reconnaîtront.

###Du programme
Ce programme est un éditeur basique d'images [PBM/PGM/PPM](http://fr.wikipedia.org/wiki/Portable_pixmap) s'éxecutant en ligne de commande.

*Status :* Prétotype

##Compilation
###Windows
1. Télecharger et installer [MinGW](http://www.mingw.org/)
2. Inclure **MinGW** dans la variable d'environnement ```%PATH%``` : ```set path=%path%;C:\MinGW\bin```
3. Créer le dossier *bin* à la racine du dépôt : ```mkdir bin```
4. Télécharger la [bibliothèque de développement SDL 1.2.15](http://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz), copier le contenu des dossier *lib* et *include* de l'archive téléchargée dans le dossier de **MinGW**
5. Télécharger la [bibliothèque d'execution de SDL 1.2.15](http://www.libsdl.org/release/SDL-1.2.15-win32.zip) et placer *SDL.dll* dans le dossier *bin*
6. Compiler : ```g++ src/main.cpp -o bin/main.exe -lmingw32 -lSDLmain -lSDL -static-libgcc -static-libstdc++```

L'executable se trouvera dans le dossier *bin*

----------
*Copyright 2014 Lucas et Geoffrey*
