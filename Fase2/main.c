#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Logica.h"
#include "LlistaPDI.h"
#include "Cua.h"

int main(int argc, char *argv[]){
	int opcio = 0, puntuacio = 0;
	int sortir = 0, fet = 0, error = 0, index = 0, blanc = 0, emot1 = 0, emot2 = 0;
	char nom_pilot[MAX], nom_escuderia[MAX], nom_cursa[MAX], nom_circuit[MAX];
	float distancia = 0;	
	char fi[3];
	int indexfi = 0;
	int compt = 0, c_aux= 0;
	FILE *f;
	FILE *f_c;
	LlistaPDI_P lp;
	LlistaPDI_C lc;
	Cua c;
	fi[indexfi] = 'F';
	fi[indexfi + 1] = 'I';
	fi[indexfi + 2] = '\0';

	//comprovem que els arguments que li passem siguin 3
	if (argc != 3){
		printf ("Error. Nombre de parametres incorrecte!");
		return 0;
	}
	
	//extreiem els circuits emmagatzemats al fitxer
	lc = extreuCircuits(lc, f_c, &sortir);
	//extreu els pilots del fitxer de text i els emmagatzema a la llista
	lp = extreuInfo(lp, f, &sortir);
	// crea una cua
	//c = CUA_crea();
			
	//realtzem un bucle infinit que printa el menu fins que no es premi la opcio "9"
	while(sortir == 0){
		do{
			printf("\n\n ----- Menu Principal ----- \n\n ");
			printf ("1) Crear Pilot \n");
			printf (" 2) Eliminar Pilot \n");
			printf (" 3) Crear Circuit \n");
			printf (" 4) Eliminar Circuit \n");
			printf (" 5) Mostrar Pilots \n");
			printf (" 6) Mostrar Estadistiques \n");
			printf (" 7) FerCursa \n");
			printf (" 8) FerCampionat \n");
			printf (" 9) Sortir \n\n ");
			//netejem la pantalla
			fflushnou();
			// demanem l'opcio a l'usuari
			printf (" Opcio?: \n");
			scanf("%d", &opcio);
		
			// comprovem que la opcio seleccionada estigui dins dels parametres permesos
			if((opcio < 1) || (opcio > 9)){
				printf("Error. La opcio escollida no es valida!\n");
			}
			/*
			while ((compt<10)&& (!error)){
				c_aux = compt + '0';
				if ((opcio - c_aux) != 0){
					printf ("\n Error. Aquesta opcio no es valida!\n");
					error = 1;
				}
			}*/
			
		}while((opcio < 1) || (opcio > 9));	
			switch (opcio){
				
				//demanem a l'usuari l'informacio per crear un nou pilot
				case 1:
						printf (" ----- Creacio del pilot ----- \n\n");
						printf ("Nom :\n ");
						fflushnou();
						gets (nom_pilot);
						index = 0;
						//aquesta variable ens permetra comprovar que el nom es correcte
						blanc = 1;
						emot1 = 0;
						emot2 = 0;
						//comprovem que el nom entrat no estigui unicament compost per espais en blanc 
						while (nom_pilot[index] != '\0'){
							if (nom_pilot[index] != ' '){
								blanc = 0;
							}
							index ++;
						}
						// en cas de que es doni la situacio en blanc donara error
						if (blanc != 0){
							emot1 = 1;
						}else{
							//comprovem que el nom no estigui buit
							if (nom_pilot[0] == '\0'){
								emot1 = 1;
							}
						}
						
						//en cas de que no hi hagui error es demanara l'escuderia
						if (emot1 == 0){
							printf ("Escuderia:\n ");
							fflushnou();
							gets (nom_escuderia);
							index = 0;
							blanc = 1;
							//comprovem que el nom de l'escuderia no estigui compost nomes per espais en blanc
							while (nom_escuderia[index] != '\0'){
								if (nom_escuderia[index] != ' '){
									blanc = 0;
								}
								index ++;
							}//tanquem el while 
						
							//en cas de que estigui en blanc donara error
							if (blanc != 0){
								emot2 = 1;
							}else{
								//comprovem que el nom no estigui buit
								if (nom_escuderia[0] == '\0'){
									emot2 = 1;
								}
							}
							//si no s'ha donat error de cap tipus s'emmagatzermara la informacio
							if (emot2 == 0){
								lp = afegeixJugador(lp, nom_pilot, nom_escuderia);
							}else{
								//si hi ha hagut errors donara un missatge d'avis
								printf("Error! El nom de la escuderia no es valid \n");
							}
						}else{
							//si hi ha hagut error amb el nom del pilot donara un missatge d'avis
							printf("Error! El nom del pilot no es valid \n");
						}
						//netejem la pantalla
						fflushnou();
						break;
				//Demanem la infromacio a l'usuari per eliminar un pilot
				case 2: 

					printf (" ----- Eliminar pilot ----- \n\n");
					printf ("Nom:\n ");
					fflushnou();
					gets (nom_pilot);
					//truquem a la funcio encarregada d'eliminar-lo
					lp = esborraPilot(lp, nom_pilot);
					break;
				
				//demanem la informacio per crear un circuit
				case 3: 
					printf (" ----- Creacio del circuit ----- \n\n");
					printf ("Nom: ");
					fflushnou();
					gets (nom_cursa);
					emot1 = 0;
					blanc = 1;
					index = 0;
					//comprovem que el nom inserit no estigui compost unicament per espais en blanc
					while (nom_cursa[index] != '\0'){
						if (nom_cursa[index] != ' '){
							blanc = 0;
						} 
						index ++;
					}
					//si es dona la situacio en blanc s'activara 'error
					if (blanc != 0){
						emot1 = 1;
					}else{
						//comprovem que el nom no estigui buit
						if (nom_cursa[0] == '\0'){
							emot1 = 1;
						}
					}
					//en cas de que no hi hagi error es demanan la resta de dades
					if (emot1 == 0){
						//demanem els kilometres disponibles del circuit
						printf ("\nKilometres: ");
						fflushnou();
						scanf("%f", &distancia);
						//demanem la maxima puntuacio que es pot obtenir al circuit
						printf ("\nPuntuacio Maxima: ");
						fflushnou();
						scanf ("%d", &puntuacio);
						//emmagatzemem el circuit a la llista
						lc = afegeixCircuit(lc, nom_cursa, distancia, puntuacio);
						printf("Nom del Circuit =  %s\n", lc.ant -> c.nomCircuit);
					}else{
						//en cas de que s'hagi detectat un error mostara un missatge d'advertencia
						printf("Error! El nom del circuit no es valid");
					}
					break;
			case 4:
					//Demanem les dades del circuit a eliminar
					printf (" ----- Eliminar circuit ----- \n\n");
					printf ("Nom: ");
					fflushnou();
					gets (nom_circuit);
					//cridem a la funcio encarregada d'esborrar el circuit
					lc = esborraCircuit(lc, nom_circuit);

					break;
			case 5: 
					fflushnou();
					//mostrem els pilots que es troben a la llista sempre i quan aquesta no estigui buida
					if(!LLISTAPDI_P_buida(lp)){
					   mostraPilots(lp);
					}else{
						//en cas de que estigui buida donara missatge d'error
						printf("No hi han pilots a mostrar\n");
					}
			
					break;
			case 6:
					printf(" ----- Estadistiques -----\n\n");
					//comprovem que s'ha realitzat com a minim una cursa
					if(fet == 1){
						printaEstadistiques(lp, lc);
					}else{
						printf("No has fet cap cursa, ni cap campionat\n");
					}
					break;
			case 7: 
					printf(" ----- Cursa ----- \n\n");
					
					//ubiquem el PDI al inici de la llista
					lp = LLISTAPDI_P_vesInici(lp);
					
					//comprovem que hi hagi pilots a la llista
					if(LLISTAPDI_P_buida(lp)){
						
						printf("No hi han pilots\n");
						error = 1;
					
					}else{
						
						//pintem per pantalla els circuits enregistrats fins el moment
						printf("\n Circuits disponibles:\n");
						circuitsDisponibles(lc, &error);
						fflushnou();
					}
					//si hi ha pilots demanem a l'usuari el circuit en el que es vol realitzar la cursa
					if(error == 0){
						printf("\n Quin circuit vols: ");
						fflushnou();
						gets (nom_circuit);
						printf(" %s\n", nom_circuit);
						//realitzem la cursa en funcio del cricuit escollit
						lp = circuitEscollit(lc, nom_circuit, lp);
						fet = 1;
					}
					break;
			case 8: 
					printf (" ----- Campionat ----- \n\n");
					//pintem per pantalla els circuits enregistrats fins el moment
					printf("\n Circuits disponibles:\n");
					circuitsDisponibles(lc, &error);
					fflushnou();
					//si hi ha circuits es realitza el campionat
					c = CUA_crea();

					if(error == 0){

						printf("Quin circuit vols: \n");
						gets (nom_circuit);
						//comprovem que el circuit demanat per l'usuari existeix
						while(strcmp(nom_circuit,fi) != 0){
							c = circuitAuxiliar(nom_circuit, c, lc);
							printf("Quin circuit vols: \n");
							gets (nom_circuit);
						
						}
						lp = ferCampionat(c, lp);
						fet = 1;
					}

					break;
			
			case 9:
		
					printf ("\n Actualitzat fitxer de Jugadors ...\n");
					printf ("\n Actualitzat fitxer de Circuits ...\n");
					
					printf ("\n Gracies per utilitzar RallyLSMaker, GAS! \n\n");
					//guardem els pilots de la llista al fitxer de text
					lp = insereixPilot(lp, f);
					//guardem els circuits de la llista al fitxer de text
					lc = insereixCircuit(lc, f_c);
					//forcem la sortida del bucle
					sortir = 1;
					break;
					
		}//tanquem el switch
	
	}//tanquem el while
	return 0;
}
