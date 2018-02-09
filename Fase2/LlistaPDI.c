#include "LlistaPDI.h"

LlistaPDI_P LLISTAPDI_P_crea(){
	LlistaPDI_P lp;
	Pilots p;
	p.le = LLISTAPDI_E_crea();
	lp.pri = (NodeP*) malloc (sizeof(NodeP));
	if (lp.pri == NULL){
		printf (" Error al demanar memoria dels pilots\n");
	}else{
		lp.pri -> p = p;
		lp.pri -> seg = NULL;
		lp.ant = lp.pri;
		
	}
	return lp;
}// tanquem 

LlistaPDI_P LLISTAPDI_P_insereix(LlistaPDI_P lp, Pilots p){
	NodeP *aux;
	aux = (NodeP*) malloc (sizeof(NodeP));
	p.le = LLISTAPDI_E_crea();
	if (aux == NULL){
		printf (" Error al demanar memoria pel pilot \n");
	}else{
		aux -> p = p;
		aux -> seg = lp.ant -> seg;
		lp.ant -> seg = aux;
		lp.ant = aux;
	}
	return lp;
} 

LlistaPDI_P LLISTAPDI_P_esborra (LlistaPDI_P lp){
	NodeP *aux;
	if (lp.ant -> seg != NULL){
		aux = lp.ant -> seg;
		aux -> p.le = LLISTAPDI_E_destrueix(aux -> p.le);
		lp.ant -> seg = aux ->seg;
		free (aux);
	}else{
		printf("No hi ha res a borra\n");
	}
	return lp;
}

Pilots LLISTAPDI_P_consulta(LlistaPDI_P lp){
	Pilots p;
	if(lp.ant -> seg == NULL){
		printf("Error, no hi ha element a consultar\n");
	}else{
		p = lp.ant -> seg->p;
	}
	return p;
}

int LLISTAPDI_P_buida(LlistaPDI_P lp){
	return lp.pri -> seg == NULL;
}

LlistaPDI_P LLISTAPDI_P_vesInici(LlistaPDI_P lp){
	lp.ant = lp.pri;
	return lp;
}

LlistaPDI_P LLISTAPDI_P_avanca(LlistaPDI_P lp){
	if(lp.ant -> seg == NULL){
		printf("Error, no es pot avaçar mes\n");
	}else{
		lp.ant = lp.ant -> seg;
	}
	return lp;
}

int LLISTAPDI_P_fi(LlistaPDI_P lp){
	return lp.ant ->seg == NULL;
}//tanquem

LlistaPDI_P LLISTAPDI_P_destrueix(LlistaPDI_P lp){
	NodeP *aux;
	while(lp.pri -> seg != NULL){
		aux = lp.pri;
		lp.pri = lp.pri -> seg;
		free(aux);
	}
	free(lp.pri);
	return lp;
}//tanquem

LlistaPDI_C LLISTAPDI_C_crea(){
	LlistaPDI_C lc;
	Circuits c;
	lc.pri = (NodeC*)malloc(sizeof(NodeC));
	if(lc.pri == NULL){
		printf("Error!! NO hi ha memoria\n");
	}else{
		lc.pri -> c = c;
		lc.pri -> seg = NULL;
		lc.ant = lc.pri;
	}
	return lc;
}//tanquem

LlistaPDI_C LLISTAPDI_C_insereix(LlistaPDI_C lc, Circuits c){
	NodeC *aux;
	aux = (NodeC*)malloc(sizeof(NodeC));
	if(aux == NULL){
		printf("Error!! No hi ha memoria\n");
	}else{
		aux -> c = c;
		if(lc.pri -> seg == NULL){
			aux -> seg = NULL;
			lc.pri -> seg = aux;
			lc.ant = aux;
		}else{
			aux -> seg = lc.ant -> seg;
			lc.ant -> seg = aux;
			lc.ant = aux;
		}
	}
	return lc;
}

LlistaPDI_C LLISTAPDI_C_esborra(LlistaPDI_C lc){
	NodeC *aux;
	if(lc.ant -> seg == NULL){
		printf("No hi ha res a esborrar\n");
	}else{
		aux = lc.ant -> seg;
		lc.ant -> seg = aux -> seg;
		free(aux);
	}
	return lc;
}

Circuits LLISTAPDI_C_consulta(LlistaPDI_C lc){
	Circuits c;
	if(lc.ant -> seg == NULL){
		printf("Error! No hi ha res a consultar\n");
	}else{
		c = lc.ant -> seg ->c;
	}
	return c;
}//tanquem

int LLISTAPDI_C_buida(LlistaPDI_C lc){
	return lc.pri -> seg == NULL;
}//tanquem

LlistaPDI_C LLISTAPDI_C_vesInici(LlistaPDI_C lc){
	lc.ant = lc.pri;
	return lc;
}//tanquem

LlistaPDI_C LLISTAPDI_C_avanca(LlistaPDI_C lc){
	if(lc.ant -> seg == NULL){
		printf("Error!! No es pot avançar\n");
	}else{
		lc.ant = lc.ant -> seg;
	}
	return lc;
}

int LLISTAPDI_C_fi(LlistaPDI_C lc){
	return lc.ant -> seg == NULL;
}

LlistaPDI_C LLISTAPDI_C_destrueix(LlistaPDI_C lc){
	NodeC *aux;
	while(lc.pri -> seg != NULL){
		aux = lc.pri;
		lc.pri = lc.pri -> seg;
		free(aux);
	}
	free(lc.pri);
	return lc;
}

LlistaPDI_E LLISTAPDI_E_crea(){
	LlistaPDI_E le;
	Estadistica e;
	le.pri = (NodeE*)malloc(sizeof(NodeE));
	if(le.pri == NULL){
		printf("No hi ha memoria per les estaditiques\n");
	}else{
		le.pri -> e = e;
		le.pri -> seg = NULL;
		le.ant = le.pri;
	}
	return le;
}

LlistaPDI_E LLISTAPDI_E_insereix(LlistaPDI_E le, Estadistica e){
	NodeE *aux;
	aux = (NodeE*)malloc(sizeof(NodeE));
	if(aux == NULL){
		printf("No hi ha memoria per introduir un element\n");
	}else{
		aux -> e = e;
		aux -> seg = le.ant -> seg;
		le.ant -> seg = aux;
		le.ant = aux;
	}
	return le;
}

LlistaPDI_E LLISTAPDI_E_esborra(LlistaPDI_E le){
	NodeE *aux;
	aux = le.ant -> seg;
	if(aux == NULL){
		printf("No hi ha res a borrar\n");
	}else{
		le.ant -> seg = aux -> seg;
		free(aux);
	}
	return le;
}

Estadistica LLISTAPDI_E_consulta(LlistaPDI_E le){
	Estadistica e;
	if(le.ant -> seg == NULL){
		printf("Error!! No hi ha res a consultar\n");
	}else{
		e = le.ant -> seg -> e;
	}
	return e;
}
int LLISTAPDI_E_buida(LlistaPDI_E le){
	return le.pri -> seg == NULL;
}

LlistaPDI_E LLISTAPDI_E_vesInici(LlistaPDI_E le){
	le.ant = le.pri;
	return le;
}

LlistaPDI_E LLISTAPDI_E_avanca(LlistaPDI_E le){
	if(le.ant -> seg == NULL){
		printf("No es pot avancar\n");
	}else{
		le.ant = le.ant -> seg;
	}
	return le;
}

int LLISTAPDI_E_fi(LlistaPDI_E le){
	return le.ant -> seg == NULL;
}

LlistaPDI_E LLISTAPDI_E_destrueix(LlistaPDI_E le){
	NodeE *aux;
	while(le.pri -> seg != NULL){
		aux = le.pri -> seg;
		le.pri -> seg = aux -> seg;
		free(aux);
	}
	return le;
}
