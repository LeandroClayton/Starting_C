#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define PEDRA 1
#define PAPEL 2
#define TESOURA 3

int main()
{
    int numUser, numComp, vitUser, vitComp;
    char condicao, jokenpo[3][50];

    strcpy(jokenpo[0], "Pedra");
    strcpy(jokenpo[1], "Papel");
    strcpy(jokenpo[2], "Tesoura");
    srand(time(NULL));

    numComp = (rand() % 3)+1 ;
    condicao = 's';
    vitComp = vitUser = 0;
    while ((condicao != 'N') && (condicao != 'n'))
    {
        printf("-----------------------------\n");
        printf("1 - Pedra\n");
        printf("2 - Papel\n");
        printf("3 - Tesoura\n");
        printf("-----------------------------\n");
        printf("Insira qual sera o número: ");
        scanf("%d", &numUser);
        fflush(stdin);
        while (numUser < 1 && numUser > 3)
        {
            printf("!!ERRO!!");
            
        }
        
        if (numUser == numComp)
        {
            printf("Player = %s\nComputador = %s", jokenpo[numUser-1], jokenpo[numComp-1]);
            printf("\n\n\t--Empate--");
        }
        else if ((numUser == PEDRA && numComp == PAPEL))
        {
            printf("Player = %s\nComputador = %s", jokenpo[numUser-1], jokenpo[numComp-1]);
            printf("\n\n\t--Vitória do Player!--");
            vitUser++;
        } else if (numUser == PAPEL && numComp == PEDRA)
        {
            printf("Player = %s\nComputador = %s", jokenpo[numUser-1], jokenpo[numComp-1]);
            printf("\n\n\t--Vitória do Player!--");
            vitUser++;
        } else if (numUser == TESOURA && numComp == PAPEL)
        {
            printf("Player = %s\nComputador = %s", jokenpo[numUser-1], jokenpo[numComp-1]);
            printf("\n\n\t--Vitória do Player!--");
            vitUser++;
        } else
        {
            printf("Player = %s\nComputador = %s", jokenpo[numUser-1], jokenpo[numComp-1]);
            printf("\n\n\t--Vitória do Computador!--");
            vitComp++;
        }
        printf("\n\nDeseja jogar novamente?(s/n)\n");
        scanf("%c", &condicao);
        fflush(stdin);

        while (condicao != 's' && condicao != 'S' && condicao != 'n' && condicao != 'N')
        {
            printf("Input incorreta, insira novamente: ");
            scanf("%c", &condicao);
            fflush(stdin);
        }
        
    }

    if (vitUser > vitComp)
    {
        printf("O usuário ganhou mais partidas quando comparado com o Computador");
        printf("\nQuantidade de vitórias do computador %d\nQuantidade de vitórias do usuário: %d", vitUser, vitComp);
    } else if (vitComp == vitUser)
    {
        printf("Os 2 jogadores empataram!");
    } else
    {
        printf("O computador ganho mais partidas quando comparado ao computador");
        printf("\nQuantidade de vitórias do computador %d\nQuantidade de vitórias do usuário: %d", vitUser, vitComp);
    }

    
    return 0;
}
