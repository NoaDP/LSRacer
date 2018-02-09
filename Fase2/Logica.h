#ifndef _LOGICA_H_
#define _LOGICA_H_
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "LlistaPDI.h"
#include "Cua.h"

LlistaPDI_P extreuInfo(LlistaPDI_P lp, FILE *f, int *sortir);

LlistaPDI_C extreuCircuits(LlistaPDI_C lc, FILE *f_c, int *sortir);

LlistaPDI_P afegeixJugador(LlistaPDI_P lp, char nom_pilot[MAX], char nom_escuderia[MAX]);

LlistaPDI_P esborraPilot(LlistaPDI_P lp, char nom_pilot[MAX]);

LlistaPDI_C afegeixCircuit(LlistaPDI_C lc, char nom_cursa[MAX], float km, int punts);

LlistaPDI_C esborraCircuit(LlistaPDI_C lc, char nom_circuit[MAX]);

void mostraPilots(LlistaPDI_P lp);

void circuitsDisponibles(LlistaPDI_C lc, int *mal);

LlistaPDI_P circuitEscollit(LlistaPDI_C lc, char nom_circuit[MAX], LlistaPDI_P lp);

LlistaPDI_P ferCursa(Circuits c, LlistaPDI_P lp);

LlistaPDI_P substitueix(LlistaPDI_P lp, Pilots p);

LlistaPDI_E insereixEstadistica(LlistaPDI_E le, Estadistica e);

int PuntsMaximsPilots(LlistaPDI_P lp);

float KmMaximsPilots(LlistaPDI_P lp);

Cua circuitAuxiliar(char nom_circuit[MAX], Cua c, LlistaPDI_C lc);

LlistaPDI_P ferCampionat(Cua c, LlistaPDI_P lp);

LlistaPDI_P insereixPilot(LlistaPDI_P lp, FILE *f);

LlistaPDI_C insereixCircuit(LlistaPDI_C lc, FILE *f_c);

void printaEstadistiques(LlistaPDI_P lp, LlistaPDI_C lc);

void malluscules(char nom[MAX]);

#endif
