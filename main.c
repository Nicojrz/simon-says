#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

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
	int puntaje;
	
    clearScreen();
    setColor(10); //verd
    printf("========== COMIENZA EL JUEGO ==========\n\n");

    // poner logica
    printf("juegooo\n");

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