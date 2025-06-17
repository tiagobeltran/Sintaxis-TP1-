#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define long 100


// Estructura para almacenar las producciones
struct Produccion
{
    char noTerminal;
    char produccion[long];
};

// Estructura para almacenar las gramaticas
struct Gramatica
{
    char noTerminales[long];
    char Terminales[long];
    struct Produccion producciones[long];
    char axioma;
    int cant_producciones;
};

// Devuelve el primer no terminal en una cadena de derivacion
char buscarNoTerminal(char *cadena, struct Gramatica *G) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        for (int j = 0; G->noTerminales[j] != '\0'; j++) {
            if (cadena[i] == G->noTerminales[j])
                return cadena[i];
        }
    }
    return '\0';
}

// Proceso de derivación
void derivarGramatica (struct Gramatica *G)
{
    char cadena[2048] = "";
    cadena[0] = G->axioma;
    cadena[1] = '\0';

    srand(time(NULL));
    
    char NTActual;
     while ((NTActual = buscarNoTerminal(cadena, G)) != '\0') {
        int indices[long];
        int count = 0;
        // Buscar producciones aplicables al NTActual
        for (int i = 0; i < G->cant_producciones; i++) {
            if (G->producciones[i].noTerminal == NTActual) {
                indices[count++] = i;
            }
        }

        if (count == 0) break;

        int elegida = indices[rand() % count];
        char *reemplazo = G->producciones[elegida].produccion;

        int pos;
        for (int i = 0; cadena[i] != '\0'; i++) {
            if (cadena[i] == NTActual) {
                pos = i;
                break;
            }
        }

        char nuevaCadena[2048] = "";
        strncat(nuevaCadena, cadena, pos);     // Copia parte antes del no terminal
        strcat(nuevaCadena, reemplazo);        // Copia la producción (reemplazo)
        strcat(nuevaCadena, cadena + pos + 1); // Copia el resto después del no terminal

        strcpy(cadena, nuevaCadena);
    }

    printf("Palabra generada: %s\n", cadena);
}

// Función para validar si una producción es regular
int esProduccionRegular(char *ladoDerecho)
{
    int len = strlen(ladoDerecho);

    if (len == 0) return 1; // ε (cadena vacía), se acepta

    if (len == 1)
    {
        return islower(ladoDerecho[0]); // Solo un terminal
    }
    else if (len == 2)
    {
        return islower(ladoDerecho[0]) && isupper(ladoDerecho[1]) ; // terminal + no terminal 
    }
    

    return 0; // Más largo que 2 => no regular
}

int esGramaticaRegular(struct Gramatica *G)
{
    for (int i=0 ; i < G->cant_producciones ; i++)
    {
        if (esProduccionRegular(G->producciones[i].produccion) == 0)
            return 0;
    }
    return 1;
}

// Elimina espacios de Terminales y noTerminales
void limpiarEspacios(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] != ' ') {
            dest[j++] = src[i];
        }
    }
    dest[j] = '\0';
}

// Prodecimiento para ingresar una gramatica formal
void ingresarGramatica(struct Gramatica *G)
{
    char aux[long];

    printf("Ingrese los simbolos no terminales separados por un espacio: ");
    scanf(" %[^\n]", aux);
    limpiarEspacios(G->noTerminales, aux);

    printf("Ingrese los simbolos terminales separados por un espacio: ");
    scanf(" %[^\n]", aux);
    limpiarEspacios(G->Terminales, aux);
    
    printf("Ingrese las producciones en el formato S->xT :\n");
    printf("Ingrese fin para finalizar.\n");

    G->cant_producciones = 0;
    while (1)
    {
        printf("Produccion %d: ",G->cant_producciones + 1);
        scanf(" %[^\n]",aux);

        if (strcmp(aux,"fin") == 0)
            break;

        G->producciones[G->cant_producciones].noTerminal = aux[0];
        strcpy(G->producciones[G->cant_producciones].produccion  , aux + 3);
        G->cant_producciones ++;
    }
    
    printf("Ingrese el axioma (noTerminal inicial): ");
    scanf(" %c",&G->axioma);


    return;
}

void MostrarGramatica(struct Gramatica *G)
{
    printf("\n --- GRAMATICA INGRESADA --- \n");

    printf("Vocabulario no Terminal: ");
    for (int i=0 ; G->noTerminales[i] != '\0' ; i++)
    {
        printf("%c" , G->noTerminales[i]);
        if (G->noTerminales[i + 1] != '\0') // si no es el último
            printf(", ");
    }

    printf("\n");

    printf("Vocabulario Terminal: ");
    for (int i=0 ; G->Terminales[i] != '\0' ; i++)
    {
        printf("%c" , G->Terminales[i]);
        if (G->Terminales[i + 1] != '\0') // si no es el último
            printf(", ");
    }

    printf("\n");

    printf("Producciones: \n");
    for (int i=0 ; i < G->cant_producciones ; i++)
    {
        printf(" %c -> %s \n" , G->producciones[i].noTerminal,G->producciones[i].produccion);
    }

    printf("\n");

    printf("Axioma: %c",G->axioma); printf("\n");

    return;
}

int main()
{
    struct Gramatica G;
    ingresarGramatica (&G);
    MostrarGramatica (&G);

    if (esGramaticaRegular(&G) == 0)
    {
        printf("La Gramatica ingresada no es regular, intente nuevamente. \n");
        ingresarGramatica (&G);
    }
    else
        printf("La Gramatica ingresada es regular.\n");

    derivarGramatica (&G);
    return 0;
}
