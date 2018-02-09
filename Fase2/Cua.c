#include "Cua.h"

Cua CUA_crea(){
	CircuitsCua C;
	Cua c;

	c.pri = (NodeCua*)malloc(sizeof(NodeCua));
	if(c.pri == NULL){
		printf("No hi ha memoria per utilitzar\n");
	
	}else{
	
		c.pri -> C = C;
		c.pri -> seg = NULL;
		c.ult = c.pri;
	}
	return c;
}

void CUA_encua(Cua *c, CircuitsCua C){
	NodeCua *aux;
	aux = (NodeCua*)malloc(sizeof(NodeCua));
	if(aux == NULL){
		printf(" No hi ha memoria per aux\n");
	
	}else{

		aux -> C = C;
		aux -> seg = NULL;
		c -> ult -> seg = aux;
		c -> ult = aux;
	}
}

void CUA_desencua(Cua *c){
	NodeCua *aux;
	if(c -> pri -> seg == NULL){
		printf(" No hi ha res a desencuar\n");
	
	}else{
		aux = c -> pri -> seg;
		c -> pri -> seg = aux -> seg;
		if(aux -> seg == NULL){
			c -> ult = c -> pri;
		}
		free(aux);
	}
}

CircuitsCua CUA_cap(Cua c){
	CircuitsCua C;
	if(c.pri -> seg != NULL){
		C = c.pri -> seg -> C;
	}else{
		printf("No hi ha res en la cua\n");
	}
	return C;
}

int CUA_buida(Cua c){
	return c.pri -> seg == NULL;
}

void CUA_destrueix(Cua *c){
	NodeCua *aux;
	while(c -> pri != NULL){
		aux = c -> pri;
		c -> pri = c -> pri -> seg;
		free(aux);
	}
	c -> ult = NULL;
}
