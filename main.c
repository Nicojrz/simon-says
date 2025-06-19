#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "dqueue.h"

//consts
#define MAX_NOMBRE 50
//vars
char jugador[MAX_NOMBRE];

//funciones menu
void setColor(int color);
void clearScreen();
void mostrarMenuPrincipal();
void verHistorial();
void jugar();
void instrucciones();

/*
	0-negro, 1-az osc, 2-verd osc, 3-aqua
	4-rojo osc, 5-purpura, 6-cafe, 7-gris claro
	8-gris-osc, 9-az claro, 10-verd claro, 11-cyan
	12-rojo, 13-rosa, 14-amarelo, 15-blanc
*/

//main
int main()
{
    int opcion;
    
    clearScreen();
    setColor(11); //cyan
    printf("===================================\n");
    printf("          JUEGO SIMON DICE         \n");
    printf("===================================\n\n");
    setColor(15); //blanco
    printf("Ingresa tu nombre: ");
	
	//input nombre
    fgets(jugador, MAX_NOMBRE, stdin);
    jugador[strcspn(jugador,"\n")] = '\0';

    do
	{
        mostrarMenuPrincipal();
        scanf("%d", &opcion);
        getchar();

        switch(opcion)
		{
            case 1:
                verHistorial();
                break;
            case 2:
                jugar();
                break;
            case 3:
                instrucciones();
                break;
            case 4:
                setColor(12);//rojo
                printf("\nHasta luego %s!\n", jugador);
                break;
            default:
                setColor(12);
                printf("\nOpcion invalida.\n");
                system("pause");
                break;
        }

    }
	while(opcion != 4);
	
	setColor(15);

    return 0;
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen()
{
    system("cls");
}

void mostrarMenuPrincipal()
{
    clearScreen();
    setColor(11);  //cyan
    printf("===================================\n");
    printf("          JUEGO SIMON DICE         \n");
    printf("===================================\n\n");
    setColor(14);  //amarillo
    printf("Bienvenido, %s!\n\n", jugador);
    printf("1. Historial\n");
    printf("2. Jugar\n");
    printf("3. Instrucciones\n");
    printf("4. Salir\n\n");
    setColor(15);  //blanco
    printf("Selecciona una opcion: ");
}

void instrucciones()
{
    clearScreen();
    setColor(13); //magenta
    printf("========== INSTRUCCIONES ==========\n\n");
    printf("El juego de Simon dice consiste en memorizar e indicar\n");
    printf("la serie de colores mostrados en cada nivel. Cada nivel\n");
    printf("agrega un nuevo color a la secuencia. El juego termina\n");
    printf("cuando se comete un error.\n\n");
    system("pause");
}

void verHistorial()
{
    FILE *archivo;
    char linea[200];

    clearScreen();
    setColor(9); // Azul claro
    printf("========== MEJOR PUNTAJE ==========\n\n");

    archivo = fopen("mejor_puntaje.txt", "r");
    if (archivo == NULL)
	{
        printf("No hay mejor puntaje registrado.\n");
    }
	else
	{
        while(fgets(linea, sizeof(linea), archivo))
		{
            printf("%s", linea);
        }
        fclose(archivo);
    }

    printf("\n========== HISTORIAL DE JUGADAS ==========\n\n");
    archivo = fopen("historial.txt", "r");
	
    if (archivo == NULL)
	{
        printf("No hay historial disponible.\n");
    }
	else
	{
        while(fgets(linea, sizeof(linea), archivo)) {
            printf("%s", linea);
        }
        fclose(archivo);
    }

    printf("\n");
    system("pause");
}


void jugar()
{
    node *secuencia = NULL; // Cola de la secuencia
    int nivel = 1;
    int color, correcto = 1;
    int puntaje = 0;

    srand(time(NULL));

    // Leer mejor puntaje oficial desde mejor_puntaje.txt
    int mejorPuntaje = 0;
    char mejorJugador[MAX_NOMBRE] = "";
    FILE *archivo = fopen("mejor_puntaje.txt", "r");
    if(archivo != NULL)
	{
        char linea[200];
        while(fgets(linea, sizeof(linea), archivo))
		{
            int p = 0;
            if(sscanf(linea, "Jugador: %[^ |]| Fecha: %*[^ |]| Puntaje: %d", mejorJugador, &p) == 2)	
			{
                mejorPuntaje = p;
            }
        }
        fclose(archivo);
    }

    clearScreen();
    setColor(10); // Verde
    printf("========== COMIENZA EL JUEGO ==========\n\n");
    printf("Mejor puntaje: %d por %s\n\n", mejorPuntaje, mejorJugador[0] ? mejorJugador : "no hay");

    create_dqueue(&secuencia);

    while(correcto)
    {
        // random color
        color = rand() % 4 + 1;
        enqueue_dqueue(&secuencia, color);

        clearScreen();
        setColor(14); // amarillo
        printf("Nivel %d | Mejor puntaje: %d (%s)\n\n", nivel, mejorPuntaje, mejorJugador[0] ? mejorJugador : "no hay");
        printf("Memoriza la secuencia:\n");

        // imprimir secuencia
        node *aux = NULL;
        create_dqueue(&aux);

        while(!isEmpty_dqueue(secuencia))
        {
            int c = dequeue_dqueue(&secuencia);

            clearScreen();
            setColor(15);
            printf("Nivel %d\n", nivel);
            printf("Mejor puntaje: %d (%s)\n\n", mejorPuntaje, mejorJugador[0] ? mejorJugador : "no hay");

            switch(c)
            {
                case 1:
					setColor(12);
					printf("  ROJO  \n");
					break;
                case 2:
					setColor(10);
					printf("  VERDE  \n");
					break;
                case 3:
					setColor(11);
					printf("  AZUL  \n");
					break;
                case 4:
					setColor(14);
					printf("  AMARILLO  \n");
					break;
            }

            Sleep(800);
            clearScreen();
            Sleep(200);

            enqueue_dqueue(&aux, c);
        }

        // restaurar secuencia
        while (!isEmpty_dqueue(aux))
        {
            int c = dequeue_dqueue(&aux);
            enqueue_dqueue(&secuencia, c);
        }

        // pedir respuesta
        setColor(15);
        printf("Repite la secuencia presionando teclas:\n");
        printf("1: "); setColor(12); printf("ROJO  "); setColor(15);
        printf("2: "); setColor(10); printf("VERDE  "); setColor(15);
        printf("3: "); setColor(11); printf("AZUL  "); setColor(15);
        printf("4: "); setColor(14); printf("AMARILLO\n\n");
        setColor(15);

        node *auxSec = NULL;
        create_dqueue(&auxSec);

        for(int i = 0; i < nivel; i++)
        {
            int esperado = dequeue_dqueue(&secuencia);
            enqueue_dqueue(&auxSec, esperado);

            char tecla = getch();
            int c = tecla - '0';

            // mostrar feedback
            switch (c)
			{
                case 1:
					setColor(12);
					printf("ROJO ");
					break;
                case 2:
					setColor(10);
					printf("VERDE ");
					break;
                case 3:
					setColor(11);
					printf("AZUL ");
					break;
                case 4:
					setColor(14);
					printf("AMARILLO ");
					break;
                default:
					setColor(12);
					printf("?? ");
					break;
            }
            setColor(15);

            if(c != esperado)
			{
                correcto = 0;
                break;
            }
        }
        printf("\n");

        // restaurar secuencia
        while(!isEmpty_dqueue(auxSec))
		{
            int c = dequeue_dqueue(&auxSec);
            enqueue_dqueue(&secuencia, c);
        }

        if(correcto)
		{
            puntaje = nivel;
            nivel++;
            setColor(10); // verde
            printf("\nCorrecto Pasas al siguiente nivel.\n");
            Sleep(1000);
        }
		else
		{
            setColor(12); // rojo
            printf("\nIncorrecto Fin del juego.\n");
            printf("Tu puntaje final es: %d\n", puntaje);
			
            if (puntaje > mejorPuntaje)
			{
                printf("Nuevo mejor puntaje!\n");
				
                // cambiar puntaje
                archivo = fopen("mejor_puntaje.txt", "w");
				
                if (archivo != NULL)
				{
					//obtener tiempo local
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
					//file printf
                    fprintf(archivo, "Jugador: %s | Fecha: %02d-%02d-%d | Puntaje: %d\n",
                            jugador, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, puntaje);
                    fclose(archivo);
                }
            }
        }
    }

    // guardar historial
    archivo = fopen("historial.txt", "a");
    if (archivo != NULL)
	{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(archivo, "Jugador: %s | Fecha: %02d-%02d-%d | Puntaje: %d\n",
                jugador, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, puntaje);
        fclose(archivo);
    }

    system("pause");
}