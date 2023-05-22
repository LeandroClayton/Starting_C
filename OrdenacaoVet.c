#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM 30


void printVet(int *v, int size){
    int i;
    for (i = 0; i < size; i++)
    {
        if (i < 9)
        {
            printf("Número 0%i: %i\n", i+1, v[i]);
        }
        else
        {
            printf("Número %i: %i\n", i+1, v[i]);
        }
    }
}

void ordenaVetInsert(int *v){
    int i, k, i2, aux;
    for (i = 0; i < TAM; i++)
    {
        k = i;
        for (i2 = i+1; i2 < TAM; i2++)
        {
            if (v[i2] > v[k])
            {
                k = i2;
            }
        }
        aux = v[i];
        v[i] = v[k];
        v[k] = aux;
    }
}

void preencherVet(int *v){
    int i, vt[TAM];

    srand(time(NULL));

    for (i = 0; i < TAM; i++)
    {
        vt[i] = (rand() % 90) + 10;
        v[i] = vt[i];
    }
    
}

void media(int *v){


    int i;
    double media = 0;

    for (i = 0; i < TAM; i++)
    {
        media = media + v[i];
    }
    
    media = media / TAM;

    printf("A média dos números é: %.2f\n", media);
}

void numRepetidos(int *v){

    int *rep, i, i2, i3, numRepet = 0;
    bool aux;

    for (i = 0; i < TAM; i++)
    {
        aux = false;
        for (i2 = i+1; i2 < TAM; i2++)
        {
            if (v[i] == v[i2])
            {
                
                if (numRepet == 0)
                {
                    numRepet++;
                    rep = (int*)malloc(numRepet * sizeof(int));
                    rep[numRepet-1] = v[i]; 
                }else{
                    for (i3 = 0; i3 <= numRepet; i3++)
                    {
                        if (v[i] == rep[i3])
                        {
                            aux = true;
                        }
                    }
                    
                    if (aux == false)
                    {
                        numRepet++;
                        rep = (int*)realloc(rep, numRepet * sizeof(int));
                        rep[numRepet-1] = v[i];
                    }
                    
                    
                }
                
                
            }
            
        }
    }

    if (numRepet == 0)
    {
        printf("Não foram registrados valores repetidos!\n");
    }else{

        printVet(rep, numRepet);
        free(rep);
    }
    
}

void decoracao(){

    for (int i = 0; i < 20; i++)
    {
        printf("-");
    }
    printf("\n");
}

void printNomeDosHomi(){

    decoracao();
    printf("Integrantes: Leandro Clayton Pivovarsky e Douglas Roque Machado\n");
    decoracao();
}

int main()
{
    int v[TAM];

    decoracao();
    printf("Vetor original: \n");
    decoracao();

    preencherVet(v);

    printVet(v, TAM);

    decoracao();
    printf("Vetor ordenado: \n");
    decoracao();

    ordenaVetInsert(v);

    printVet(v, TAM);

    decoracao();
    printf("Números repetidos: ");


    numRepetidos(v);

    decoracao();
    media(v);


    printNomeDosHomi();
    return 0;
}
