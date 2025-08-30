#include <stdio.h>
// Exercício 1 - Troca de valores com ponteiros (swap)

// ---------------------------------------------------

// Implemente um programa em C que contenha uma função chamada swap() responsável por trocar os valores de duas variáveis inteiras.

// A função deve receber os endereços das variáveis como parâmetros (ou seja, usar ponteiros).

// Protótipo da função:

void swap(int *a, int *b)
{
    // a = -a +b
    // b = b -a // a
    // a = a + b //b

    *a = -*a + *b;
    *b = *b - *a;
    *a = *a + *b;
}

int main()
{

    int x = 10, y = 20;

    swap(&x, &y);

    printf("x = %d, y = %d \n", x, y);
}
// Exemplo de uso no main():

// int x = 10, y = 20;

// swap(&x, &y);

// Resultado esperado:

// Antes: x = 10, y = 20

// Depois : x = 20, y = 10

// Exercício 2 - Soma de elementos de um vetor

// -------------------------------------------

// Escreva uma função que receba um vetor de inteiros e seu tamanho, e retorne a soma de seus elementos.

// A função deve utilizar ponteiros para percorrer o vetor.

// Protótipo:

int soma_vetor(int *v, int n)
{
    int saida = 0;
    for (int i = 0; i < n; i++)
    {
        saida += *v;
        *v++;
    }
    return saida;
}

// int main()
// {

//     int numeros[] = {1, 2, 3, 4, 5};
//     int total = soma_vetor(numeros, 5);

//     printf("%d \n", total);
// }

// Exemplo de uso:

// int numeros[] = {1, 2, 3, 4, 5};

// int total = soma_vetor(numeros, 5);

// Resultado esperado:

// Soma = 15