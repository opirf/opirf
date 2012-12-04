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
Les imagettes acompagn�es des descipteurs se trouvent dans le dossier res/

----------------------------------------------------------------------------------------------------------------------
----------------------------------------- Description de la m�thode d'obtention --------------------------------------
----------------------------------------------------------------------------------------------------------------------

Pour chaque image:
La technique est modifier l'image que l'on analyse pour que les coordonn�es des icones et des imagettes correspondent
� celles de l'image que nous avons choisi pour r�f�rence.


/********** Etape num�ro 1 : Recherche des deux croix **********/
Pour comparer les 2 images, on cherche � localiser 2 croix pr�sentes aux m�mes endroits sur toutes les images
- Conversion de l'image en niveau de gris pour gagner du temps.
- On r�duit la zone d'inter�t (ROI) aux coin sup�rieur droit et inf�rieur gauche.
- on utilise la foncion match_template qui prend en param�tre un template de la croix � trouver.


/********** Etape num�ro 2 : Rotation & Redimensionnement **********/
Pour aligner l'image sur l'image de r�f�rence on applique des traitements.
- Grace aux coordonn�es des croix, on applique une rotation sur l'image (de base)
- On calcul l'�cart entre les 2 croix et on redimensionne pour que cet �cart soit 
le meme que celui de l'image de r�f�rence.


/********** Etape num�ro 3 : Identification de l'icone pour chaque ligne **********/
Pour chaque ligne, on connait la ROI � analyser.
- On applique la m�thode match_template avec la liste de tous les icones et on m�morise les deux meilleures 
confiances trouv�es
- Si la confiance maximale est inf�rieure � 0.5, on regarde la diff�rence entre les deux confiances maximales
- Si cette diff�rence est inf�rieure � 0.1, on consid�re que la confiance est trop faible et que l'icone n'a pas �t�
 trouv�e. On ignore alors la ligne enti�re.
- La m�me m�thode est appliqu�e pour d�terminer la taille de l'icone.


/********** Etape num�ro 4 : D�coupage et sauvegarde des imagettes **********/
Pour chaque ligne, on connait la position de chaque imagette.
- On d�coupe les images et on les sauvegarde dans des fichiers diff�rents.
- A chaque imagette est associ� un fichier texte descriptif.



----------------------------------------------------------------------------------------------------------------------
------------------------------------------------ Taux de bon �tiquetage ---------------------------------------------
----------------------------------------------------------------------------------------------------------------------

On obtient un taux de bon �tiquetage de 99,83%. En effet, 9 lignes n'ont pas �t� class�es car la confiance �tait trop
faible, dont 7 a cause d'une page mal cadr�e (croix sup�rieure manquante). Sans cette page, le taux de bon �tiquetage
est de 99.96%



----------------------------------------------------------------------------------------------------------------------
------------------------------------------------ Qualit� de l'extraction ---------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Les traitements de rotation et redimensionnement n'�tant pas parfait, on retrouve des d�calages sur la position des 
imagettes, se traduisant par la pr�sence de l�g�res bordures sur les cot�s des imagettes. (Dans de rares cas)



----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------- Cas d'�checs ---------------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Une des pages ayant une de ses croix coup�es n'a pas �t� trait�e.