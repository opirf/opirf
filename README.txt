Projet OPIRF - Percot-Tetu Sach', Averty Ben', Garry Flow', Colleoni Polo


                    // //  //
         __    ____||_//  //
       _/__--~~        ~~~-_
      /  /___        ___    \
     /  /(  +)      ( + )    |
    /  |  ~~~    __  ~~~   _/\/|
   |    \  ___.-~  ~-.___  \   / 
    \    \(     ` '      ~~)|   \
     \     )              / |    \
      \/   /              \ |    |
      /   |               | |    |
     |    /               |  \__/
     |    \_            _/      |    ___
     \      ~----...---~       /_.-~~ _/
      \_                      |    _-~ 
        \                    /  _-~ 
         ~-.__             _/--~
        _.-~  ~~~-----~~~~~
       ~-.-. _-~     /_ ._ \   
            ~       ~  ~  ~-

Temps de traitement de la base (35 writer, 22 pages/writer, 7 rows/page, 5 boxes/row - so 26950 boxes) : 13'19''


----------------------------------------------------------------------------------------------------------------------
----------------------------------------------- Emplacement des fichiers ---------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Les source se trouvent dans le dossier opirf/
Les imagettes acompagnées des descipteurs se trouvent dans le dossier res/

----------------------------------------------------------------------------------------------------------------------
----------------------------------------- Description de la méthode d'obtention --------------------------------------
----------------------------------------------------------------------------------------------------------------------

Pour chaque image:
La technique est modifier l'image que l'on analyse pour que les coordonnées des icones et des imagettes correspondent
à celles de l'image que nous avons choisi pour référence.


/********** Etape numéro 1 : Recherche des deux croix **********/
Pour comparer les 2 images, on cherche à localiser 2 croix présentes aux mêmes endroits sur toutes les images
- Conversion de l'image en niveau de gris pour gagner du temps.
- On réduit la zone d'interêt (ROI) aux coin supérieur droit et inférieur gauche.
- on utilise la foncion match_template qui prend en paramètre un template de la croix à trouver.


/********** Etape numéro 2 : Rotation & Redimensionnement **********/
Pour aligner l'image sur l'image de référence on applique des traitements.
- Grace aux coordonnées des croix, on applique une rotation sur l'image (de base)
- On calcul l'écart entre les 2 croix et on redimensionne pour que cet écart soit 
le meme que celui de l'image de référence.


/********** Etape numéro 3 : Identification de l'icone pour chaque ligne **********/
Pour chaque ligne, on connait la ROI à analyser.
- On applique la méthode match_template avec la liste de tous les icones et on mémorise les deux meilleures 
confiances trouvées
- Si la confiance maximale est inférieure à 0.5, on regarde la différence entre les deux confiances maximales
- Si cette différence est inférieure à 0.1, on considère que la confiance est trop faible et que l'icone n'a pas été
 trouvée. On ignore alors la ligne entière.
- La même méthode est appliquée pour déterminer la taille de l'icone.


/********** Etape numéro 4 : Découpage et sauvegarde des imagettes **********/
Pour chaque ligne, on connait la position de chaque imagette.
- On découpe les images et on les sauvegarde dans des fichiers différents.
- A chaque imagette est associé un fichier texte descriptif.



----------------------------------------------------------------------------------------------------------------------
------------------------------------------------ Taux de bon étiquetage ---------------------------------------------
----------------------------------------------------------------------------------------------------------------------

On obtient un taux de bon étiquetage de 99,83%. En effet, 9 lignes n'ont pas été classées car la confiance était trop
faible, dont 7 a cause d'une page mal cadrée (croix supérieure manquante). Sans cette page, le taux de bon étiquetage
est de 99.96%



----------------------------------------------------------------------------------------------------------------------
------------------------------------------------ Qualité de l'extraction ---------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Les traitements de rotation et redimensionnement n'étant pas parfait, on retrouve des décalages sur la position des 
imagettes, se traduisant par la présence de légères bordures sur les cotés des imagettes. (Dans de rares cas)



----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------- Cas d'échecs ---------------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Une des pages ayant une de ses croix coupées n'a pas été traitée.