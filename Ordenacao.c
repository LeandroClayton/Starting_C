#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VET 5
int main()
{
    int matriz[MAX_VET][MAX_VET], i, i2, i3, i4, aux;
    srand(time(NULL));

    printf("A matriz aleatória gerada é: \n");
    for (i = 0; i < MAX_VET; i++){
        for (i2 = 0; i2 < MAX_VET; i2++){
            matriz[i][i2] = (rand() % 40) + 10;
            printf("%d ", matriz[i][i2]);
        }
        printf("\n");
    }

    printf("\n\n\n");
    for (i = 0; i < MAX_VET; i++)
    {
        for (i2 = 0; i2 < MAX_VET; i2++)
        {
            for (i3 = i; i3 < MAX_VET; i3++)
            {
                for (i4 = i2; i4 < MAX_VET; i4++)
                {
                    if (matriz[i][i2] < matriz[i3][i4])
                    {
                        aux = matriz[i][i2];
                        matriz[i][i2] = matriz[i3][i4];
                        matriz[i3][i4] = aux;
                    }
                    
                }
                
            }
        
        }
    }
    
    
    for (i = 0; i < MAX_VET; i++){
        for (i2 = 0; i2 < MAX_VET; i2++){
            printf("%d ", matriz[i][i2]);
        }
        printf("\n");
    }
    

    return 0;
}
