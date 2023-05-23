#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

//structs

typedef struct 
{
    char *titulo;
    char **autores;
    int numAutores;
    char *editora;
    int num_pag;
    int ano;
    char *idioma;
    int num_genero;
    char **genero;
}Livro;


//variável global

int num_livros = 0;
Livro *biblioteca;

//Funções com propósito de decoração/ printar menus
void limparBuffer();
void decoracao(char a);                 // função que decora o menu
void menuPrincipal();                   // Printa o menu principal
void menuListar();                      // Printa o menu da listagem
void menuEditar();                      // Printa o menu para editar livros
void subMenus(int o);                   // 1 para printar a função de editar autor e 2 para printar a tela de editar Genero
void menus();                           // Lança os outros menus e funções

//Funções principais
void incluirLivros();                   // Cria um livro completo e novo
int validarAno(int n);                  // Verifica se o ano inserido é correto
int validarPag(int m);                  // Verifica se a página não é 0 ou > 0
char* validarStr(char *a);              // Valida se não foi inserido uma string em branco
void msgErro(int e);                    // Printa msg de erro
void alocarMemoria(Livro n);            // Aloca memória no caso de livro add ou excluido 
void listarLivros(int a);               // Lista os livros adicionados
void mostrarLivro(int a);     // Lista um livro e todas os seus atributos 
void listarTitulos();                   // Lista o título de todos os livros
void listarAutores(Livro b);            //Lista todos os autores presentes na criação dor arquivo
void excluirLivro();                    // Exclui livros
void editarLivro();                     // Função de editar um livro                     
void realocarMemoria(char *a, char *b); // Realoca memória de duas strings
int validarOpcao(int a, int a2);        // valida opções inteiras(a = variável a ser validada, a2 = limite máximo que essa variável pode atingir)
void editarStr(char *a, char *o);       // Edita todas as estrings, podendo ser manipulável (a = string a ser editada, o = digitar o que será alterado no livro(editora, titulo, autor, etc.))
void deletarAutor(int indice);          // Deleta um autor até não ser mais possível
void listarGeneros(Livro b);            // Lista todos os gêneros do livrp
void deletarGenero(int indice);         // Deleta um gênero até não ser mais possível
void salvarTxt();
void limparTela();
char validarChar(char n);
void recuperarDados();

int main()
{
    recuperarDados();
    menus();
    salvarTxt();
    return 0;
}

void menus(){
    int opcao,opcao2;

    
    while (opcao != 5)
    {
        limparTela();
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        opcao = validarOpcao(opcao, 5);
        {
            switch (opcao)
            {
            case 1:
                incluirLivros();    
                break;
            case 2:
                if (num_livros == 0)
                {
                    limparTela();
                    msgErro(-2);
                    break;
                }
                editarLivro();
                break;

            case 3:
                if (num_livros == 0)
                {
                    limparTela();
                    msgErro(-2);
                    break;
                }
                excluirLivro();
            break;
            case 4:
                if (num_livros == 0)
                {
                    limparTela();
                    msgErro(-2);
                    break;
                }
                
                menuListar();
                scanf("%d", &opcao2);
                listarLivros(opcao2);
                limparBuffer();
                break;
            default:
                break;
            }
        }            
        }
        
        


}

void incluirLivros(){

    limparTela();
    num_livros++;
    char str[200], n;

    Livro var;
    var.numAutores = var.num_genero = 0;
    printf("-- Adicionando Livro --\n");
    //Adicionar título do livrp
    printf("Título do Livro: ");
    gets(str);
    limparBuffer();
    strcpy(str, validarStr(str));

    var.titulo = (char *) malloc ((strlen(str) + 1) * sizeof (char));
    strcpy(var.titulo, str);

    //Alocar e inserir o nome de todos os autores
    while (n != 'n'){
        var.numAutores++;
        if (var.numAutores == 1)
        {
            var.autores = (char **) malloc(var.numAutores * sizeof(char*));
        }
        else{
            var.autores = (char **) realloc(var.autores, var.numAutores * sizeof(char*));
        }

        printf("Nome do %d autor: ", var.numAutores);
        gets(str);
        limparBuffer();    
        strcpy(str, validarStr(str));

        var.autores[var.numAutores-1] = (char *) malloc((strlen(str)+1) * sizeof(char));
        strcpy(var.autores[var.numAutores-1], str);
        printf("Adicionar mais autores?(s/n)\n");
        n = getchar();
        limparBuffer(); 
        n = validarChar(n);
    }
    
    n = 's';

    //Adicionar nome da editora
    printf("Nome da editora: ");
    gets(str);
    limparBuffer();
    strcpy(str, validarStr(str));
    var.editora = (char *) malloc ((strlen(str) + 1) * sizeof (char));
    strcpy(var.editora, str);

    //Adicionar os idiomas disponíveis do Livro
    printf("Idioma: ");
    gets(str);
    limparBuffer();
    strcpy(str, validarStr(str));
    var.idioma = (char *) malloc ((strlen(str) + 1) * sizeof (char));
    strcpy(var.idioma, str);

    //Adicionar Gênero do Livro

    while (n != 'n'){
        var.num_genero++;
        if (var.num_genero == 1)
        {
            var.genero = (char **) malloc(var.num_genero * sizeof(char*));
        }
        else{
            var.genero = (char **) realloc(var.genero, var.num_genero * sizeof(char*));
        }

        printf("%dº gênero do Livro: ", var.num_genero);
        gets(str);
        limparBuffer();        
        strcpy(str, validarStr(str));

        var.genero[var.num_genero-1] = (char *) malloc((strlen(str)+1) * sizeof(char));
        strcpy(var.genero[var.num_genero-1], str);
        printf("Adicionar mais gêneros?(s/n)\n");
        n = getchar();
        limparBuffer();
        n = validarChar(n);
    }
    //Adicionar o Númro de páginas que há no livro

    printf("Número de páginas: ");
    scanf("%d", &var.num_pag);
    var.num_pag = validarPag(var.num_pag);
    limparBuffer();

    printf("Ano de lançamento do livro: ");
    scanf("%d", &var.ano);
    limparBuffer();

    var.ano = validarAno(var.ano);

    //Alocar/realocar espaço na biblioteca

    alocarMemoria(var);
    mostrarLivro(num_livros-1);
    printf("Livro %s Criado com sucesso!(enter para continuar)\n", var.titulo);
    getchar();
    limparBuffer();
}


void listarLivros(int a){

    limparTela();
    int op, i;
    char opcao;

    switch (a)
    {
    case 1:
        while ((opcao != 'n') && (opcao != 'N'))
        {
            // Númera os livros mostrando somente os títulos
            printf("Selecione o livro que você deseja listar por completo: \n");
            listarTitulos();
            
            scanf("%d", &op);
            fflush(stdin);
            while ((op > num_livros) || (op < 1))
            {
                msgErro(-3);
                scanf("%d", &op);
                limparBuffer();
                
            }
            op--;

            
            //Lista o Livro por completo de acordo com o Livro escolhido
            mostrarLivro(op);
            printf("Deseja listar mais algum livro?(s/n) ");
            scanf("%c", &opcao);
            limparBuffer();
            opcao = validarChar(opcao);
        }

        break;
    case 2:

        for (i = 0; i < num_livros; i++)
        {
            mostrarLivro(i);
        }
        limparBuffer();
        printf("\nAperte enter para voltar a tela principal\n");
        getchar();
        limparBuffer();
        
        break;
        default:
            break;
        } 


}




void excluirLivro(){

    int op, i;
    char opcao, aux[200], n;
    while (n != 'n' && n != 'N')
    {

        if (num_livros == 0)
        {
            msgErro(-8);
            getchar();
            return;
        }
        
        limparTela();
        printf("Qual dos Livros você deseja excluir? \n");
        listarTitulos();
        printf("(Digite 0 para voltar ao menu principal)\n");
        scanf("%d", &op);
        limparBuffer();
        
        if ((op == 0))
        {
            return;
        }
        
        if ((op > num_livros))
        {
            msgErro(-1);
            return;
        }
        op--;
        printf("Têm certeza que deseja excluir o livro \"%s\"? (s/n)", biblioteca[op].titulo);
        scanf("%c", &opcao);
        limparBuffer();
        opcao = validarChar(opcao);
        strcpy(aux, biblioteca[op].titulo);

        if ((opcao == 'n') || (opcao == 'N'))
        {
            limparTela();
            printf("Operação cancelada!(Aperte enter para voltar ao menu inicial)\n");
            getchar();
            return;
        }

        num_livros--;

        for (i = op; i < num_livros; i++)
        {
            biblioteca[i] = biblioteca[i+1];
        }
        biblioteca = (Livro *) realloc(biblioteca, num_livros * sizeof(Livro));
        
        printf("Livro \"%s\" excluído com sucesso!!!\nDeseja excluir mais algum Livro?(s/n)", aux);
        n = getchar();
        limparBuffer();
        n = validarChar(n);
    }

}


void editarLivro(){

int op,op2,op3,op4;
op = op2 = op3 = op4 = 1;
char opcao, str[100], n;
    
    
    while (op > 0) // Começa o looping para verificar se o usuário não deseja editar mais de 1 livro
    {
        limparTela();
        printf("\t-- Editar Livro --\n");
        printf("Qual dos livros você quer editar?\n");
        listarTitulos();
        printf("(Digite 0 para voltar ao menu principal)\n");
        scanf("%d", &op);
        limparBuffer();
        if (op == 0)
            return;
        

        while ((op > num_livros) || (op < 0)) // Valida o número de livros a partir da opção escolhida
        {
            msgErro(-3);
            scanf("%d", &op);
        }
        op--;

        limparTela();
        printf("O livro escolhido foi: \n");
        mostrarLivro(op);
        printf("Confimar livro selecionado para alteração?(s/n)\n");
        opcao = getchar();
        limparBuffer();
        opcao = validarChar(opcao);

        if ((opcao == 'n') || (opcao == 'N')) // Verifica se foi selecionado o livro correto
        {
            printf("Operação cancelada!!!\n");
        }
        else
        {

            while (opcao != 'n') // Opção caso o usuário queira editar mais coisa no livro selecionado
            {
                n = 's';
                limparTela();
                menuEditar();
                scanf("%d", &op2);
                limparBuffer();
                op2 = validarOpcao(op2, 8);

                switch (op2) // Switch para o primeiro menu
                {
                case 1: // Edita o título

                    printf("\n-- Editar Título --\n");
                    printf("Digite qual será o novo título: ");
                    editarStr(biblioteca[op].titulo,"Título");
                    printf("TÍTULO ALTERADO COM SUCESSO!!!!\nDeseja alterar mais algum item?(s/n)\n");
                    opcao = getchar();
                    limparBuffer();
                    opcao = validarChar(opcao);
                    break;
                    
                case 2: // Edita os autores
                    limparTela();
                    subMenus(1);
                    scanf("%d", &op3);
                    limparBuffer();
                    op3 = validarOpcao(op3,4);

                    switch (op3) // Switch para o submenu de Autor
                    {
                    case 1: // Adiciona mais autores
                        limparTela();
                        printf("\t -- Adicionar Autores --\n");
                        while (n != 'n'){
                            biblioteca[op].numAutores++;
                            biblioteca[op].autores = (char **) realloc(biblioteca[op].autores, biblioteca[op].numAutores * sizeof(char*));

                            printf("Nome do %d autor: ", biblioteca[op].numAutores);
                            gets(str);
                            limparBuffer();    
                            strcpy(str, validarStr(str));
                            biblioteca[op].autores[biblioteca[op].numAutores-1] = (char *) malloc((strlen(str)+1) * sizeof(char));
                            strcpy(biblioteca[op].autores[biblioteca[op].numAutores-1], str);
                            printf("Adicionar mais autores?(s/n)\n");
                            n = getchar();
                            limparBuffer(); 
                            n = validarChar(n);
                        }
                        printf("Deseja alterar mais algum item?(s/n)\n");
                        opcao = getchar();      
                        limparBuffer();
                        opcao = validarChar(opcao);
                        break;

                    case 2: // Editar um único autor
                        limparTela();
                        listarAutores(biblioteca[op]);
                        printf("Selecione qual autor você irá alterar:");
                        scanf("%d", &op4);
                        limparBuffer();
                        op4 = validarOpcao(op4, biblioteca->numAutores);
                        op4--;
                        printf("Digite o novo autor: ");
                        editarStr(biblioteca[op].autores[op4], "Autor");
                        opcao = getchar();
                        limparBuffer();
                        opcao = validarChar(opcao);
                        break;

                    case 3: // Excluir um único autor
                        limparTela();
                        if (biblioteca[op].numAutores == 1)
                        {
                            limparTela();
                            msgErro(-7);
                            getchar();
                            break;
                        } 
                        deletarAutor(op);
                        printf("Deseja alterar mais algum item?(s/n)\n");
                        opcao = getchar();
                        limparBuffer();
                        opcao = validarChar(opcao);
                        break;

                    default:
                        break;
                    }
                    break;
                case 3:
                    limparTela();
                    printf("\n-- Editar Editora --\n");
                    printf("Digite qual será a nova editora: ");
                    editarStr(biblioteca[op].editora, "Editora");
                    printf("EDITORA ALTERADO COM SUCESSO!!!!\ndeseja alterar mais algum item?(s/n)\n");
                    opcao = getchar();
                    limparBuffer();
                    opcao = validarChar(opcao);

                    break;
                case 4:
                    limparTela();
                    printf("\n-- Editar Ano de Edição --\n");
                    printf("Digite qual será o ano de edição: ");
                    scanf("%d", &biblioteca[op].ano);
                    limparBuffer();
                    validarAno(biblioteca[op].num_pag);
                    printf("ANO DE EDIÇÃO ALTERADO COM SUCESSO!!!!\ndeseja alterar mais algum item?(s/n)\n");
                    opcao = getchar();
                    limparBuffer();
                    opcao = validarChar(opcao);
                    break;
                
                case 5:
                    limparTela();
                    printf("\n-- Editar Número de Páginas --\n");
                    printf("Digite qual será o número de páginas: ");
                    scanf("%d", &biblioteca[op].num_pag);
                    limparBuffer();
                    validarPag(biblioteca[op].num_pag);
                    printf("NÚMERO DE PÁGINAS ALTERADO COM SUCESSO!!!!\ndeseja alterar mais algum item?(s/n)\n");
                    opcao = getchar();   
                    limparBuffer();
                    opcao = validarChar(opcao);
                    break;

                case 6:
                    limparTela();
                    printf("\n-- Editar Idioma --\n");
                    printf("Digite qual será o novo idioma: ");
                    editarStr(biblioteca[op].idioma, "Idioma");
                    printf("IDIOMA ALTERADO COM SUCESSO!!!!\ndeseja alterar mais algum item?(s/n)\n");
                    opcao = getchar();    
                    limparBuffer();
                    opcao = validarChar(opcao);
                    break;

                case 7:
                    limparTela();
                    subMenus(2);
                    scanf("%d", &op3);
                    limparBuffer();
                    op3 = validarOpcao(op3,4);

                    switch (op3) // Switch para o submenu de Autor
                    {
                    case 1: // Adiciona mais autores
                        limparTela();
                        printf("\t -- Adicionar gênero --\n");
                        while (n != 'n'){ 
                            biblioteca[op].num_genero++;
                            biblioteca[op].genero = (char **) realloc(biblioteca[op].genero, biblioteca[op].num_genero * sizeof(char*));

                            printf("Nome do %d gênero: ", biblioteca[op].num_genero);
                            gets(str);
                            limparBuffer();    
                            strcpy(str, validarStr(str));
                            biblioteca[op].genero[biblioteca[op].num_genero-1] = (char *) malloc((strlen(str)+1) * sizeof(char));
                            strcpy(biblioteca[op].genero[biblioteca[op].num_genero-1], str);
                            printf("Adicionar mais gêneros?(s/n)\n");
                            n = getchar();
                            limparBuffer(); 
                        }
                        printf("Deseja alterar mais algum item?(s/n)\n");
                        opcao = getchar(); 
                        limparBuffer();
                        opcao = validarChar(opcao);     
                    break;

                    case 2: // Editar um único autor
                        limparTela();
                        listarGeneros(biblioteca[op]);
                        printf("Selecione qual dos gêneros você irá alterar:");
                        scanf("%d", &op4);
                        limparBuffer();
                        op4 = validarOpcao(op4, biblioteca->num_genero);
                        op4--;
                        printf("Digite o Gênero: ");
                        editarStr(biblioteca[op].genero[op4], "Gênero");
                        printf("Deseja alterar mais algum item?(s/n)\n");
                        opcao = getchar();
                        limparBuffer();
                        opcao = validarChar(opcao);
                        break;

                    case 3: // Excluir um único autor
                        limparTela();
                        if (biblioteca[op].num_genero == 1)
                        {
                            limparTela();
                            msgErro(-7);
                            getchar();
                            break;
                        } 
                        deletarGenero(op);
                        printf("Deseja alterar mais algum item?(s/n)");
                        opcao = getchar();
                        limparBuffer();
                        opcao = validarChar(opcao);
                        break;

                    default:
                        break;
                    }
                    break;
                default:
                    opcao  = 'n';
                    break;
                }
            }  
            op++;
            limparTela();
            printf("-- Resultado final da alteração --\n");
            mostrarLivro(op-1);
            printf("Aperte enter para terminar a operação");
            getchar();
            limparBuffer();


        }

    }
    

}


void salvarTxt(){

    int i, i2;
    FILE *pArquivo;

    //Abre o arquivo
    pArquivo = fopen("bibliotecaBD.txt", "w");

    for (i = 0; i < num_livros; i++)
    {
        fprintf(pArquivo, "%s;", biblioteca[i].titulo);
        fprintf(pArquivo, "%s;", biblioteca[i].idioma);
        fprintf(pArquivo, "%s;", biblioteca[i].editora);
        fprintf(pArquivo, "%d;", biblioteca[i].num_pag);
        fprintf(pArquivo, "%d;", biblioteca[i].ano);
        for (i2 = 0; i2 < biblioteca[i].numAutores; i2++)
        {
            fprintf(pArquivo, "%s!", biblioteca[i].autores[i2]);
        }

        for (i2 = 0; i2 < biblioteca[i].num_genero; i2++)
        {
            fprintf(pArquivo, "%s$", biblioteca[i].genero[i2]);
        }
        
        fprintf(pArquivo, "%c", '\n');
    }
    fclose(pArquivo);
    free(biblioteca);
}


void recuperarDados(){

    int i, sep, j;
    FILE *pArquivo;
    char str[200], c;

    i = 0;
    sep = 0;
    pArquivo = fopen("bibliotecaBD.txt", "r");

    if(pArquivo)
    {
        while (!feof(pArquivo))
        {
            c = fgetc(pArquivo);

            if (c != '\n' && c != ';' && c != '!' && c != '$' && c != EOF)
            {
                str[i] = c;
                i++;
            }else if (c == '\n' || c == ';' || c == '!' || c == '$')
            {
                str[i] = '\0';
                i = 0;
                if (c == ';')
                {
                    if (sep == 0)
                    {
                        if (num_livros == 0)
                        {
                            biblioteca = (Livro *) malloc(1 * sizeof(Livro));
                        } else
                        {
                            biblioteca = (Livro *) realloc(biblioteca, (num_livros+1) * sizeof(Livro));
                        }

                        biblioteca[num_livros].titulo = (char*) malloc((strlen(str)+1) * sizeof(char)); 
                        strcpy(biblioteca[num_livros].titulo, str);
                        sep++;
                        biblioteca[num_livros].numAutores = 0;
                        biblioteca[num_livros].num_genero = 0;
                    }else if (sep == 1)
                    {
                        biblioteca[num_livros].idioma = (char*) malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[num_livros].idioma, str);
                        sep++;
                    }else if (sep == 2)
                    {
                        biblioteca[num_livros].editora = (char*) malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[num_livros].editora, str);
                        sep++;
                    }else if (sep == 3)
                    {
                        biblioteca[num_livros].num_pag = atoi(str);
                        sep++;
                    } else if (sep == 4)
                    {
                        biblioteca[num_livros].ano = atoi(str);
                    }

                }else if (c == '!')
                {
                    j = biblioteca[num_livros].numAutores;
                    if (j == 0)
                    {
                        biblioteca[num_livros].autores = (char**)malloc(1 * sizeof(char*));
                    }else
                    {
                        biblioteca[num_livros].autores = (char**)realloc(biblioteca[num_livros].autores,(j+1) * sizeof(char*));
                    }
                    
                    biblioteca[num_livros].autores[j] = (char*)malloc((strlen(str)+1)* sizeof(char));
                    strcpy(biblioteca[num_livros].autores[j], str);
                    biblioteca[num_livros].numAutores++;
                }else if (c =='$')
                {
                    if (biblioteca[num_livros].num_genero == 0)
                    {
                        biblioteca[num_livros].genero = (char**)malloc(1 * sizeof(char*));
                    }else
                    {
                        biblioteca[num_livros].genero = (char**)realloc(biblioteca[num_livros].genero,(biblioteca[num_livros].num_genero+1) * sizeof(char*));
                    }
                    
                    biblioteca[num_livros].genero[biblioteca[num_livros].num_genero] = (char*)malloc((strlen(str)+1)* sizeof(char));
                    strcpy(biblioteca[num_livros].genero[biblioteca[num_livros].num_genero], str);
                    biblioteca[num_livros].num_genero++;
                }else if (c =='\n')
                {
                    num_livros++;
                    sep = 0;
                }
            
                
            }
            
            
        }
    }
    fclose(pArquivo);
}


//Funções que validam, ou são funcionalidades dentro de funções

void editarStr(char *a, char *o){
    char str[100], opcao;

    gets(str);
    limparBuffer();
    strcpy(str, validarStr(str));
    printf("Deseja realmente trocar o nome do(a) %s de \"%s\" para \"%s\"?(s/n)", o, a, str);
    opcao = getchar();
    limparBuffer();
    opcao = validarChar(opcao);

    if ((opcao == 'n') || (opcao == 'N'))
    {
        printf("OPERAÇÃO CANCELADA!!!\n");
        return;
    }

    realocarMemoria(a, str);
    strcpy(a, str);

    printf("%s alterado com sucesso!(deseja alterar mais algum item?)\n", o);
}

void deletarAutor(int indice){
    int i, op;
    char  opcao, n;

    while (n != 'n' && n != 'N')
    {
        limparTela();
        if (biblioteca[indice].numAutores == 1)
        {
            msgErro(-8);
            getchar();
            return;
        }
        
    
        listarAutores(biblioteca[indice]);
        printf("Selecione qual autor você irá excluir: ");
        scanf("%d", &op);
        limparBuffer();
        op = validarOpcao(op, biblioteca->numAutores);
        op--;    
        printf("Têm certeza que deseja apagar o autor \"%s\"?\n", biblioteca[indice].autores[op]);
        opcao = getchar();
        limparBuffer();

        if ((opcao == 'n') || (opcao == 'N'))
        {
            printf("OPERAÇÃO CANCELADA!!!\n");
            return;
        }
        

        for (i = op; i < biblioteca[indice].numAutores-1; i++)
        {
            biblioteca[indice].autores[i] = (char*) realloc(biblioteca[indice].autores[i], (strlen(biblioteca[indice].autores[i+1])+1) * sizeof(char));

            strcpy(biblioteca[indice].autores[i],biblioteca[indice].autores[i+1]);
        }

        biblioteca[indice].numAutores--;
        free(biblioteca[indice].autores[biblioteca[indice].numAutores]);
        biblioteca[indice].autores = (char **) realloc(biblioteca[indice].autores, biblioteca[indice].numAutores * sizeof(char *));
        printf("AUTOR EXCLUÍDO COM SUCESSO(!!!\nDeseja deletar mais algum autor?(s/n)\n");
        n = getchar();
        limparBuffer();
        n = validarChar(n);
    }



}

void deletarGenero(int indice){
    int i, op;
    char  opcao, n;
    while (n != 'n' && n != 'N')
    {
        limparTela();
        listarGeneros(biblioteca[indice]);
        printf("Selecione qual gênero você irá excluir: ");
        scanf("%d", &op);
        limparBuffer();
        op = validarOpcao(op, biblioteca[indice].num_genero);
        op--;    
        printf("Têm certeza que deseja apagar o Gênero \"%s\"?\n", biblioteca[indice].genero[op]);
        opcao = getchar();
        opcao = validarChar(opcao);
        limparBuffer();

        if ((opcao == 'n') || (opcao == 'N'))
        {
            printf("OPERAÇÃO CANCELADA!!!\n");
            return;
        }
        

        for (i = op; i < biblioteca[indice].num_genero-1; i++)
        {
            biblioteca[indice].genero[i] = (char*) realloc(biblioteca[indice].genero[i], (strlen(biblioteca[indice].genero[i+1])+1) * sizeof(char));

            strcpy(biblioteca[indice].genero[i],biblioteca[indice].genero[i+1]);
        }

        biblioteca[indice].num_genero--;
        free(biblioteca[indice].genero[biblioteca[indice].num_genero]);
        biblioteca[indice].genero = (char **) realloc(biblioteca[indice].genero, biblioteca[indice].num_genero * sizeof(char *));
        printf("GÊNERO EXCLUÍDO COM SUCESSO!!!\nDeseja apagar mais algum gênero?(s/n)\n");
        n = getchar();
        limparBuffer();
        n = validarChar(n);
        
    }
    
    

}





void alocarMemoria(Livro n){

    if (num_livros == 1)
    {
        biblioteca = (Livro *) malloc(num_livros * sizeof(Livro));
        biblioteca[num_livros-1] = n;
    } else
    {
        biblioteca = (Livro *) realloc(biblioteca, num_livros * sizeof(Livro));
        biblioteca[num_livros-1] = n;
    }

}

void realocarMemoria(char *a, char *b){
    a = (char *) malloc((strlen(b)+1) * sizeof(char));
    strcpy(a, b);    
}

void listarAutores(Livro b){
    int i;
    printf("Os autores que participaram desse livro são: \n");
    for (i = 0; i < b.numAutores; i++)
    {
        printf("%d) %s\n", i+1, b.autores[i]);
    }
    
    
}

void listarGeneros(Livro b){
    int i;
    printf("Os gêneros desse livro são: \n");
    for (i = 0; i < b.num_genero; i++)
    {
        printf("%d) %s\n", i+1, b.genero[i]);
    }
    
    
}

int validarOpcao(int a, int a2){

    while ((a <= 0) || (a > a2))
    {
        msgErro(-3);
        scanf("%d", &a);
        limparBuffer();
    }
    return a;
}

char validarChar(char n){

    while ((n != 's') && (n != 'n') && (n != 'S') && (n != 'N'))
    {
        msgErro(-9);
        n = getchar();
        limparBuffer();
    }
    return n;
}

void listarTitulos(){
    int i;
    for (i = 0; i < num_livros; i++)
    {
        printf("%d) %s\n", i+1, biblioteca[i].titulo);
    }
}

void limparBuffer(){

    fflush(stdin);
    //__fpurge(stdin);
}

char* validarStr(char *a){

    while (strcmp(a, "") == 0)
    {
        msgErro(-4);
        gets(a);
        limparBuffer();
    }
    
    return a;
}


int validarAno(int n){
    while ((n <= 0) || (n > 2023))
    {
        msgErro(-6);
        scanf("%d", &n);
        limparBuffer();
    }
    return n;
}

int validarPag(int m){
    while (m <= 0)
    {
        msgErro(-5);
        scanf("%d", &m);
        limparBuffer();
    }
    return m;
}

void limparTela(){

    printf("\e[1;1H\e[2J");
    //system("clear");
}

//Funções que printam algo na tela

void decoracao(char a){
    int i;

    for (i = 0; i < 20; i++)
    {
        printf("%c ", a);
    }
    printf("\n");
}

void mostrarLivro(int a){

    int i;
    printf("Livro %d: \n", a+1);
    decoracao('=');
    printf("Título do livro: %s\n", biblioteca[a].titulo);
    printf("Autor(es) do livro: %s", biblioteca[a].autores[0]);

    for (i = 1; i < biblioteca[a].numAutores; i++)
    {
        printf(", %s", biblioteca[a].autores[i]);
    }
    printf("\n");
    
    printf("Editora: %s\n", biblioteca[a].editora);

    printf("Idioma do Livro: %s", biblioteca[a].idioma);
    printf("\n");
    printf("Número de páginas: %d\n", biblioteca[a].num_pag);
    printf("Ano em que o livro foi escrito: %d\n", biblioteca[a].ano);

    printf("Genero(os) do Livro: %s", biblioteca[a].genero[0]);
    for (i = 1; i < biblioteca[a].num_genero; i++)
    {
        printf(", %s", biblioteca[a].genero[i]);
    }
    printf("\n");
    decoracao('=');     

}

void menuPrincipal(){
    printf("Livros cadastrados: %d\n", num_livros);
    printf("C O N T R O L E     D E     L I V R O S\n");
    decoracao('#');
    printf("# # # \t  -- Menu Principal -- \t  # # #\n");
    printf("# # # 1) Adicionar livro\t  # # #\n");
    printf("# # # 2) Editar livro\t\t  # # #\n");
    printf("# # # 3) Excluir livro\t\t  # # #\n");
    printf("# # # 4) Listar livro(s)\t  # # #\n");
    printf("# # # 5) Encerrar programa\t  # # #\n");
    decoracao('#');
    printf("\nInsira qual será a opção selecionada: ");
}

void menuEditar(){

    printf("C O N T R O L E     D E     L I V R O S\n");
    decoracao('*');
    printf("* * * 1) Título \t\t  * * * \n");
    printf("* * * 2) Autor(es) \t\t  * * * \n");
    printf("* * * 3) Editora \t\t  * * * \n");
    printf("* * * 4) Ano de edição \t\t  * * * \n");
    printf("* * * 5) Número de páginas\t  * * * \n");
    printf("* * * 6) Idioma \t\t  * * * \n");
    printf("* * * 7) Genero(s) \t\t  * * * \n");
    printf("* * * 8) Voltar p/ Opção anterior * * * \n");
    decoracao('*');
    printf("\nInsira qual será a opção selecionada: ");

}

void menuListar(){
    printf("C O N T R O L E     D E     L I V R O S\n");
    decoracao('@');
    printf("@ @ @ 1) Listar Livro \t\t  @ @ @ \n");
    printf("@ @ @ 2) Listar Todos \t\t  @ @ @ \n");
    printf("@ @ @ 3) Voltar p/ Opção anterior @ @ @ \n");
    decoracao('@');
    printf("\nInsira qual será a opção selecionada: ");
}

void subMenus(int o){ // Submenus da função editar

    switch (o)
    {
    case 1:
        printf("C O N T R O L E     D E     L I V R O S\n");
        decoracao('*');
        printf("* * * 1) Incluir Autor \t\t  * * * \n");
        printf("* * * 2) Editar Autor \t\t  * * * \n");
        printf("* * * 3) Excluir Autor \t\t  * * * \n");
        printf("* * * 4) Voltar p/ Opção anterior * * * \n");
        decoracao('*');
        printf("\nInsira qual será a opção selecionada: ");

        break;
    case 2:
        printf("C O N T R O L E     D E     L I V R O S\n");
        decoracao('*');
        printf("* * * 1) Incluir Genero \t  * * * \n");
        printf("* * * 2) Editar Genero \t  * * * \n");
        printf("* * * 3) Excluir Genero \t  * * * \n");
        printf("* * * 4) Voltar p/ Opção anterior * * * \n");
        decoracao('*');
        printf("\nInsira qual será a opção selecionada: ");

        break;
    }
}

void msgErro(int e){

    switch (e)
    {
    case -1:
        printf("!!!OPCAO INVÁLIDA!!!\n(aperte enter para voltar para tela inicial)");
        getchar();
        break;
    case -2:

        printf("ERRO!!! NENHUM LIVRO REGISTRADO NO BANCO DE DADOS!!!\n(aperte enter para voltar para tela inicial)");
        getchar();
        break;

    case -3:
        printf("OPCAO INVÁLIDA!!!!!\nFAVOR REINSERIR: ");
        break;

    case -4:
        printf("ERRO!!!!\nCAMPO EM BRANCO!!!!\nREINSIRA: ");
        break;
    case -5:
        printf("!!!!ERRO!!!!\nNÚMERO DE PÁGINAS INVÁLIDO!!!!!!\nReinsira por favor: ");
        break;
    case -6: 
        printf("!!!!ERRO!!!!\nANO INVÁLIDO!!!!!!\nReinsira por favor: ");
        break;
    case -7:
        printf("!!!ERRO!!!!\nNÃO É POSSÍVEL REALIZAR EXCLUSÕES DESTA OPÇÃO!!!!\nCaso queira mudar algo, selecione a opção de editar!!!!!");
        break;
    case -8:
        printf("!!!ERRO!!!!\nNÃO É POSSÍVEL REALIZAR MAIS EXCLUSÕES!!!!\nretornando à tela anterior...");
        break;
    case -9:
        printf("!!!ERRO!!!!\nCOMANDO INCORRETO!!!!\nReinsira:");
        break;
    default:
        break;
    }
}


