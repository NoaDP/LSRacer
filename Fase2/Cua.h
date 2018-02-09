#ifndef _CUA_H_
#define _CUA_H_

#define MAX 100

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char nomCircuit[MAX];
	float Kilometres;
	int punts;
}CircuitsCua;

typedef struct N {
	CircuitsCua C;
	struct N*seg;
}NodeCua;

typedef struct{
	NodeCua *pri;
	NodeCua *ult;
}Cua;

Cua CUA_crea();
void CUA_encua(Cua *c, CircuitsCua C);
void CUA_desencua(Cua *c);
CircuitsCua CUA_cap(Cua c);
int CUA_buida(Cua c);
void CUA_destrueix(Cua *c);

#endif
