# include "JogV-HCKM-Model.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//  Funcoes void de interface do terminal
void Nome_Do_Domino();                  //Apenas visual, mostra o nome do projeto com "#"
void clear();                           //Funcão indentifica o sistema do usuário para a funcao de limpar a interface
void limpar_Interface();                //Funcão que limpa o terminal
void flush_in();                        //funcão que limpa o buffer
void pause (float);                     //Funcao que cria um delay entre os printf's,(Uma ideia de deixar o terminal com uma apresentacao melhor)

//  Funcoes void visuais do terminal
void Regras();                          //Função de todas as regras de como o jogo funciona
void Mostra_Matriz(int o);              //******************************************************************
void Geracao_Redundante();              //******************************************************************
void Passo_a_Passo_Menu();              //Funcão que cria a opcao de dar o tempo necessario para quem está executando o código renovar a geração

//  Funcoes int visuais do terminal
int Menu_Inicial_opcoes();              //Mostra as opcoes no menu incial
int Criacao_Matricial_Menu();           //Funcao que cria as dimensoes das matrizes (ex: AxA)
int Seres_Vivos_Menu();                 //Menu que da a opcao de escolher colocar as celulas manualmente ou de uma forma randomica
int Seres_Vivos_Menu_Escolhax(int o);   //Menu da opcao de colocar as celulas manualmente (eixo x)      obs: Como em c, uma funcao não pode retornar duas variaveis,
int Seres_Vivos_Menu_Escolhay(int o);   //Menu da opcao de colocar as celulas manualmente (eixo y)           criamos duas funcoes para os dois eixos
int Seres_Vivos_Menu_Rand(int o);       //Menu da opcao randomica
int Calcula_Vizinhos_Menu1();           //Menu que pergunta quantas geracoes o jogador deseja representar
int Calcula_Vizinhos_Menu2();           //Menu que pergunta o intervalo entre as geracoes, sendo o 0 o passo a passo
int Esvazia_Matriz_Menu();              //Menu que pergunta se o jogador deseja realizar o jogo novamente ou voltar ao menu inicial



void Nome_Do_Domino()
{

    printf("\n\n\n       # #######  #####  #######       ######     #          #     # ### ######     #                #     #  #####  #    # #     # \n");
    pause (0.05);
    printf("       # #     # #     # #     #       #     #   # #         #     #  #  #     #   # #               #     # #     # #   #  ##   ## \n");
    pause (0.05);
    printf("       # #     # #       #     #       #     #  #   #        #     #  #  #     #  #   #              #     # #       #  #   # # # # \n");
    pause (0.05);
    printf("       # #     # #  #### #     #       #     # #     #       #     #  #  #     # #     #    #####    ####### #       ###    #  #  # \n");
    pause (0.05);
    printf(" #     # #     # #     # #     #       #     # #######        #   #   #  #     # #######             #     # #       #  #   #     # \n");
    pause (0.05);
    printf(" #     # #     # #     # #     #       #     # #     #         # #    #  #     # #     #             #     # #     # #   #  #     # \n");
    pause (0.05);
    printf("  #####  #######  #####  #######       ######  #     #          #    ### ######  #     #             #     #  #####  #    # #     # \n");
    pause (0.05);
}

void clear()    //Funcão indentifica o sistema do usuário para a funcao de limpar a interface
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void pause (float delay1) //Funcao que cria um delay entre os printf's,(Uma ideia de deixar o terminal com uma apresentacao melhor)
{

   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

void flush_in()     //funcão que limpa o buffer
{
    char op;
    while ((op = fgetc(stdin)) != EOF && op != '\n')
    {
    };
    printf("\r");
}

void limpar_Interface()  //Funcão que limpa o terminal
{ 
    char op;
    printf("\n\n----------------Pressione <ENTER> para continuar----------------");
    getchar();
    flush_in();
    clear();
}

void Regras()
{

}

int Menu_Inicial_opcoes()
{
    int op;
    do
    {
        printf("\n======================= Menu Inicial =======================");
        printf("\n(1)- Criar a matriz");
        printf("\n(2)- Selecionar uma opcao de uma imagem pre-definida");
        printf("\n(3)- Salve sua matriz");
        printf("\n(4)- Carregue sua matriz");
        printf("\n(5)- Regras do jogo da vida");
        printf("\n(6)- Sair do programa");
        printf("\nDigite sua opcao: ");
        scanf("%d", &op);

    }while (op>6);

    return op;

}

int Criacao_Matricial_Menu()
{
    int op;
    do
    {
        printf("\nDigite o tamanho do mundo matricial( AxA ) que voce deseja criar (Minimo: 2 | Maximo 100): ");
        scanf("%d", &op);
        if(op<2 || op>100)
        {
            printf("\nO numero informado não esta dentro do intervalo permitido\n");
        }

    }while (op<2 || op>100);
    op = op-1;
    return op; 
}

int Seres_Vivos_Menu()
{
    int op;

    do
    {
        printf("\nEscolha uma das seguintes opcoes:\n(1)- Escolha por conta propria onde colocar as celulas.\n(2)- Deixe o programa escolher de uma forma randomica.\n");
        scanf("%d", &op);
    }while (op<1 || op>2);
    
    return op;
}

int Seres_Vivos_Menu_Escolhax(int o)
{
    int x;
    do
    {
        printf("\nDigite a coordenada x (numero de cima) que voce deseja inserir uma celula (Digite 0 para parar de colocar celulas).\n");
        scanf("%d", &x);
    } while (x>o+1 || x<0);
    x = x - 1;

    return x;
}

int Seres_Vivos_Menu_Escolhay(int o)
{
    int y;
    do
    {
        printf("\nDigite a coordenada y (numero da esquerda) que voce deseja inserir uma celula (Digite 0 para parar de colocar celulas).\n");
        scanf("%d", &y);
    } while ( y>o+1 || y<0);
    y = y - 1;

    return y;
}

int Seres_Vivos_Menu_Rand(int o)
{
    int op;
    int tam = (o+1)*(o+1);
    do
    {
        printf("\nEscolha quantas celulas voce deseja inserir na matriz aleatoriamente(lembrando que sua matriz possui %d termos | Recomendamos que voce coloque um numero proximo de %d).\n", tam, tam/2);
        scanf("%d", &op);
        if(op>tam)
        {
            printf("\nO numero digitado nao esta no intervalo de termos permitidos, digite novamente.\n");
        }
    } while (op>tam || op<0);

    return op;
}

void Mostra_Matriz(int o)
{
    int a, b;                       //Variaveis do loop

    printf("  ");
    for(a = 0; a<=o; a++)
    {
        if(a<9)
            printf(" 0%d", a+1);
        else
            printf(" %d", a+1);
    }
    printf("\n");
    for(b = 0; b<=o; b++)
    {
        if(b<9)
            printf("0%d  ", b+1);
        else
            printf("%d  ", b+1);

        for(a = 0; a<=o; a++)
        { 
            if(a<9)
            printf("%c  ", Matriz[a][b].cel);
            else
            printf("%c  ", Matriz[a][b].cel);
        }
        printf("\n");
    }
    printf("\n");
}

int Calcula_Vizinhos_Menu1()
{
    int op;
    printf("\nQuantas geracoes voce deseja representar?\n ");
    scanf("%d", &op);

    return op;
}

int Calcula_Vizinhos_Menu2()
{
    float op;
    do
    {
        printf("\nDe quanto em quanto tempo voce deseja representar a nova geracao(min 1s | max 10s) ou (0s Para visulaizar passo a passo)\n");
        scanf("%f", &op);
    } while (op<0 || op>10);
    

    return op;
}

void Geracao_Redundante()
{
    printf("\nNao havera mudanca na proxima gerancao, portanto o programa foi encerrado\n");
    exit(0);
}

int Esvazia_Matriz_Menu()
{
    int op;
    do
    {
        printf("\nDeseja limpar a Matriz e comecar denovo?(1- Sim | 2-Nao)\n");
        scanf("%d", &op);
        if(op<1 || op>2)
        {
            printf("\nO numero informado não esta dentro do intervalo permitido\n");
        }
    }while (op<1 || op>2);
    
    return op;
}

void Passo_a_Passo_Menu()
{
    char op;
    printf("\n\n----------------Pressione <ENTER> para continuar----------------\n");
    scanf("%c", &op);   //A funcao não precisa retornar nada, apenas cria a opcao de criar a geracao passo a passo
}
