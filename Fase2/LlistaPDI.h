#ifndef _LLISTAPDI_H_
#define _LLISTAPDI_H_

#define MAX 100

#include <stdio.h>
#include <stdlib.h>


typedef struct {
	char nomPilot[MAX];
	char nomCircuit[MAX];
	int punts;
}Estadistica;

typedef struct {
	char nomCircuit[MAX];
	float kilometres;
	int PuntsMax;
}Circuits;

typedef struct Ne{
	Estadistica e;
	struct Ne* seg;
}NodeE;

typedef struct Nc{
	Circuits c;
	struct Nc* seg;
}NodeC;

typedef struct{
	NodeE* pri;
	NodeE* ant;
}LlistaPDI_E;

typedef struct{
	NodeC* pri;
	NodeC* ant;
}LlistaPDI_C;

typedef struct {
	char nomPilot[MAX];
	char nomEscuderia[MAX];
	int punts;
	float kilometres;
	LlistaPDI_E le;
}Pilots;


typedef struct Np{
	Pilots p;
	struct Np* seg;
}NodeP;

typedef struct{
	NodeP* pri;
	NodeP* ant;
}LlistaPDI_P;

LlistaPDI_P LLISTAPDI_P_crea ();
LlistaPDI_P LLISTAPDI_P_insereix (LlistaPDI_P  lp, Pilots p);
LlistaPDI_P LLISTAPDI_P_esborra (LlistaPDI_P lp);
Pilots  LLISTAPDI_P_consulta (LlistaPDI_P lp);
int LLISTAPDI_P_buida (LlistaPDI_P lp);
LlistaPDI_P LLISTAPDI_P_vesInici (LlistaPDI_P lp);
LlistaPDI_P LLISTAPDI_P_avanca (LlistaPDI_P lp);
int LLISTAPDI_P_fi (LlistaPDI_P lp);
LlistaPDI_P LLISTAPDI_P_destrueix (LlistaPDI_P lp);

LlistaPDI_C LLISTAPDI_C_crea ();
LlistaPDI_C LLISTAPDI_C_insereix (LlistaPDI_C lc, Circuits c);
LlistaPDI_C LLISTAPDI_C_esborra (LlistaPDI_C lc);
Circuits LLISTAPDI_C_consulta (LlistaPDI_C lc);
int LLISTAPDI_C_buida (LlistaPDI_C lc);
LlistaPDI_C LLISTAPDI_C_vesInici (LlistaPDI_C lc);
LlistaPDI_C LLISTAPDI_C_avanca (LlistaPDI_C lc);
int LLISTAPDI_C_fi (LlistaPDI_C lc);
LlistaPDI_C LLISTAPDI_C_destrueix (LlistaPDI_C lc);

LlistaPDI_E LLISTAPDI_E_crea();
LlistaPDI_E LLISTAPDI_E_insereix(LlistaPDI_E le, Estadistica e);
LlistaPDI_E LLISTAPDI_E_esborra(LlistaPDI_E le);
Estadistica LLISTAPDI_E_consulta(LlistaPDI_E le);
int LLISTAPDI_E_buida(LlistaPDI_E le);
LlistaPDI_E LLISTAPDI_E_vesInici(LlistaPDI_E le);
LlistaPDI_E LLISTAPDI_E_avanca(LlistaPDI_E le);
int LLISTAPDI_E_fi(LlistaPDI_E le);
LlistaPDI_E LLISTAPDI_E_destrueix(LlistaPDI_E le);

#endif
