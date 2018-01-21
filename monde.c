#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "header.h"
#include <time.h>

void initialiserMonde(Monde *monde) {
	monde->tour = 0;
	monde->rouge = NULL;
	monde->bleu = NULL;

	/* Parcours du plateau de jeu */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			monde->plateau[i][j] = NULL;
		}
	}
}

/* Retourne un nombre aleatoire */
// On suppose a<b
int rand_a_b(int a, int b){
return rand()%(b-a) +a;
}


int afficheMonde(Monde monde) {

	MLV_Image *serf, *guerrier;

	int i, j;
	
	for (i = 0; i < LONG; i++){

		for (j = 0; j < LARG; j++) {


	/* Essai de creer des cases pieges mais pour l'instant c'est un fiasco */
	/*
	int p = 0;
	int nombre_aleatoire1 = 0;
	int nombre_aleatoire2 = 0;

		if(p<2){

		nombre_aleatoire1 = rand_a_b(0,LONG);
		nombre_aleatoire2 = rand_a_b(0,LARG);

		MLV_draw_filled_rectangle(nombre_aleatoire1*CASE, nombre_aleatoire2*CASE, CASE, CASE, MLV_COLOR_ORANGE_RED);
		
			if ((i + j) % 2 == 0 && j!=nombre_aleatoire1 && i!=nombre_aleatoire2){
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(200,200,200,255));
			} else {
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(90,90,90,255));
			}

		p++;
		}
		*/
	

			/* Création du damier */
			if ((i + j) % 2 == 0){
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(200,200,200,255));
			} else {
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(90,90,90,255));
			}
			
			if (monde.plateau[i][j] != NULL){

				/* Test du propriétaire & chargement des images */
				if (monde.plateau[i][j]->couleur == ROUGE){
					serf = MLV_load_image( "image/serf-r.png" );
					guerrier = MLV_load_image( "image/guerrier-r.png" );					
				} else {
					serf = MLV_load_image( "image/serf-b.png" );
					guerrier = MLV_load_image( "image/guerrier-b.png" );
				}

				/* Redimensionne les images */
				MLV_resize_image_with_proportions(serf, CASE, CASE);
				MLV_resize_image_with_proportions(guerrier, CASE, CASE);	

				/* Test du type d'unité */
				if (monde.plateau[i][j]->type == SERF){
					MLV_draw_image(serf, j*CASE, i*CASE);
				} else {
					MLV_draw_image(guerrier, j*CASE, i*CASE);
				}
			}

		}

	}

	// Met a jour l'affichage
	MLV_actualise_window();


}

void viderMonde(Monde *monde) {

	int i, j;

	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			if (monde->plateau[i][j] != NULL) {

				/* Supprime toutes les unités restantes sur le plateau */
				enleverUnite(monde->plateau[i][j], monde);
				monde->plateau[i][j] = NULL;
			}
		}
	}

	monde->tour = 0;
	monde->rouge = NULL;
	monde->bleu = NULL;

}