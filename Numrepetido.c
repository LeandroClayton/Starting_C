#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VET 5
int main()
{
    int vetor[MAX_VET], aux, i, i2, cont = 0, aux2 = 0;
    srand(time(NULL));
    printf("Vetor: ");
    for (i = 0; i < MAX_VET; i++){
        vetor[i] = (rand() % 9) + 1;
        printf("%d ", vetor[i]);
    }
    printf("\n");
    for (i = 0; i < MAX_VET; i++){
        cont = 1;
        aux2 = 0;
        for (i2 = i + 1; i2 < MAX_VET; i2++)
        {
            if ((vetor[i] == vetor[i2]) && (vetor[i] != 0))
            {
                aux = vetor[i];
                cont++;
                vetor[i2] = 0;
                if (aux2 != 1){
                    aux2 = 1;
                    printf("%d: ", aux);
                }
                
                
            }
        }
        if (cont != 1)
            printf("Número %d Ocorrências\n", cont);
    }
    
    return 0;
}
