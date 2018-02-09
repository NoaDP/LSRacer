#include "Logica.h"

LlistaPDI_P extreuInfo (LlistaPDI_P lp, FILE *f, int *sortir){
	char aux[MAX], auxnomp[MAX], auxnomesc[MAX], auxpunts[MAX], auxkm[MAX];
	int index = 0, indexn = 0, indexesc = 0, punts = 0, indexpunts = 0, indexkm = 0, compt = 0,  mal = 0;
	float km;
	Pilots p;
	Pilots p_aux;
	//creem la llista que contindra els pilots
	lp = LLISTAPDI_P_crea();	
	// obrim el fitxer de text en mode lectura
	f = fopen("Pilots.txt", "r");
	
	fgets(aux,100,f);

	//llegim tots els elements el fitxer
	while(!feof(f) && mal == 0){
		
		// primer treiem el \n del final de la fila i anem copiant les dades en un aux i despres en el tipus pilot
		index = 0;		
		indexn = 0;
		indexesc = 0;
		indexpunts = 0;
		indexkm = 0;
		compt++;
		//llegim el nom del pilot
		while (aux[index] != '/' && mal == 0){
			//comprovem que estigui compost per caracters valids
			if((aux[index] >= 'A' && aux[index] <= 'Z') || (aux[index] >= 'a' && aux[index] <= 'z') || (aux[index] >= '0' && aux[index] <= '9') || aux[index] == ' '){
				//copiem el nom en una variable
				auxnomp[indexn] = aux[index];
				indexn++;
				index++;
			}else{
				//en cas de que el nom sigui erroni mostra un missatge d'avís
				mal = 1;
				printf("Revisa el nom dels pilot numero %d, conte un caracter invalid\n", compt);
			}//else
		}//while

		//en cas de que sigui correcte es guarda el nom del pilot a la variable tipus pilot
		if(mal == 0){
			
			auxnomp[indexn] = 0;
			strcpy (p.nomPilot, auxnomp);
			index++;//saltem el '/'
		}//if
		
		//llegim el nom de l'escuderia 
		while (aux[index] != '/' && mal == 0){
			
			//comprovem que el nom contingui caracters permesos
			if((aux[index] >= 'A' && aux[index] <= 'Z') || (aux[index] >= 'a' && aux[index] <= 'z') || (aux[index] >= '0' && aux[index] <= '9') || aux[index] == ' '){
				//copiem el nom a una variable auxiliar
				auxnomesc[indexesc] = aux[index];
				indexesc++;
				index++;
			}else{
				//en cas de que estigui malament mostra un missatge d'error
				mal = 1;
				printf("Revisa l'escuderia de %s, hi ha un caracter invalid\n", auxnomp);
			}//else
		}//while
		
		//en cas de que estigui be emmagatze el nom de l'escuderia a la variable tipus pilot
		if(mal == 0){
		
			auxnomesc[indexesc] = 0;
			strcpy(p.nomEscuderia, auxnomesc);
			index++;
		}
		
		//llegim els punts del pilot
		while(aux[index] != '/' && mal == 0){
			
			//comprovem si la puntuacio esta composta unicament per numeros
			if(aux[index] >= '0' && aux[index] <= '9'){
				// copiem la puntuacio a la variable tipus pilot
				auxpunts[indexpunts] = aux[index];
				indexpunts++;
				index++;
			}else{
				
				// en cas de que estigui malament mostrara un missatge d'error
				mal = 1;
				printf("Hi ha hagut algun error amb la puntuacio de %s\n", auxnomp);
			}//if
		}//while 
		
		// en cas de que estigui be s'emmagatzemen els punts a la variable tipus pilot
		if(mal == 0){
			auxpunts[indexpunts] = 0;
			index++;
			// converim els caracters en un nombre enter 
			punts = atoi(auxpunts);
			p.punts = punts;
		}//if 
		
		//llegim els kilometres
		while(aux[index] != '\n' && mal == 0){
			
			// comprovem que els caracters siguin valids
			if((aux[index] >= '0' && aux[index] <= '9') || aux[index] == '.'){
				auxkm[indexkm] = aux[index];
				index++;
				indexkm++;
			}else{
				//en cas de que estigui malament mostrara un missatge d'error
				mal = 1;
				printf("Hi ha hagut un error en els km de %s\n", auxnomp);
			}//else
		}//while

		//en cas de que no hi hagi errors s'emmagazema la informacio a la variable tipus pilot
		if(mal == 0){
			auxkm[indexkm] = 0;
			//convertim els kilometres a reals
			km = atof(auxkm);
			// convertim el nom del pilot a majuscules per evitar errors futurs
			malluscules(auxnomp);
			//emmagatzem els kilometres a la variable tipus pilot
			p.kilometres = km;
			//ubiquem el PDI a l'inici de la llista 
			lp = LLISTAPDI_P_vesInici(lp);
		}//if

		//anem emmagatzemant els pilots dins de la llista 
		while(!LLISTAPDI_P_fi(lp) && mal == 0){
			
			p_aux = LLISTAPDI_P_consulta(lp);
			malluscules(p_aux.nomPilot);
			//abans d'inserir comprovem que el pilot no aparegui mes d'una vegada al fitxer
			if(strcmp(p_aux.nomPilot, auxnomp) == 0){
				//en cas de que ja existeixi el pilot mostrara un missatge d'error
				printf("Error!! %s ja existeix\n", p.nomPilot);
				mal = 1;
			
			}else{
				//avancem 
				lp = LLISTAPDI_P_avanca(lp);
			}//else
		}//while

		//en cas de que estigui be inserirem el pilot a la llista
		if(mal == 0){
		
			lp = LLISTAPDI_P_insereix(lp, p); 
		}

		fgets(aux,100,f);
	}//while
	
	//en cas de que es generi un error a la lectura del fitxer, es mostrara un missatge d'error i el programa es tencara<
	if(mal == 1){
		printf("No s'han pogut inserir tots els jugadors\n");
		//es destrueix la llista de pilots
		lp = LLISTAPDI_P_destrueix(lp);
		//sortim del bucle del main
		*sortir = 1;
	}
	//tanquem el fitxer de text
	fclose(f);
	return lp;
}//tanquem la funcio

LlistaPDI_C extreuCircuits(LlistaPDI_C lc, FILE *f_c, int *sortir){
	char aux_nom[MAX], auxkm[MAX], auxpunts[MAX], aux[MAX];
	int index = 0, index_nom = 0, index_km = 0, index_punts = 0, mal = 0, compt = 0;
	Circuits c;
	Circuits c_aux;
	//generem la llista de circuits 
	lc = LLISTAPDI_C_crea();
	//obrim el fitxer de circuits en mode lectura
	f_c = fopen("Circuits.txt", "r");
	
	fgets(aux,100,f_c);

	//generem un bucle de lectura del fitxer per tal d'extreure els circuits
	while (!feof(f_c) && mal == 0){
		index = 0;
		index_nom = 0;
		index_km = 0;
		index_punts = 0;
		compt++;
		
		//llegim el nom del circuit
		while(aux[index] != '/' && mal == 0){
			//comprovem que els caracters que el componen siguin valids
			if((aux[index] >= 'A' && aux[index] <= 'Z') || (aux[index] >= 'a' && aux[index] <= 'z') || (aux[index] >= '0' && aux[index] <= '9') || aux[index] == ' '){
				//anem copiant el nom a una variable auxiliar
				aux_nom[index_nom] = aux[index];
				index++;
				index_nom++;
			}else{
				//en cas de que es trobi un caracter invalid es mostrara un error
				mal = 1;
				printf("Error!! El nom del circuit numero %d te un caracter invalid\n", compt);
			}//else
		}//while
		
		aux_nom[index_nom] = 0;
		index++;
		
		//llegim els kilometres que te el circuit
		while(aux[index] != '/' && mal == 0){
			//comprovem que etigui compost per els caracters valids
			if((aux[index] >= '0'  && aux[index] <= '9') || aux[index] == '.'){
				//anem copiant els kilometres a una variable auxiliar
				auxkm[index_km] = aux[index];
				index_km++;
				index++;
			}else{
				//en cas de que estigui malament es mostrara un missatge d'error
				mal = 1;
				printf("Hi ha hagut un problema amb el circuit %s\n", aux_nom);
			}//else
		}//while

		auxkm[index_km] = 0;
		index++;

		//llegim la puntuacio maxima del circuit
		while(aux[index] != '\n' && mal == 0){
			//comprovem que els caracters siguin valids
			if(aux[index] >= '0' && aux[index] <= '9'){
				//copiem la puntuacio a una variable auxiliar
				auxpunts[index_punts] = aux[index];
				index++;
				index_punts++;
			}else{
				//en cas de que estigui malament es mostrara un missatge d'error
				mal = 1;
				printf("Hi ha hagut un error amb els punts del circuit %s\n", aux_nom);
			}//else	
		}//while
		
		//si tot es correcte es procedeix amb l'emmagatzemament de la informacio a la variable tipus circuit
		if(mal == 0){
			
			auxpunts[index_punts] = 0;
			//copiem el nom a la variable tipus circuit
			strcpy(c.nomCircuit, aux_nom);
			//convertim els kilometres a reals i emmagatzemem la informacio
			c.kilometres = atof(auxkm);
			//convertim els punts a enter i emmagatzemem la informacio
			c.PuntsMax = atoi(auxpunts);
			//convertim el nom a majuscules per evitar problemes futurs
			malluscules(aux_nom);
			//situem el PDI a l'inici de la llista
			lc = LLISTAPDI_C_vesInici(lc);
		}//if

		//comprovem que el circuit a inserir no existeixi a la llista
		while(!LLISTAPDI_C_fi(lc) && mal == 0){
			c_aux = LLISTAPDI_C_consulta(lc);
			malluscules(c_aux.nomCircuit);
			
			//en cas de que el circuit estigui enregistrat es mostrara un missatge d'error
			if(strcmp(c_aux.nomCircuit, aux_nom) == 0){
				printf("El Circuit ja existeix!!\n");
				mal =1;
			}else{
				//en cas de que no el trobi avança
				lc = LLISTAPDI_C_avanca(lc);
			}//else
		}//while
		//si no existeix l'insereix
		if(mal == 0){
			lc = LLISTAPDI_C_insereix(lc, c);
		}

		fgets(aux,100,f_c);
	}//while
	//si s'ha detectat un error es mostra un missatge d'avis i el programa es tanca
	if(mal == 1){
		//destruim la llista de circuits
		lc = LLISTAPDI_C_destrueix(lc);
		//forçem la sortida del programa 
		*sortir = 1;
		printf("No s'han pogut inserir tots els circuits\n");
	}
	//tanquem el fitxer de text
	fclose(f_c);
	return lc;
}//funcio


LlistaPDI_P afegeixJugador(LlistaPDI_P lp, char nom_pilot[MAX], char nom_escuderia[MAX]){
	Pilots p;
	Pilots p_aux;
	int mal = 0, index_nom = 0, index_esc = 0, index = 0, indexesc = 0, trobat = 0;
	char auxnom[MAX], auxesc[MAX];
	
	//comprovem que el nom inserit per l'usuari contingui caracters correctes
	while(nom_pilot[index] != '\0' && mal == 0){
		if((nom_pilot[index] >= 'A' && nom_pilot[index] <= 'Z') || (nom_pilot[index] >= 'a' && nom_pilot[index] <= 'z') || (nom_pilot[index] >= '0' && nom_pilot[index] <= '9') || nom_pilot[index] == ' '){
			//anem copiant el nom a una variable auxiliar		
			auxnom[index_nom] = nom_pilot[index];
			index++;
			index_nom++;
		
		}else{
			//en cas de que estigui malament es mostra un missatge d'error
			mal = 1;
			printf("Hi ha un caracter no permes en el nom del pilot\n");
		}//else	
	}//while

	auxnom[index_nom] = 0;
	
	//comprovem que el nom de l'escuderia contingui caracters correctes
	while(nom_escuderia[indexesc] != '\0' && mal == 0){
		if((nom_escuderia[indexesc] >= 'A' && nom_escuderia[indexesc] <= 'Z') || (nom_escuderia[indexesc] >= 'a' && nom_escuderia[indexesc] <= 'z') || (nom_escuderia[indexesc] >= '0' && nom_escuderia[indexesc] <= '9') || nom_escuderia[indexesc] == ' '){
			//anem copiant el nom de l'escuderia a una variable auxiliar
			auxesc[index_esc] = nom_escuderia[indexesc];
			indexesc++;
			index_esc++;
			
		}else{
			//en cas de que estigui malament es mostrara un missatge d'error
			mal = 1;
			printf("Hi ha un caracter no permes en la escuderia\n");
		}//if
	}//while

	auxesc[index_esc] = 0;
	
	//en cas de que tot estigui correcte emmagatzemarem la informacio a una variable tipus pilot
	if(mal == 0){
				
		index = 0;
		//guardem el nom del pilot
		strcpy(p.nomPilot, auxnom);
		//guardem el nom de l'escuderia
		strcpy(p.nomEscuderia, auxesc);
		//convertim el nom del pilot a majuscules per estalviar problemes futurs
		malluscules(auxnom);
		//situem el PDI al comencament de la llista 
		lp = LLISTAPDI_P_vesInici(lp);
		
		//comporvem que el nou pilot no estigui ja enregistrat
		while(!LLISTAPDI_P_fi(lp) && trobat == 0){
			
			p_aux = LLISTAPDI_P_consulta(lp);
			malluscules(p_aux.nomPilot);
				
			//en cas de que el pilot ja existeixi es mostrara un missatge d'avis i s'activara l'error
			if(strcmp(p_aux.nomPilot, auxnom) == 0){
				printf("Error! El pilot ja existeix\n");
				trobat = 1;
			}else{
				//en cas contrar avancem el PDI
				lp = LLISTAPDI_P_avanca(lp);
			}//else
		}//while
		
		//en cas de que tot estigui correcte s'afageix el nou pilot a la llista
		if(trobat == 0){
			p.punts = 0;
			p.kilometres = 0;
			lp = LLISTAPDI_P_insereix(lp, p);
			printf(" El pilot ha sigut inserit correctament\n");
		}
	}//if
	return lp;
}//tanquem la funcio

LlistaPDI_P esborraPilot (LlistaPDI_P lp, char nom_pilot[MAX]){
	Pilots p;
	char aux[MAX];
	int index = 0, indexaux = 0, mal = 0;
	
	//anem llegint el nom del pilot
	while(nom_pilot[index] != '\0' && mal == 0){
		//comprovem que el nom estigui compost per caracters valids
		if((nom_pilot[index] >= 'A' && nom_pilot[index] <= 'Z') || (nom_pilot[index] >= 'a' && nom_pilot[index] <= 'z') || (nom_pilot[index] >= '0' && nom_pilot[index] <= '9') || nom_pilot[index] == ' '){
			//anem copiant el nom del pilot a una variable auxiliar
			aux[indexaux] = nom_pilot[index];
			index++;
			indexaux++;
		}else{
			//en cas de que el nom inserit no sigui valid es mostra un missatge d'error
			mal = 1;
			printf("Hi ha hagut un error en el nom\n");
		}//else
	}//while

	//en cas de que no hi hagui problemes amb el nom es começa a buscar a la llista de pilots
	if(mal == 0){
		aux[indexaux] = 0;
		//convertim el nom a majuscules per comparar-lo amb la resta
		malluscules(aux);
		//situem el PDI al comencament de la llista
		lp = LLISTAPDI_P_vesInici(lp);
		
		//comprovem pilot a pilot
		while(!LLISTAPDI_P_fi(lp) && mal == 0){
			p = LLISTAPDI_P_consulta(lp);
			malluscules(p.nomPilot);
			//si es troba el pilot s'esborra
			if(strcmp(p.nomPilot, aux) == 0){
				lp = LLISTAPDI_P_esborra(lp);
				mal = 1;
				printf("El pilot ha sigut borrat correctament\n");
			}else{
				//en cas de que no es trobi avancem el PDI
				lp = LLISTAPDI_P_avanca(lp);
			}//else
		}//while
	}//if

	//en cas de no trobar el pilot a la llista es mostra un missatge d'error
	if(mal == 0){
		printf("El pilot no existeix\n");
	}
	return lp;
}//fi funcio
		
LlistaPDI_C afegeixCircuit(LlistaPDI_C lc, char nom_cursa[MAX], float km, int punts){
	char auxnom[MAX], auxmall[MAX];
	int index = 0, indexaux = 0, trobat = 0, mal = 0;
	Circuits c;
	Circuits c_aux;

	//llegim el nom inserit per l'usuari
	while(nom_cursa[index] != '\0' && mal == 0){
		//comprovem que el nom estigui compost per caracters valids
		if((nom_cursa[index] >= 'A' && nom_cursa[index] <= 'Z') || (nom_cursa[index] >= 'a' && nom_cursa[index] <= 'z') || (nom_cursa[index] >= '0' && nom_cursa[index] <= '9') || nom_cursa[index] == ' '){
			
			//anem copiant el nom a una variable auxiliar
			auxnom[indexaux] = nom_cursa[index];
			index++;
			indexaux++;
		}else{
			//en cas de que el nom estigui malament es mostra  un missatge d'error
			mal = 1;
			printf("Error! Hi ha un caracter no permes\n");
			
		}//else
	}//while

	//en cas de que el nom sigui correcte comprovem que no existeixi ja 
	if(mal == 0){
		//situem el PDI a l'inici de la llista 
		lc = LLISTAPDI_C_vesInici(lc);
		auxnom[indexaux] = 0;
		//copiem el nom a una variable tipus circuit
		strcpy(c.nomCircuit, auxnom);
		malluscules(auxnom);
		//comprovem que el circuit no exiteixi i, si es el cas, l'insereix
		while(!trobat && !LLISTAPDI_C_fi(lc)){
			c_aux = LLISTAPDI_C_consulta(lc);
			strcpy(auxmall, c_aux.nomCircuit);
			malluscules(auxmall);
			if( strcmp(auxmall, auxnom) == 0){
				trobat = 1;
				printf("El Circuit no es pot inserir perque ja existeix\n");

			}else{
				lc = LLISTAPDI_C_avanca(lc);
			}
		}
		if(trobat==0){
			c.kilometres = km;
			c.PuntsMax = punts;
			lc = LLISTAPDI_C_insereix(lc, c);
			printf("El circuit s'ha inserit correctament\n");
		}
	}
	return lc;
}

LlistaPDI_C esborraCircuit(LlistaPDI_C lc, char nom_circuit[MAX]){
	char aux[MAX]; 
	//char c_aux[MAX];
	int trobat = 0, mal = 0;
	int index = 0, indexaux = 0;
	Circuits c;
	while(nom_circuit[index] != '\0' && mal == 0){
		if((nom_circuit[index] >= 'A' && nom_circuit[index] <= 'Z') || (nom_circuit[index] >= 'a' && nom_circuit[index] <= 'z') || (nom_circuit[index] >= '0' && nom_circuit[index] <= '9') || nom_circuit[index] == ' '){

			aux[indexaux] = nom_circuit[indexaux];
			index++;
			indexaux++;
		}else{
			mal = 1;
			printf("Error! El nom conte un caracter no permes\n");
		}
	}
	if(mal == 0){
		//despres d'haver comprovat que el nom sigui correcte el busquem per la llista i si el troba l'elimina
		aux[indexaux] = 0;
		malluscules(aux);
		lc = LLISTAPDI_C_vesInici(lc);
		while(!LLISTAPDI_C_fi(lc) && trobat== 0){
			c = LLISTAPDI_C_consulta(lc);
			malluscules(c.nomCircuit);
			if(strcmp(aux, c.nomCircuit) == 0){
				lc = LLISTAPDI_C_esborra(lc);
				printf("El circuit s'ha borrat correctament\n");
				trobat = 1;

			}else{
				
				lc = LLISTAPDI_C_avanca(lc);
			}
		}
	}
	if(trobat == 0){
		printf("Error! No existeix el circuit\n");
	}
	
	return lc;
}

void mostraPilots(LlistaPDI_P lp){
	Pilots p;
	printf("--------------------------Pilots apuntats-----------------------------------\n");
	printf("  Nom \t Escuderia \t Punts Acumulats \t Km Acumulats\n");
	printf("------------------------------------------------------------------------------\n");		
	lp = LLISTAPDI_P_vesInici(lp);
	while(!LLISTAPDI_P_fi(lp)){
		p = LLISTAPDI_P_consulta(lp);
		printf(" %s         %s          %d                %.2f\n", p.nomPilot, p.nomEscuderia, p.punts, p.kilometres);
		lp = LLISTAPDI_P_avanca(lp);

	}
}

void circuitsDisponibles (LlistaPDI_C lc, int *mal){
	Circuits c;
	*mal = 0;
	lc = LLISTAPDI_C_vesInici(lc);
	if(!LLISTAPDI_C_buida(lc)){

		while(!LLISTAPDI_C_fi(lc)){
			c = LLISTAPDI_C_consulta(lc);
			printf(" - %s\n", c.nomCircuit);
			lc = LLISTAPDI_C_avanca(lc);
		}
	}else{
		printf("No hi han circuits a mostrar\n");
		*mal = 1;
	}
}

LlistaPDI_P circuitEscollit (LlistaPDI_C lc, char nom_circuit[MAX], LlistaPDI_P lp){
	char aux[MAX];
	int index = 0, indexaux = 0;
	int trobat = 0, mal = 0;
	Circuits c;
	
	while(nom_circuit[index] != '\0' && mal == 0){
		if((nom_circuit[index] >= 'A' && nom_circuit[index] <= 'Z') || (nom_circuit[index] >= 'a' && nom_circuit[index] <= 'z') || (nom_circuit[index] >= '0' && nom_circuit[index] <= '9') || nom_circuit[index] == ' '){

			aux[indexaux] = nom_circuit[index];
			index++;
			indexaux++;
		}else{
			printf("Hi ha hagun un error amb el circuit escollit\n");
			mal = 1;
		}
	}
	//un cop comprovat que el nom del circuit es correcte el busquem per la  llista i printem les seves caracteristiques
	aux[index] = 0;
	if(mal == 0){
		
		lc = LLISTAPDI_C_vesInici(lc);
	
		while(!LLISTAPDI_C_fi(lc) && trobat == 0){
			malluscules(aux);
			c = LLISTAPDI_C_consulta(lc);
			malluscules(c.nomCircuit);
			if(strcmp(aux, c.nomCircuit)== 0){
				
				printf("\nEl circuit escollit te %.2f km i la puntuacio maxima es de %d\n\n", c.kilometres, c.PuntsMax);
				
				lp = ferCursa(c, lp);
				trobat = 1;
			
			}else{
				
				lc = LLISTAPDI_C_avanca(lc);
			
			}
		}
		if (trobat == 0){
			
			printf("El circuit escollit no existeix\n");
		
		}
	}
	return lp;
}

LlistaPDI_P ferCursa (Circuits c, LlistaPDI_P lp){
	
	int trobat = 0;
	int PuntsMaxPilots = 0, compt = 0;
	float KmMaxPilots = 0, Sort= 0, Puntuacio = 0;
	LlistaPDI_P lp_aux;
	Pilots p;
	Pilots p_aux;
	Estadistica e;

	lp_aux = LLISTAPDI_P_crea();
	
	
	printf("\n-----Resultats-------------------------------------------\n");
	printf("Posicio Nom                    Puntuacio            Sort\n");
	printf("--------------------------------------------------------\n");
	
	// situem el PDI a l'inici de la llista
	lp = LLISTAPDI_P_vesInici (lp);

	// extreiem la suma total dels punts de tots els pilots
	PuntsMaxPilots = PuntsMaximsPilots(lp);

	// extreiem la suma total del kilometres de tots els pilots
	KmMaxPilots = KmMaximsPilots (lp);
	 
	compt = 0;

	// fem servir un bucle per modificar la informacio de tots els pilots disponibles
	while (!LLISTAPDI_P_fi(lp)){
	
		Puntuacio = 0;
		
		// llegim la informacio del pilot de la llista 
		p = LLISTAPDI_P_consulta (lp);
		
		// en cas de que el pilot no hagui realitzat cap cursa se li assignara una puntuacio aleatoria
		if (p.punts == 0){
			
			//generem una puntuacio aleatoria entre 0 i la maxima del circuit	
			p.punts = rand () % c.PuntsMax;
			Puntuacio = p.punts;
			Sort = rand() %10;
			Sort = Sort / 10;

		}else{
			
			// generem un valor aleatori entre 0 i 1 que representa la sort
			Sort = rand() % 10;
			Sort = Sort / 10;
			
			// generem la puntuacio mitjancant la formula proporcionada a l'enunciat
			Puntuacio =  (c.PuntsMax/2) * ((p.punts/PuntsMaxPilots) + (p.kilometres/KmMaxPilots)) * Sort;
		}

		strcpy (p_aux.nomPilot, p.nomPilot);
		p_aux.punts = Puntuacio;
		p_aux.kilometres = Sort;
		lp_aux = LLISTAPDI_P_vesInici(lp_aux);
		strcpy(e.nomPilot, p.nomPilot);
		strcpy(e.nomCircuit, c.nomCircuit);
		e.punts = Puntuacio;
		
		trobat = 0;
		//col·loquem els punts al pilot corresponent 
		while ((!LLISTAPDI_P_fi(lp_aux)) && !trobat){
			
			if (LLISTAPDI_P_buida(lp_aux)){
				lp_aux = LLISTAPDI_P_insereix(lp_aux, p_aux);
				trobat = 1;
			}else{
				if (LLISTAPDI_P_consulta(lp_aux).punts > p_aux.punts){
					lp_aux = LLISTAPDI_P_avanca(lp_aux);
				}else{
					lp_aux = LLISTAPDI_P_insereix (lp_aux, p_aux);
					trobat = 1;
				}
			}
		}
		
		if (!trobat){
			lp_aux = LLISTAPDI_P_insereix (lp_aux, p_aux);
		}

		p.punts += Puntuacio;
		p.kilometres += c.kilometres;
		p.le = insereixEstadistica(p.le, e);
		lp = substitueix(lp, p);	
		lp = LLISTAPDI_P_avanca(lp);


	// tanquem el while 
	}
	
	lp_aux = LLISTAPDI_P_vesInici(lp_aux);
	// despres d'haver acabat de fer la cursa amb tots els pilots els printem ordenats
	while (!LLISTAPDI_P_fi(lp_aux)){
		
		compt ++;
		p_aux = LLISTAPDI_P_consulta (lp_aux);

		printf ("\n%d     %s                          %d       %.2f", compt, p_aux.nomPilot, p_aux.punts, p_aux.kilometres);
		lp_aux = LLISTAPDI_P_avanca (lp_aux);
	}
	
	lp_aux = LLISTAPDI_P_destrueix (lp_aux);
	return lp;
}

//aquesta funcio substitueix l'element del propi pdi
LlistaPDI_P substitueix(LlistaPDI_P lp, Pilots p){
	lp.ant->seg->p = p;
	return lp;
}

LlistaPDI_E insereixEstadistica(LlistaPDI_E le, Estadistica e){
		int trobat = 0;
		Estadistica e_aux;
		char circuit[MAX];
		char aux[MAX];

		le = LLISTAPDI_E_vesInici(le);
		
		if(LLISTAPDI_E_buida(le)){
			
			le = LLISTAPDI_E_insereix(le, e);
			
		}else{
			//busca si ja existeteix algun circuit fet d'aquest pilot i si hi ha el substitueix segons la puntuacio	
			while(!LLISTAPDI_E_fi(le) && trobat == 0){

				e_aux = LLISTAPDI_E_consulta(le);
				strcpy(aux, e_aux.nomCircuit);
				strcpy(circuit, e.nomCircuit);
				malluscules(aux);
				malluscules(circuit);
				
				if(strcmp(aux, circuit) == 0){
				
					if(e.punts > e_aux.punts){
						le = LLISTAPDI_E_esborra(le);
						le = LLISTAPDI_E_insereix(le, e);

					}
					trobat = 1;
				
				}else{

					le = LLISTAPDI_E_avanca(le);
				}
			}
			if(trobat == 0){
				le = LLISTAPDI_E_insereix(le, e);
			}
		}

		return le;
}
	
int PuntsMaximsPilots(LlistaPDI_P lp){
	
	int punts = 0;
	Pilots p;
	lp = LLISTAPDI_P_vesInici(lp);

	//Realitzem la suma total de tots els pilots enregistrats
	while(!LLISTAPDI_P_fi(lp)){
		p = LLISTAPDI_P_consulta(lp);
		punts += p.punts;
		lp = LLISTAPDI_P_avanca(lp);
	}
	return punts;
}

float KmMaximsPilots (LlistaPDI_P lp){
	float km = 0;
	Pilots p;
	lp = LLISTAPDI_P_vesInici(lp);
	while(!LLISTAPDI_P_fi(lp)){
		p = LLISTAPDI_P_consulta(lp);
		km += p.kilometres;
		lp = LLISTAPDI_P_avanca(lp);
	}
	return km;
}

Cua circuitAuxiliar (char nom_circuit[MAX], Cua c, LlistaPDI_C lc){
	char aux[MAX], nomc[MAX];
	int index = 0, indexaux = 0, trobat = 0;
	Circuits z;
	CircuitsCua x;
	while(nom_circuit[index] != '\0'){
		aux[indexaux] = nom_circuit[index];
		index++;
		indexaux++;
	}
	aux[index] = 0;
	lc = LLISTAPDI_C_vesInici(lc);
	malluscules(aux);
	while(!LLISTAPDI_C_fi(lc) && trobat == 0){
		
		z = LLISTAPDI_C_consulta(lc);
		strcpy(nomc, z.nomCircuit);
		malluscules(nomc);
		//Afegim els circuits escollit en la cua
		if(strcmp(nomc, aux) == 0){
			strcpy(x.nomCircuit, z.nomCircuit);
			x.Kilometres = z.kilometres;
			x.punts = z.PuntsMax;
			CUA_encua(&c, x);
			trobat = 1;
		
		}else{

			lc = LLISTAPDI_C_avanca(lc);
		}
	}
	if(trobat == 0){
		printf(" El circuit no existeix\n");
	
	}
	return c;
}

LlistaPDI_P ferCampionat(Cua c, LlistaPDI_P lp){
	
	CircuitsCua z;
	Circuits cir;
		
	while(!CUA_buida(c)){
		
		z = CUA_cap(c);
		printf("\n\n------------------------- %s ----------------------------\n\n", z.nomCircuit);
		printf("El circuit escollit te %.2f Km i la puntuació màxima es de %d\n", z.Kilometres, z.punts);
		
		strcpy(cir.nomCircuit, z.nomCircuit);
		cir.kilometres = z.Kilometres;
		cir.PuntsMax = z.punts;
		lp = ferCursa(cir, lp);
		CUA_desencua(&c);

	}
	CUA_destrueix(&c);
	return lp;
}

//emmagatzem els pilots de la llista PDI al fitxer de text
LlistaPDI_P insereixPilot(LlistaPDI_P lp, FILE *f){
	int indexnom = 0, indexesc = 0, index = 0;
	char aux_nom[MAX], aux_esc[MAX];
	Pilots p;
	
	//coloquem el PDI a l'inici de la llista
	lp = LLISTAPDI_P_vesInici(lp);
	//obrim el fitxer de text en mode escriptura
	f = fopen("Pilots.txt","w");
		
		//realitzem un bucle que emmagatzemi els pilots en el fitxer
		while(!LLISTAPDI_P_fi(lp)){
			
			//llegim el pilot de la llista
			p = LLISTAPDI_P_consulta(lp);
			indexesc = 0;
			indexnom = 0;
			index = 0;
			
			//copiem el nom del pilot
			while(p.nomPilot[index] != '\0'){
				aux_nom[indexnom] = p.nomPilot[index];
				indexnom++;
				index++;
			}
			aux_nom[indexnom] = 0;
		
			index = 0;
			
			//emmagatzem el nom de l'escuderia 
			while(p.nomEscuderia[index] != '\0'){
				aux_esc[indexesc] = p.nomEscuderia[index];
				index++;
				indexesc++;
			}
			aux_esc[indexesc] = 0;
			
			//emmagatzem les variables dins el fitxer de text
			fprintf(f,"%s/%s/%d/%f\n", aux_nom, aux_esc, p.punts, p.kilometres);
			//avancem al seguent pilot
			lp = LLISTAPDI_P_avanca(lp);
		}//tanquem el while
	//tanquem el fiter de text	
	fclose(f);
	//destruim la llista que conte els pilots
	lp = LLISTAPDI_P_destrueix(lp);
	return lp;
}// tanquem la funcio

//emmagatzem els circuits al fitxer de text
LlistaPDI_C insereixCircuit(LlistaPDI_C lc, FILE *f_c){
	int indexnom = 0, index = 0;
	char aux[MAX];
	Circuits c;
	//col·loquem el PDI a l'inici de la llista
	lc = LLISTAPDI_C_vesInici(lc);
	//obrim el fitxer de text
	f_c = fopen("Circuits.txt","w");
		
		//iniciem un bucle que llegeixi els circuits un a un
		while(!LLISTAPDI_C_fi(lc)){
			//extreiem el circuit de la llista 
			c = LLISTAPDI_C_consulta(lc);
			indexnom = 0;
			index = 0;
			//copiem el nom del circuit a la variable auxiliar
			while(c.nomCircuit[index] != '\0'){
				aux[indexnom] = c.nomCircuit[index];
				index++;
				indexnom++;
			}
			aux[indexnom] = 0;
			//emmagatzem el nom del circuit i les seves caracteristiques al fitxer
			fprintf(f_c,"%s/%f/%d\n", aux, c.kilometres, c.PuntsMax);
			lc = LLISTAPDI_C_avanca(lc);
		}
	//es destrueix la llista de circuits
	lc = LLISTAPDI_C_destrueix(lc);
	//tanquem el fitxer
	fclose(f_c);
	return lc;
}

void printaEstadistiques(LlistaPDI_P lp, LlistaPDI_C lc){ 

	Pilots p;
	Circuits c;
	Estadistica e;
	char aux1[MAX], aux2[MAX];
	int trobat = 0;
	
	printf("---------Millor Puntuacio--------------------------------------------\n");
	printf(" Nom       ");
	
	//ubiquem el PDI al primer element de la llista de circutis
	lc = LLISTAPDI_C_vesInici(lc);
	
	//printem els millors resultats de cada pilot a cadascun dels circuits
	while(!LLISTAPDI_C_fi(lc)){
		c = LLISTAPDI_C_consulta(lc);
		printf("%s             ", c.nomCircuit);
		lc = LLISTAPDI_C_avanca(lc);
	}

	printf("\n----------------------------------------------------------------------");
	
	lc = LLISTAPDI_C_vesInici(lc);

	lp = LLISTAPDI_P_vesInici(lp);
	
	//printem per pantalla les millors puntuacions a cada circuit
	while(!LLISTAPDI_P_fi(lp)){
		
		p = LLISTAPDI_P_consulta(lp);
		
		printf("\n %s           ", p.nomPilot);
		
		lc = LLISTAPDI_C_vesInici(lc);

		while(!LLISTAPDI_C_fi(lc)){
		
			c = LLISTAPDI_C_consulta(lc);
			
			p.le = LLISTAPDI_E_vesInici(p.le);
			
			strcpy(aux1, c.nomCircuit);
			
			malluscules(aux1);
			
			p.le = LLISTAPDI_E_vesInici (p.le);
			trobat = 0;
			while(!LLISTAPDI_E_fi(p.le) && (trobat == 0)){
		
				e = LLISTAPDI_E_consulta(p.le);
				strcpy(aux2, e.nomCircuit);
				malluscules(aux2);
		
				if(strcmp(aux2, aux1) == 0){
					printf(" %d               ", e.punts);
					trobat = 1;
				}else{
					p.le = LLISTAPDI_E_avanca(p.le);
				}
			}

			if(trobat == 0){
				printf("-                  ");
			}

			lc = LLISTAPDI_C_avanca(lc);
		}
		printf ("\n");
		lp = LLISTAPDI_P_avanca(lp);
	}
			
}

void malluscules(char nom[MAX]){
	int index = 0;

	while(nom[index] != '\0'){
		if((nom[index] >= 'a') && (nom[index] <= 'z')){
			nom[index] = nom[index] - ('a' - 'A');
		}
		index++;
	}
	nom[index] = 0;
}
