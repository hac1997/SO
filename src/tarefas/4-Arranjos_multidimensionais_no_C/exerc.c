// TAREFA - Arranjos multidimensionais no C 	de 22/08/2025 às 21h55 a 29/08/2025 às 23h59 	Não 	0

// Criar uma função de tiro no exemplo de Batalha Naval.. Esta função deve ler a posição de tiro, verificar se a casa ainda não foi alvejada.
// Se alvejada pergunta novamente a posição. Se a posição for válida e tiver um navio então o
// usuário ganha pontos da seguinte forma: 10 para o porta aviões, 5 para o submarino e 3 para fragata.
// A função deve retornar 0 se o jogo continua, 1 se o usuário atingiu todos os navios ou 2 se o usuário teve um número
// máximo de tiros ultrapassado (assumir 30 tiros). Ao final, mostrar a situação do jogo.

#include <stdio.h>
int main ()
{
   char alfa[50];

   int i=0;

   printf ("Entre com a cadeia: ");
   scanf("%s",alfa);
   while(alfa[i]!=0)
      i++;
   printf ("\nNumero de caracteres em %s = %d \n", alfa, i);
   return 0;
}