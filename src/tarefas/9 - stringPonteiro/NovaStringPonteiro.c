//  Implemente em linguagem C um programa que receba uma ou mais strings como argumentos de linha de comando.
// O programa deve:

// 1. Inverter cada string recebida utilizando manipulação de ponteiros.
// 2. Imprimir na tela a string invertida.
// 3. Imprimir o tamanho da string.

// Para isso, implemente uma função com o seguinte protótipo:

//     int inverter(char *str);

// Essa função deve inverter a string recebida (modificando-a no próprio vetor via ponteiros) e retornar
// o tamanho da string (utilize strlen() da biblioteca <string.h>).

// Exemplo de execução esperada:

// Entrada pelo terminal:
//     ./prog "computador" "rede" "ifsc"

// Saída:
//     rodautpmoc (Tamanho: 10)
//     eder (Tamanho: 4)
//     csfi (Tamanho: 4)

// Esqueleto sugerido:
#include <stdio.h>
#include <string.h>

// Função que inverte a string no próprio vetor e retorna o tamanho
int inverter(char *str) {
    int len = strlen(str);
    char *ini = str;
    char *fim = str + len - 1;

    while (ini < fim) {
        char temp = *ini;
        *ini = *fim;
        *fim = temp;
        ini++;
        fim--;
    }

    return len;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <string1> <string2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        // Criar uma cópia local da string, pois strings em argv são literais e não podem ser modificadas diretamente
        char copia[1000];
        strncpy(copia, argv[i], sizeof(copia));
        copia[sizeof(copia) - 1] = '\0'; // Garantir que termina com '\0'

        int tamanho = inverter(copia);
        printf("%s (Tamanho: %d)\n", copia, tamanho);
    }

    return 0;
}
