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
 
int inverter(char *str) {
    char saida;
/////fazer em casa
    int ponteiroInvertido = *str -1;
    while(*str){

    }
    
    // implementar aqui usando ponteiros
}
 
int main(int argc, char *argv[]) {
    // Implementar aqui
 
} 