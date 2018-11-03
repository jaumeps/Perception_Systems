# webcam_point_features
Detection of ORB features from online webcam imges.

Dins del Find ORB point, el primer pas es posar a cero el point_set. EL següent pas és carrega el orb_detector es fa amb la funció detectAndCompute. En aquesta funció el primer parametre és la imatge original, el segon és la mascara, el tercer el vector de punts (point_set) i el quart és output arrey. Després el que es fa es dibuixar/col·locar els punts detectats a la imatge original.

ORB detecta els punts situats als extrem i els col·loca en una matriu (rotació).
