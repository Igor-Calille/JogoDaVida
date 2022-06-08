#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int Criacao_Matricial();    //Funcao que limita a matriz para a dimesão requisitada pelo jogador

typedef struct 
{
    char cel;   // "X": Sem celula; "O": Celula viva
    int info;   // 0: sem celula; 1:  com celula    |   Criado para alterar a matriz apenas depois da matriz original ser varrida,
                // evitando que o programa altera a matriz por causa de uma célula recem colocada
}tipo_m;

tipo_m Matriz[100][100];              //Criar a matriz do mundo matricial

int Criacao_Matricial()
{
    int o;                          //Ordem da matriz
    o = Criacao_Matricial_Menu();
    
    return o;
}
