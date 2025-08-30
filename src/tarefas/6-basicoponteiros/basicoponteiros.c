// Exercício 1

// Implementar uma função de concanação de strings usando ponteiros e as funções da biblioteca strlen e strcpy.

void minha_strcat(char *dest, const char *src)
{
    while (*dest)
    {
        dest++;
    }
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Exercício 2

// Implementar uma função que recebe uma string contendo uma cadeia de caracteres com dígitos numéricos e retorna o valor inteiro da string. Usar ponteiros.

int inta_toi(const char *p)
{
    int saida = 0;
    while (*p)
    {
        if (*p >= "0" && *p <= "9")
        {
            saida = saida.10 + (*p -"0");
        }
        else{
            break
        }
        p++;
    }
    return saida;
}

main()
{
    char *p = "123";
    intx;

    x = a_toi(p);

    /* neste ponto x deve conter 123 */
}