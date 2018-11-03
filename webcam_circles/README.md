# webcam_circleis
Circle detection from online webcam images

Primer: Transforma la imatge de color a escala de gris. Per tal de eliminar errors del soroll.

Segon: Elimina el soroll per evitar deteccions erronies.

Tercer: Es fa servir al transformada de Hough Circle. Els argument són:
	src_gray = gray_image : Matriu imput.
	circles = circles : Vector de 3 valors (x,y,z).
	CV_HOUGH_GRADIENT : Defineix el mètode de detecció.
	dp = HOUGH_ACCUM_RESOLUTION : La resolució inercia de la resolució.
	min_dist = MIN_CIRCLE_DIST : La distància mínima entre els centres de les circunferències.
	param_1 = CANNY_EDGE_TH : Llindar superior per les cantonades Canny.
	param_2 = HOUGH_ACCUM_TH : Llindar per la detecció del centre.
	min_radius = MIN_RADIUS : Mínim radi que detecta.
	max_radius = MAX_RADIUS : Màxim radi que detecta.
