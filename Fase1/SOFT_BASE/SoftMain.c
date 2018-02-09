//
//-------------------------PROGRAMA DE TEST DE l'LSMAKER--------------------
//
// Aquest és el programa que porta carregat "de fàbrica" l'LSMaker.
// Només fa que moure els motors endavant i endarrera i enviar una
// trama per l'enllaç de radiofreqüencia. Per la pantalla de l'LCD
// mostra la tensió de la bateria, l'adreça mac, el nom d'usuari 
// que hagis configurat amb el programa LSLoader, la inclinació XYZ i
// el valor dels senyals STOP0, STOP1 i STOP2 (Blanc o Negre)
//
// Per crear la teva propia aplicació, només cal que baixis el directori
// LS_API i el directori Proves i ja pots engegar el MPLAB i obrir el projecte
// TestMain. El projecte ja te tots els tads i l'API ben configurada, només
// cal que afegeixis els teus propis TADS i la teva aplicació en lloc de 
// la "ProvaDeCalibracio"
// 

//------------------------------LLIBRERIES-------------------------
#include "../LS_API/LSApi.h"
#include <stdio.h>
//-------------------------END--LLIBRERIES-------------------------

//------------------------------CONSTANTS--------------------------
// Opcions de configuració del microprocessador PIC16F64
_CONFIG2(OSCIOFNC_ON);
_CONFIG1(JTAGEN_OFF & ICS_PGx1);
#define MAX 100
//-------------------------END--CONSTANTS--------------------------

//------------------------------TIPUS------------------------------
//-------------------------END--TIPUS------------------------------
//generem una funcio que ens generi una cadena de caracters de la linia del fitxer que llegeix
int LS_NVOL_ReadLine (int HANDLE, char *buffer){
    int i = 0;
    char aux[5];
    for ( i = 0; buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '\r'; i++ ) buffer[i] = '\0';
    i = 0;
    while (LS_NVOL_Read(HANDLE,aux,1) != EOF){
        if(aux[0] == '\n'){
            buffer[i] = '\0';
            return i;
        }else{
            buffer[i] = aux[0];
            i++;
        }
    }
    buffer[i] = '\0';
    return EOF;
}
// inicialitza el robot
void inicialitza() {
    LS_Init();
}
// generem una funcio atoi per convertir caracters a enters
int atoi (char *cadena, int *index){
    int num = 0;
    int negatiu = 0;
    if(cadena[*index] == '-'){
        negatiu = 1;
    }
    while (cadena[*index] != '\0' && cadena[*index] != '/' && cadena[*index] != '\r'){
        if(cadena[*index] >= '0' && cadena[*index] <= '9'){
            num = num*10 + (cadena[*index] - '0');
        }
        LS_Executiu();
        (*index)++;
    }
    // en cas de que sigui negatiu el multiplicarem per menys 1
    if (negatiu){
        num = num * -1;
    }
    return num;
}
// comencem a tractar el fitxer per generar les comandes
void LlegeixFitxer (){
    int f = -1;
    char cadena[MAX];

    int i = 0;
    int x = 0;
    int y = 0;
    int velocitat = 0;
    int angle = 0;
    unsigned int temps = 0;
    char caracter = ' ';
    int stop = 0;
    int error = 1;
    int aux = 0;

    // obrim el fitxer de text
    f = LS_NVOL_Open(NVOL_STREAM_A, "r");

    // comencem la lectura
    while (LS_NVOL_ReadLine(f,cadena) != EOF){

        i = 0;
        x = atoi(cadena, &i);
        if (cadena[i] == '/') i++;
        y = atoi (cadena, &i);
        if (cadena[i] == '/') i++;

        LS_LCD_Clear();
        // situem el text en les coordenades x i y
        LS_LCD_GotoXY(x,y);
        
        //comprovem que el missatge es troba dins les coordenades valides
        if ((x<0)|| (x>15) || (y<0) || (y>3)){
            error = 1;
        }
        
        while (cadena[i] != '/' && cadena[i] != '\0' && (x>=0) && (x<=15) && (y>=0) && (y<=3)){
            LS_LCD_Printf(x,y,"%c",cadena[i]);
            x++;
            i++;
            error = 0;
            LS_Executiu();
        }
        

        LS_SYS_SleepMiliSecs(2000);

        if (LS_NVOL_ReadLine(f,cadena) != EOF){
            i = 0;
            caracter = cadena[i];
            i = i + 2;
            if (error != 1){
                // segons la lletra efectuara una comanda o altra
                switch (caracter){
                    // en cas de que sigui F es moura en linia recta
                    case 'F':
                        temps = atoi(cadena, &i);
                        i++;
                        velocitat = atoi (cadena, &i);
                        if((velocitat<(-100)) || (velocitat > 100)){
                             LS_LCD_Clear();
                             LS_LCD_Printf(0,0, "%s", "Error! La velocitat se surt dels parametres");
                             // s'espera 3 segons
                             LS_SYS_SleepMiliSecs(3000);
                        }else{
                            LS_MT_Lineal(temps, velocitat, 0, &stop);
                        }
                        break;
                    // en cas que sigui R es moura cap a la dreta
                    case 'R':
                        angle = atoi(cadena,&i);
                        i++;
                        velocitat = atoi (cadena, &i);
                        if (cadena[i]== '/') i++;
                        temps = LS_MT_GetTimeFromAngle(angle, velocitat);
                        LS_MT_TurnRight(temps,velocitat,0,0,&stop);
                        break;
                    // en cas de que sigui L es moura cap a la esquerra
                    case 'L':
                        angle = atoi (cadena, &i);
                        if (cadena[i] == '/') i++;
                        velocitat = atoi (cadena, &i);
                        if (cadena[i] == '/') i++;
                        temps =  LS_MT_GetTimeFromAngle( angle, velocitat);
                        LS_MT_TurnLeft(temps, velocitat,0,0,&stop);
                        break;
                    // en cas de que no es tracti de cap de les lletres anteriors donara error
                    default:
                        LS_LCD_Clear();
                        LS_LCD_Printf(0,0,"%s", "Error a la comanda");
                        LS_SYS_SleepMiliSecs(5000);
                        break;
                }
            
                // tanquem el switch
            }else{
                // si abans ens ha retornat error, retornara un missatge d'error
                LS_LCD_Clear();
                LS_LCD_Printf(0,0, "%s", "Error a la comanda");
                // s'espera 5 segons
                LS_SYS_SleepMiliSecs(5000);
            }// tanquem el if
        }//tanquem el segon while
        LS_SYS_SleepMiliSecs(2000);
        LS_Executiu();
    }
    // tanquem el fitxer un cop ha arribat al final
    LS_NVOL_Close(f);
}

int main(void) {
    
    inicialitza();
    LS_LCD_Clear();
    LS_LCD_Printf(2,2,"%s","Preparats!");

    while (1) {
        // fins que l'usuari no premi el GPButton, l'LS Maker no es moura
        if (LS_IO_GpButtonPress() == 1){
            LlegeixFitxer();
            // apaguem l'LS MAKEr
            LS_SYS_PowerOff();
         }
    LS_Executiu();
    }
    return 0;
}
