opirf
=====
The aim of this project was to be able to recognize 14 different image icons, from the NicIcon Database : 
http://unipen.nici.ru.nl/NicIcon/index.php
We reached a 97% recognition rate on a set of 200 test images.

The project is separated in 2 main part:
- FormSegmentation : which handles the images from the database : normalise image (size, orientation), segmentation
(cropped every icon)
- FeatureExtraction : extract the wanted features from the segmentated images and generate an ARFF file that
can be use with WEIKA to try machine learning algorithm and tests the features.
