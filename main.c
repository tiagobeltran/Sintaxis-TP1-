#include <string.h>
#include <stdio.h>

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

// Prodecimiento para ingresar una gramatica formal
void ingresarGramatica(struct Gramatica *G)
{
    printf("Ingrese los símbolos no terminales: ");
    scanf("%s", G -> noTerminales);

    printf("Ingrese los símbolos terminales: ");
    scanf("%s", G -> Terminales);

    printf("Ingrese las producciones en la forma S->aX (use '#' para representar epsilon):\n");
    printf("Ingrese 'fin' para finalizar.\n");

    G->cant_producciones = 1;
    while(1)
    {
        printf ("Produccion: %d",G->cant_producciones);
        char prod[long];
        scanf("%s",prod);
        if (strcmp(prod,"fin") == 0 )
            break;

        // Buscar la posición del "->"
        char *flecha = strstr(prod, "->");
        if (flecha == NULL) {
            printf("Error: La producción debe contener '->'. Intenta de nuevo.\n");
            continue;
        }

        // Calcular la longitud del lado izquierdo (no terminal)
        int longIzq = flecha - prod;

        if (longIzq <= 0) {
            printf("Error: El lado izquierdo está vacío. Intenta de nuevo.\n");
            continue;
        }

        // Guardar el lado izquierdo
        strcpy(G->producciones[G->cant_producciones].noTerminal, prod);

        // Guardar el lado derecho (lo que está después de "->")
        strcpy(G->producciones[G->cant_producciones].produccion, flecha + 2);

        G->cant_producciones++;
    }

    return;
}



int main()
{
    struct Gramatica G;
    ingresarGramatica (&G);

    


    return 0;
}