
#include <string.h>

// PARTE 1 - Arranjos no C. Strings. Funções. 	de 20/08/2025 às 21h55 a 27/08/2025 às 23h59 	Não 	3

// Exercício 1

// Dois vetores tridimensionais partem da origem (0,0,0) e terminam, respectivamente, nos pontos A e B, definidos por suas coordenadas no espaço 3D.

// Escreva uma função  em linguagem C que recebe os vetores correspondentes aos pontos A e B e retorne o produto escalar entre os vetores A e B

float produto_escalar(float vet1[3], float vet2[3])
{
    float saida = 0;
    for (int a = 0; a < 3; a++)
    {
        saida += vet1[a] * vet2[a];
    }
    return saida;
}

// Exercício 2

// Escrever uma função que recebe duas palavras (sem espaços) e concatena a segunda ao final da primeira,
// usando as funções strlen() e strcpy() da biblioteca <string.h>. Não utilize strcat().

// Regras:
// - considerepalavras  sem espaços.
// - O resultado da concatenação deve ser armazenado em um terceiro vetor que também é um parâmetro.
// - Utilize strlen() para calcular o ponto de inserção da segunda palavra.
// - Utilize strcpy() para fazer as cópias de conteúdo entre vetores.
//  -Não use ponteiros.

// Protótipo sugerido:
void concatenar(char palavra1[], char palavra2[], char resultado[])
{
    int tam1 = strlen(palavra1);
    strcpy(resultado, palavra1);
    strcpy(resultado + tam1, palavra2);
}
