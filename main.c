#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
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
    jugador[strcspn(jugador, "\n")] = '\0';

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
    printf("1. Ver historial de jugadas\n");
    printf("2. Jugar\n");
    printf("3. Instrucciones\n");
    printf("4. Salir\n\n");
    setColor(15);  //blanco
    printf("Selecciona una opcion: ");
}

void verHistorial()
{
    FILE *archivo;
    char linea[200];

    clearScreen();
    setColor(9);//az claro
    printf("========== HISTORIAL DE JUGADAS ==========\n\n");

    archivo = fopen("historial.txt", "r");
    if (archivo == NULL)
	{
        printf("No hay historial disponible.\n");
    }
	else
	{
        while (fgets(linea, sizeof(linea), archivo))
		{
            printf("%s", linea);
        }
        fclose(archivo);
    }

    printf("\n");
    system("pause");
}

void jugar()
{
    node *secuencia = NULL; // Cola de la secuencia generada
    node *respuesta = NULL; // Cola de la respuesta del jugador
    int nivel = 1;
    int color, correcto = 1;
    int puntaje = 0;

    srand(time(NULL)); // Inicializar aleatorio

    clearScreen();
    setColor(10); // verde
    printf("========== COMIENZA EL JUEGO ==========\n\n");

    create_dqueue(&secuencia);
    create_dqueue(&respuesta);

    while (correcto)
    {
        // Agregar nuevo color aleatorio a la secuencia
        color = rand() % 4 + 1; // 1-ROJO, 2-VERDE, 3-AZUL, 4-AMARILLO
        enqueue_dqueue(&secuencia, color);

        clearScreen();
        setColor(14); // amarillo
        printf("Nivel %d\n", nivel);
        printf("Memoriza la secuencia:\n");

        // Mostrar cada color uno por uno con su color real
        node *aux = NULL;
        create_dqueue(&aux);

        while (!isEmpty_dqueue(secuencia))
        {
            int c = dequeue_dqueue(&secuencia);

            clearScreen();
            setColor(15);
            printf("Nivel %d\n\n", nivel);

            // Mostrar el color con su color real
            switch (c)
            {
                case 1:
                    setColor(12); // Rojo
                    printf("  ROJO  \n");
                    break;
                case 2:
                    setColor(10); // Verde
                    printf("  VERDE  \n");
                    break;
                case 3:
                    setColor(11); // Azul/Cyan
                    printf("  AZUL  \n");
                    break;
                case 4:
                    setColor(14); // Amarillo
                    printf("  AMARILLO  \n");
                    break;
            }

            Sleep(2000); // Mostrar 1 segundo
            clearScreen(); // Limpiar para mostrar el siguiente

            enqueue_dqueue(&aux, c); // Guardar para recuperar
        }

        // Recuperar la secuencia para el siguiente nivel
        while (!isEmpty_dqueue(aux))
        {
            int c = dequeue_dqueue(&aux);
            enqueue_dqueue(&secuencia, c);
        }

        // Leer respuesta del usuario
        setColor(15);
        printf("Introduce la secuencia de colores separada por espacios:\n");
        printf("(1: ");
        setColor(12); // Rojo
        printf("ROJO ");
        setColor(15); // Blanco
        printf(", 2: ");
        setColor(10); // Verde
        printf("VERDE ");
        setColor(15); // Blanco
        printf(", 3: ");
        setColor(11); // Azul
        printf("AZUL ");
        setColor(15); // Blanco
        printf(", 4: ");
        setColor(14); // Amarillo
        printf("AMARILLO");
        setColor(15); // Blanco
        printf(")\n");
        
   

        delete_dqueue(&respuesta); // Limpiar respuesta anterior

        for (int i = 0; i < nivel; i++)
        {
            int c;
            scanf("%d", &c);
            enqueue_dqueue(&respuesta, c);
        }

        // Comparar secuencia y respuesta
        node *auxSec = NULL;
        node *auxResp = NULL;

        create_dqueue(&auxSec);
        create_dqueue(&auxResp);

        while (!isEmpty_dqueue(secuencia) && !isEmpty_dqueue(respuesta))
        {
            int s = dequeue_dqueue(&secuencia);
            int r = dequeue_dqueue(&respuesta);

            enqueue_dqueue(&auxSec, s);
            enqueue_dqueue(&auxResp, r);

            if (s != r)
            {
                correcto = 0;
                break;
            }
        }

        // Recuperar secuencia para el siguiente nivel
        while (!isEmpty_dqueue(auxSec))
        {
            int c = dequeue_dqueue(&auxSec);
            enqueue_dqueue(&secuencia, c);
        }

        if (correcto)
        {
            puntaje = nivel;
            nivel++;
            setColor(10); // verde
            printf("\n¡Correcto! Pasas al siguiente nivel.\n");
            Sleep(1000);
        }
        else
        {
            setColor(12); // rojo
            printf("\n¡Incorrecto! Fin del juego.\n");
            printf("Tu puntaje final es: %d\n", puntaje);
        }
    }
    // prueba historial
    FILE *archivo = fopen("historial.txt", "a");
    if (archivo != NULL)
	{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(archivo, "Jugador: %s | Fecha: %02d-%02d-%d | Puntaje: %d\n",
                jugador, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, puntaje); //cambiar puntaje
        fclose(archivo);
    }

    system("pause");
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