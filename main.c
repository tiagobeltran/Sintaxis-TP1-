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
    printf("Ingrese los símbolos no terminales separados por un espacio: ");
    scanf(" %[^\n]", G -> noTerminales);

    printf("Ingrese los símbolos terminales separados por un espacio: ");
    scanf(" %[^\n]", G -> Terminales);

    printf("Ingrese las producciones en el formato A->BC (separadas por ;):\n");
    printf("Ingrese fin para finalizar.\n");

    char aux[long];
    G->cant_producciones = 0;
    while (1)
    {
        printf("Produccion %d: ",G->cant_producciones + 1);
        scanf(" %[^\n]",aux);

        if (strcmp(aux,"fin") == 0)
            break;

        // Validar formato: A->x (mínimo 4 caracteres: A->x)
        if (strlen(aux) < 4 || aux[1] != '-' || aux[2] != '>') 
        {
            printf("Formato inválido. Use A->x\n");
        continue;
        }

        G->producciones[G->cant_producciones].noTerminal = aux[0];
        strcpy(G->producciones[G->cant_producciones].produccion  , aux + 3);
        G->cant_producciones ++;
    }
    
    printf("Ingrese el axioma (noTerminal inicial): ");
    scanf(" %c",G->axioma);

    return;
}

void MostrarGramatica(struct Gramatica *G)
{
    printf("\n --- GRAMATICA INGRESADA --- \n");

    printf("Vocabulario no Terminal: ");
    for (int i=0 ; G->noTerminales[i] != '\0' ; i++)
    {
        printf("%c" , G->noTerminales[i]);
    }

    printf("\n");

    printf("Vocabulario Terminal: ");
    for (int i=0 ; G->Terminales[i] != '\0' ; i++)
    {
        printf("%c" , G->Terminales[i]);
    }

    printf("\n");

    printf("Producciones: ");
    for (int i=0 ; i < G->cant_producciones ; i++)
    {
        printf(" %c -> %s \n" , G->producciones[i].noTerminal,G->producciones[i].produccion);
    }

    printf("\n");

    printf("Axioma: %c",G->axioma);
    
    return;
}

int main()
{
    struct Gramatica G;
    ingresarGramatica (&G);
    MostrarGramatica (&G);



    return 0;
}