#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**********************************/
/***** DEFINIÇÕES DESTE MÓDULO  ****/
/**********************************/

#define TAM_MAT 10
#define MAX_TIROS 30
#define MAX_NOME 30

#define LIVRE 0
#define PORTA_AVIOES 1
#define FRAGATA 2
#define SUBMARINO 3

/**********************************/
/***** VARIÁVEIS GLOBAIS **********/
/**********************************/

int ZonaDeGuerra[TAM_MAT][TAM_MAT];/* Matriz do espaço de batalha */
int ContadorTiros=0;
int PontuacaoFinal;    			   /* acumula a pontuação do jogador */
char nome[MAX_NOME];
int x_sorteado;
int y_sorteado;


/***********************************/
/****  FUNÇÕES DESTE MÓDULO ********/
/***********************************/

/***** FUNÇÕES DE INICIALIZAÇÃO ****/

void ZerarMatriz()
{
    int i,j;

    for (i=0;i<TAM_MAT;i++)
        for(j=0;j<TAM_MAT;j++)
            ZonaDeGuerra[i][j] = LIVRE;
}

void SortearCasa()
{
    do {
        /* generate secret number: */
        x_sorteado = rand() % TAM_MAT;
        y_sorteado = rand() % TAM_MAT;
    } while (ZonaDeGuerra[x_sorteado][y_sorteado] != LIVRE);

}

void PosicionarFragatas()
{
    int i;
    for(i=0;i<4;i++){
        SortearCasa();
        ZonaDeGuerra[x_sorteado][y_sorteado] = FRAGATA;
    }
}

void PosicionarSubmarinos()
{
    int i;
    for(i=0;i<5;i++){
        SortearCasa();
        ZonaDeGuerra[x_sorteado][y_sorteado] = SUBMARINO;
    }
}

void PosicionarPortaAvioes()
{
    SortearCasa();
    ZonaDeGuerra[x_sorteado][y_sorteado] = PORTA_AVIOES;
}

void PosicionarNavios()
{
    /* initialize random seed: */
    srand ( time(NULL) );

    PosicionarPortaAvioes();
    PosicionarFragatas();
    PosicionarSubmarinos();
}

/*** FUNÇÕES DE IMPRESSÃO NA TELA **/

void ImprimeLinha(int linha)
{
    int j;

    printf("     ");
    for(j=0;j<TAM_MAT;j++) {
        printf("| %2d ",ZonaDeGuerra[linha][j]);
    }
    printf("|\n");
    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
}

void ImprimeLinhaEscondida(int linha)
{
    int j;

    printf("     ");
    for(j=0;j<TAM_MAT;j++) {
        if (ZonaDeGuerra[linha][j]>=0 &&  ZonaDeGuerra[linha][j]<=3)
            printf("| -- ");
        else
            printf("| %2d ",ZonaDeGuerra[linha][j]);
    }
    printf("|\n");
    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
}

void ImprimeMatrizTudo()
{
    int i;

    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
    for(i=0;i<TAM_MAT;i++)
        ImprimeLinha(i);
}

void ImprimeMatrizEscondida()
{
    int i;

    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
    for(i=0;i<TAM_MAT;i++)
        ImprimeLinhaEscondida(i);
}

// Criar uma função de tiro no exemplo de Batalha Naval.. Esta função deve ler a posição de tiro, verificar se a casa ainda não foi alvejada. Se alvejada pergunta novamente a posição. Se a posição for válida e tiver um navio então o usuário ganha pontos da seguinte forma: 10 para o porta aviões, 5 para o submarino e 3 para fragata. A função deve retornar 0 se o jogo continua, 1 se o usuário atingiu todos os navios ou 2 se o usuário teve um número máximo de tiros ultrapassado (assumir 30 tiros). Ao final, mostrar a situação do jogo.

int Tiro()
{
    int x, y;
    int valido = 0;

    while (!valido) {
        printf("\nDigite a linha (0-%d): ", TAM_MAT-1);
        scanf("%d", &x);
        printf("Digite a coluna (0-%d): ", TAM_MAT-1);
        scanf("%d", &y);

        if (x < 0 || x >= TAM_MAT || y < 0 || y >= TAM_MAT) {
            printf("⚠️ Posição inválida! Tente novamente.\n");
            continue;
        }

        if (ZonaDeGuerra[x][y] < 0) { 
            printf("⚠️ Essa posição já foi alvejada! Escolha outra.\n");
            continue;
        }

        valido = 1;
    }

    ContadorTiros++;

    switch(ZonaDeGuerra[x][y]) {
        case PORTA_AVIOES:
            PontuacaoFinal += 10;
            printf("+10 pontos\n");
            break;
        case SUBMARINO:
            PontuacaoFinal += 5;
            printf("+5 pontos\n");
            break;
        case FRAGATA:
            PontuacaoFinal += 3;
            printf("+3 pontos\n");
            break;
        default:
            printf("Nenhum navio atingido.\n");
            break;
    }

    ZonaDeGuerra[x][y] = -abs(ZonaDeGuerra[x][y]);

    ImprimeMatrizEscondida();
    printf("Tiros usados: %d/%d | Pontuação: %d\n", ContadorTiros, MAX_TIROS, PontuacaoFinal);

    int i, j, fim = 1;
    for (i = 0; i < TAM_MAT; i++) {
        for (j = 0; j < TAM_MAT; j++) {
            if (ZonaDeGuerra[i][j] == PORTA_AVIOES ||
                ZonaDeGuerra[i][j] == SUBMARINO ||
                ZonaDeGuerra[i][j] == FRAGATA) {
                fim = 0;
            }
        }
    }

    if (fim) {
        printf("\nVocê destruiu todos os navios!\n");
        return 1;
    }

    if (ContadorTiros >= MAX_TIROS) {
        printf("\nVocê usou todos os tiros!\n");
        return 2;
    }

    return 0;
}


int main()
{
    int situacao;
    ZerarMatriz();
    PosicionarNavios();
    ImprimeMatrizEscondida();
    do {
        situacao = Tiro();
    } while (situacao==0);
    /*
      Implementar aqui o tratamento final da variável situação
    */
    return 0;
}