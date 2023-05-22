/*

Enunciado
Faça um algoritmo que gere uma matriz aleatória e depois identifique o maior número a cima,
o maior número abaixo e o maior número na diagonal

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_MAX 5

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
int main()
{
    int i, i2, matriz[TAM_MAX][TAM_MAX], maior_acima= 0, maior_abaixo = 0, maior_diagonal = 0, aux, aux2;
    srand(time(NULL));

    for (i = 0; i < TAM_MAX; i++)
    {
        for (i2 = 0; i2 < TAM_MAX; i2++)
        {
            matriz[i][i2]  = (rand() % 40) + 10;
            if ((maior_acima <= matriz[i][i2]) && (i != i2))
            {
                maior_acima = matriz[i][i2]; 
                aux = i;
                aux2 = i2;
            } else if ((i == i2) && (maior_diagonal < matriz[i][i2]))
                maior_diagonal = matriz[i][i2];         
        }
    }
    
    if(aux2 == 4){
        aux++;
        aux2 = -1;
    }      
        
    for (i = aux; i < TAM_MAX; i++)
    {
        for (i2 = aux2 + 1; i2 < TAM_MAX; i2++)
        {
            if ((maior_abaixo < matriz[i][i2]) && (i != i2)){
                maior_abaixo = matriz[i][i2];  

            }
        }
    }
    
    for (i = 0; i < TAM_MAX; i++)
    {
        for (i2 = 0; i2 < TAM_MAX; i2++)
        {
            
            if ((matriz[i][i2] == maior_acima) && (i != i2))
                printf(GRN " %d " WHT,matriz[i][i2]);
            else if ((matriz[i][i2] == maior_diagonal) && ( i == i2))
                printf(YEL " %d " WHT,matriz[i][i2]);
            else if ((matriz[i][i2] == maior_abaixo) && (i >= aux) && (i2 > aux2) && (i != i2))
                printf(MAG " %d " WHT,matriz[i][i2]);
            else
                printf(" %d ", matriz[i][i2]);
        }
            printf("\n");
        }
        
    
    
    return 0;
    

}
