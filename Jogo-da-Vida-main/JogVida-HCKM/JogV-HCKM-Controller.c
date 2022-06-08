# include "JogV-HCKM-View.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void Matriz_Matricial();                                //******************************************************************
void Esvazia_Matriz(int o);                             //Funcao que prepara a matriz "Esvaziando a mtriz", seja para começar um novo jogo ou pra limpar uma matriz anterior
void Seres_Vivos(int o);                                //Funcao que da a opcao de escolher colocar as celulas manualmente ou de uma forma randomica
void Coloca_Celula(int a, int b, int count, int c);     //Funcao que atribui as mudanças feitas na matriz, a partir das condições da Função "void Calcula_Vizinhos()"
void Calcula_Vizinhos(int o, int q, float w);           //Função com todas as condições de nascimento, morte ou manutenção de uma celula

void Menu_Inicial()
{
    int op;
    op = Menu_Inicial_opcoes();
    do
    {
        switch (op)
        {
            case 1: //Criar a matriz
                Matriz_Matricial();
                break;
            case 2: //Selecionar uma opcao de uma imagem pre-definida
                printf("opcao ainda nao implementada");
                break;
            case 3: //Salve sua matriz
                printf("opcao ainda nao implementada");
                break;
            case 4: //Carregue sua matriz
                printf("opcao ainda nao implementada");
                break; 
            case 5: //Regras
                Regras();
                break;
            case 6: //Sair do programa
                exit(0);
                break;
            default:
                printf("Erro! Digite os numeros indicados!");
                break;
        }
        
    } while (op>6);
    
}

void Esvazia_Matriz(int o)
{
    int a, b;                       //Variaveis do loop

    for(a = 0; a<=o; a++)
    {
        for(b = 0; b<=o; b++)
        {
            Matriz[a][b].cel = '.';
        }
    }
}

void Seres_Vivos(int o)
{
    int op, opRand, opEscolhax = 101, opEscolhay = 101;     //esta igualado a 101 para retirar qualquer possibilidade de entrar na matriz q possui o max de 100x100
    int aRand, bRand;
    int a;

    op = Seres_Vivos_Menu();

    if(op == 1) //Colocar todas as celulas manualmente
    {
        
        do
        {
            Mostra_Matriz(o);
            opEscolhax = Seres_Vivos_Menu_Escolhax(o);
            opEscolhay = Seres_Vivos_Menu_Escolhay(o);
            if(opEscolhax >= 0 || opEscolhay >= 0)
            {
                Matriz[opEscolhax][opEscolhay].cel = 'O';
                Matriz[opEscolhax][opEscolhay].info = 1;
            }
            
        }while (opEscolhax >= 0 || opEscolhay >= 0);

    }
    else    //Randomizar a posicao de algumas celulas e ter a opcao de colocar manualmente
    {
        srand(time(NULL)); 
        opRand = Seres_Vivos_Menu_Rand(o);
        for(a = 1; a <= opRand; a++)
        {
            aRand = rand()%o;
            bRand = rand()%o;
            
            Matriz[aRand][bRand].cel = 'O';
            Matriz[aRand][bRand].info = 1;
        }

        do
        {
            Mostra_Matriz(o);
            opEscolhax = Seres_Vivos_Menu_Escolhax(o);
            opEscolhay = Seres_Vivos_Menu_Escolhay(o);
            if(opEscolhax >= 0 || opEscolhay >= 0)
            {
                Matriz[opEscolhax][opEscolhay].cel = 'O';
                Matriz[opEscolhax][opEscolhay].info = 1;
            }
            
        }while (opEscolhax >= 0 || opEscolhay >= 0);

        Mostra_Matriz(o);

    }
}

void Matriz_Matricial()
{
    int  x = 1;
    do
    {
        int o, q, w;                          //Ordem da matriz
        o = Criacao_Matricial();

        Esvazia_Matriz(o);
        Seres_Vivos(o);
        q = Calcula_Vizinhos_Menu1();
        w = Calcula_Vizinhos_Menu2();
    
        Calcula_Vizinhos(o, q, w);

        x = Esvazia_Matriz_Menu();
        
    } while (x == 1);
    Menu_Inicial();

}

void Coloca_Celula(int a, int b, int count, int c)
{
    if(count >= 4)  //Morte por falta de comida
    {
        Matriz[a][b].info = 0;
        c=1;    //Testa se houve alguma mudança na geração. Varaivel utilizada para futurmanete testar se o codigo não esta printando algo redundante
    }
    else if(count == 3) //Reprodução
    {
        Matriz[a][b].info = 1;  //Marcada como "recem colocada na matriz", para não gerar ou matar celulas quando o loop se repetir
        c=1;    //Testa se houve alguma mudança na geração. Varaivel utilizada para futurmanete testar se o codigo não esta printando algo redundante
    }
    else if(count == 3 || count == 2)    //Sobrevivencia
    {
        //N faz nada
    }
    else if(count == 0 || count == 1)    //Morte por solidao
    {
        Matriz[a][b].info = 0;
        c=1;    //Testa se houve alguma mudança na geração. Varaivel utilizada para futurmanete testar se o codigo não esta printando algo redundante
    }
}

void Calcula_Vizinhos(int o, int q, float w)
{
    int a, b, i=1;
    int count = 0;
    int c = 0;  //contador para chegar se houve alguma mudança na geraçao, caso não acontece nada, o comando de criar uma nova geracao é encerrado para evitar redundancia do codigo

    do
    {
        for(a = 0; a < o; a++)
        {
            for(b = 0; b<o; b++)
            {
                if(a == 0 && b==0)  //Primeiro elemento (1X1) 
                {
                    if(Matriz[a+1][b].cel == 'O') //Numero da direita
                    {
                        count++;
                    }
                    if(Matriz[a][b+1].cel == 'O') //Numero de baixo
                    {
                        count++;
                    }
                    if(Matriz[a+1][b+1].cel == 'O')    //numero da diagonal-direita-baixo
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);
                    
                    count = 0;
                }
                else if(a == 0 && b == (o-1)) //Ultimo elemento da coluna 1 (1Xo) 
                {
                    if(Matriz[a+1][b].cel == 'O') //Numero da direita
                    {
                        count++;
                    }
                    if(Matriz[a][b-1].cel == 'O') //Numero de cima
                    {
                        count++;
                    }
                    if(Matriz[a+1][b-1].cel == 'O')     //numero da diagonal-direita-cima
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);

                    count = 0;
                }
                else if(a == (o-1) && b==0)   //Ultimo elemento da linha 1 (oX1) 
                {
                    if(Matriz[a-1][b].cel == 'O') //Numero da esquerda
                    {
                        count++;
                    }
                    if(Matriz[a][b+1].cel == 'O') //Numero de baixo
                    {
                        count++;
                    }
                    if(Matriz[a-1][b+1].cel == 'O')     //numero da diagonal-esquerda-baixo
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);

                    count = 0;
                }
                else if(a == (o-1) && b == (o-1))   //ultimo elemento (oXo) 
                {
                    if(Matriz[a-1][b].cel == 'O') //Numero da esquerda
                    {
                        count++;
                    }
                    if(Matriz[a][b-1].cel == 'O') //Numero de cima
                    {
                        count++;
                    }
                    if(Matriz[a-1][b-1].cel == 'O')     //numero da diagonal-esquerda-cima
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);

                    count = 0;
                } 
                else if(a == 0 && (b>0 && b<o))  //elementos da coluna 1 (menos o primeiro e o ultimo)
                {
                    if(Matriz[a+1][b].cel == 'O') //Numero da direita
                    {
                        count++;
                    }
                    if(Matriz[a][b-1].cel == 'O') //Numero de cima
                    {
                        count++;
                    }
                    if(Matriz[a][b+1].cel == 'O') //Numero de baixo
                    {
                        count++;
                    }
                    if(Matriz[a+1][b-1].cel == 'O')     //numero da diagonal-direita-cima
                    {
                        count++;
                    }
                    if(Matriz[a+1][b+1].cel == 'O')    //numero da diagonal-direita-baixo
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);

                    count = 0;
                }
                else if(b == 0 && (b>0 && a<o))  //elementos da linha 1 (menos o primeiro e o ultimo)
                {
                    if(Matriz[a-1][b].cel == 'O') //Numero da esquerda
                    {
                        count++;
                    }
                    if(Matriz[a+1][b].cel == 'O') //Numero da direita
                    {
                        count++;
                    }
                    if(Matriz[a][b+1].cel == 'O') //Numero de baixo
                    {
                        count++;
                    }
                    if(Matriz[a+1][b+1].cel == 'O')    //numero da diagonal-direita-baixo
                    {
                        count++;
                    }
                    if(Matriz[a-1][b+1].cel == 'O')     //numero da diagonal-esquerda-baixo
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);

                    count = 0;
                }
                else
                {
                    if(Matriz[a-1][b].cel == 'O') //Numero da esquerda
                    {
                        count++;
                    }
                    if(Matriz[a+1][b].cel == 'O') //Numero da direita
                    {
                        count++;
                    }
                    if(Matriz[a][b-1].cel == 'O') //Numero de cima
                    {
                        count++;
                    }
                    if(Matriz[a][b+1].cel == 'O') //Numero de baixo
                    {
                        count++;
                    }
                    if(Matriz[a-1][b+1].cel == 'O')     //numero da diagonal-esquerda-baixo
                    {
                        count++;
                    }
                    if(Matriz[a-1][b-1].cel == 'O')     //numero da diagonal-esquerda-cima
                    {
                        count++;
                    }
                    if(Matriz[a+1][b+1].cel == 'O')    //numero da diagonal-direita-baixo
                    {
                        count++;
                    }
                    if(Matriz[a+1][b-1].cel == 'O')     //numero da diagonal-direita-cima
                    {
                        count++;
                    }

                    Coloca_Celula(a, b, count, c);
                   
                    count = 0;
                }
            }
        }
        i++;
       // if(c==1)
       // {
            for(a = 0; a < o; a++)
            {
                for(b = 0; b<o; b++)
                {
                    if(Matriz[a][b].info == 1)
                    {
                        Matriz[a][b].cel = 'O';
                    }
                    else if(Matriz[a][b].info == 0)
                    {
                        Matriz[a][b].cel = '.';
                    }
            
                }
            }
       // }
        //else
        //{
            //Geracao_Redundante();
        //}
        Mostra_Matriz(o);
        if(w>=1)
        {
            pause (w);
        }
        else//Passo a passo
        {
            Passo_a_Passo_Menu();
        }
    } while (i<=q);
    
}
