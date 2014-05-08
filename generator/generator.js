#!/usr/bin/js

/*jslint node: true, forin: true, indent: 4 */

"use strict";

// Dépendances
var https = require('https'),
    fs = require('fs'),
    markdown = require('markdown').markdown;

// Variables
var liste = [];

// Fonctions
function recupererFichier(nomFichier, retour) {
    var contenu = '';
    console.log('Téléchargement de ' + nomFichier);
    https.get('https://raw.githubusercontent.com/GeoffreyFrogeye/PILG/master/' + nomFichier, function (res) {
        console.log('Réponse pour ' + nomFichier + ' obtenue (' + res.statusCode + ')');
        res.on('data', function (morceau) {
            contenu += morceau;
        }).on('end', function () {
            console.log('Fichier ' + nomFichier + ' téléchargé');
            retour(contenu);
        });
    }).on('error', function (e) {
        console.error('Impossible de récupérer le fichier ' + nomFichier + ' car ' + e.message);
    });
}

function genererPages(liste) {
    var nav = '',
        element;
    for (element in liste) {
        if (liste[element].titre === 'À propos') {
            liste[element].titreCourt = 'index';
        } else {
            liste[element].titreCourt = liste[element].titre
                .replace(/À/, 'A')
                .replace(/ /, '_')
                .replace(/\W/g, '');
        }
        if (!liste[element].lien) {
            liste[element].lien = liste[element].titreCourt + '.html';
        }
        nav += '<li><a href="' + liste[element].lien + '">' + liste[element].titre + '</a></li>\n';
    }
    fs.readFile('model.html', function (err, contenuModele) {
        if (!err) {
            liste.forEach(function (element) {
                var contenuHTML;
                if (element.contenu) {
                    contenuHTML = contenuModele
                        .toString('utf-8')
                        .replace(/%%TITRE%%/g, element.titre)
                        .replace(/%%NAV%%/, nav)
                        .replace(/%%CONTENU%%/, element.contenu)
                        .replace(/%%LICENSE%%/, 'Copyright 2014 Lucas et Geoffrey');
                    fs.writeFile('../' + element.titreCourt + '.html', contenuHTML, function (err) {
                        if (!err) {
                            console.log('Écrit ' + element.titreCourt + '.html');
                        } else {
                            console.error('Impossible d\'écrire' + element.titreCourt + '.html', err);
                        }
                    });

                }
            });
        } else {
            console.error('Impossible d\'ouvrir le fichier modèle');
        }
    });
}

// Execution
function executer() {
    recupererFichier('README.md', function (contenu) {
        var decoupe = contenu
            .toString('utf-8')
            .replace(/##Compilation\n/, '%%SPLIT%%')
            .replace(/Nos noms complets et le nom du lycée sont masqués pour des raisons d'intimité\. Les personnes devant nous reconnaître nous reconnaîtront\./g, '')
            .replace(/##Le dépôt[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\'\,\(\)\n]+?##/g, '#')
            .replace(/#(#+)/g, '$1')
            .replace(/^#[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\n/g, '')
            .replace(/\n#[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\n/g, '')
            .replace(/-+\n\*Copyright[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\*/g, '')
            .split('%%SPLIT%%');
        liste.push({
            titre: 'À propos',
            contenu: markdown.toHTML(decoupe[0]) + '\n<img src="screen.png" alt="Capture d\'écran du code" />'
        }, {
            titre: 'Compilation',
            contenu: markdown.toHTML(decoupe[1])
        });
        recupererFichier('TODO.md', function (contenu) {
            liste.push({
                titre: "Avancement",
                contenu: markdown.toHTML(contenu
                    .toString('utf-8')
                    .replace(/^#[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\n/g, '')
                    .replace(/\n#[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\n/g, '')
                    .replace(/-+\n\*Copyright[ \wæâ€êÿûîœôäßëðüïö©éÉèÈçÇàÀ\.\-\']+\*/g, ''))
                    .replace(/<strong>([DAC])<\/strong>/g, '<span class="todoEl todo_$1">$1</span>') + '\n<img src="chart.png" alt="Fonctionnement du programme" />'
            }, {
                titre: 'Code source',
                lien: 'https://github.com/GeoffreyFrogeye/PILG'
            });
            genererPages(liste);
        });
    });
}

executer();
