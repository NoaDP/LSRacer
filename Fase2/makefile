all: Practica3
Logica.o: Logica.c Logica.h LlistaPDI.h Cua.h
		gcc -c Logica.c -Wall -Wextra
main.o: main.c Logica.h LlistaPDI.h Cua.h
		gcc -c main.c -Wall -Wextra 
LlistaPDI.o: LlistaPDI.c LlistaPDI.h
		gcc -c LlistaPDI.c -Wall -Wextra
Cua.o: Cua.c Cua.h
		gcc -c Cua.c -Wall -Wextra
Practica3: Cua.o LlistaPDI.o main.o Logica.o 
		   gcc main.o Logica.o LlistaPDI.o Cua.o -o P3 -Wall -Wextra 
clean: 
		rm -rf *.o P3
