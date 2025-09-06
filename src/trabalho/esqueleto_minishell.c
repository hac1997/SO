#define _XOPEN_SOURCE 700
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

/* =============================================================
 * Parsing simples: separa linha em tokens por " \t\n" e aloca argv
 * - Retorna argc (>=0) ou -1 em caso de erro
 * - argv_out recebe um vetor terminado em NULL (argv[argc] == NULL)
 * - As strings dos tokens são duplicadas (strdup)
 * - Limite de tokens configurável via parâmetro
 * ============================================================= */
static int parse_line_simple(char *line, char ***argv_out, int max_tokens)
{
    int argc;
    char **argv;
    char *save;
    const char *delims;

    if (line == NULL || argv_out == NULL || max_tokens <= 0)
    {
        errno = EINVAL;
        return -1;
    }

    argc = 0;
    argv = NULL;
    save = NULL;
    delims = " \t\n";

    for (;;)
    {
        char *tok;
        tok = strtok_r(line, delims, &save);
        line = NULL; /* nas próximas iterações, passa NULL */

        if (tok == NULL)
        {
            break;
        }

        if (argc >= max_tokens)
        {
            int i;
            fprintf(stderr, "erro: muitos argumentos (limite = %d)\n", max_tokens);
            for (i = 0; i < argc; i++)
            {
                free(argv[i]);
            }
            free(argv);
            *argv_out = NULL;
            errno = E2BIG;
            return -1;
        }

        {
            char **tmp;
            tmp = realloc(argv, (size_t)(argc + 1) * sizeof(char *));
            if (tmp == NULL)
            {
                int i;
                perror("realloc");
                for (i = 0; i < argc; i++)
                {
                    free(argv[i]);
                }
                free(argv);
                *argv_out = NULL;
                return -1;
            }
            argv = tmp;
        }

        argv[argc] = strdup(tok);
        if (argv[argc] == NULL)
        {
            int i;
            perror("strdup");
            for (i = 0; i < argc; i++)
            {
                free(argv[i]);
            }
            free(argv);
            *argv_out = NULL;
            return -1;
        }
        argc++;
    }

    {
        char **tmp;
        tmp = realloc(argv, (size_t)(argc + 1) * sizeof(char *));
        if (tmp == NULL)
        {
            int i;
            perror("realloc");
            for (i = 0; i < argc; i++)
            {
                free(argv[i]);
            }
            free(argv);
            *argv_out = NULL;
            return -1;
        }
        argv = tmp;
    }
    argv[argc] = NULL;

    *argv_out = argv;
    return argc;
}

static void free_argv_simple(int argc, char **argv)
{
    int i;
    if (argv == NULL)
    {
        return;
    }
    for (i = 0; i < argc; i++)
    {
        free(argv[i]);
    }
    free(argv);
}

/* =============================================================
 * Tabela de comandos e dispatcher
 * ============================================================= */
struct command
{
    const char *name;
    int (*func)(int argc, char *argv[]);
    const char *help;
};

/* Prototipos dos comandos da Fase 1 (todos stubs): */
static int cmd_cwd(int argc, char *argv[]);    /* getcwd */
static int cmd_cd(int argc, char *argv[]);     /* chdir */
static int cmd_mkdir_(int argc, char *argv[]); /* mkdir */
static int cmd_rmdir_(int argc, char *argv[]); /* rmdir */
static int cmd_stat_(int argc, char *argv[]);  /* stat/lstat */
static int cmd_ls(int argc, char *argv[]);     /* opendir/readdir/closedir */
/* "exit" será tratado diretamente no dispatcher (sem implementação aqui). */
/* Opcional: implementar "help" como exercício também. */
static int cmd_help(int argc, char *argv[]); /* imprimir lista de comandos */

static struct command commands[] = {
    {"help", cmd_help, "Mostra esta ajuda (a ser implementada)"},
    {"cwd", cmd_cwd, "Imprime diretório atual"},
    {"cd", cmd_cd, "Muda diretório atual: cd <dir>"},
    {"mkdir", cmd_mkdir_, "Cria diretório: mkdir <nome> [modo_oct]"},
    {"rmdir", cmd_rmdir_, "Remove diretório: rmdir <nome>"},
    {"stat", cmd_stat_, "Mostra estatísticas: stat <alvo>"},
    {"ls", cmd_ls, "Lista conteúdo do diretório atual"},
    {"exit", NULL, "Sai do minishell"}};

static const size_t NCOMMANDS = sizeof(commands) / sizeof(commands[0]);

enum
{
    DISPATCH_OK = 0,
    DISPATCH_EXIT = 1000
};

static int dispatch(int argc, char *argv[])
{
    size_t i;

    if (argc == 0)
    {
        return DISPATCH_OK;
    }

    for (i = 0; i < NCOMMANDS; i++)
    {
        if (strcmp(argv[0], commands[i].name) == 0)
        {
            if (commands[i].func == NULL)
            {
                /* comando especial "exit" tratado aqui */
                return DISPATCH_EXIT;
            }
            else
            {
                return commands[i].func(argc, argv);
            }
        }
    }

    fprintf(stderr, "Comando não encontrado: %s\n", argv[0]);
    return DISPATCH_OK;
}

/* =============================================================
 * STUBS (a serem implementados pelos alunos)
 * - Trocar o conteúdo por chamadas POSIX conforme cada comando
 * ============================================================= */
static int cmd_help(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    fprintf(stderr, "help: não implementado.\n");
    errno = ENOSYS;
    return 1;
}

static int cmd_cwd(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    char path[4096];
    if (argc != 1)
    {
        perror("argumento inválido");
        return -1;
    }
    getcwd(path, sizeof(path));
    printf("o seu diretório é %s\n: ", path);
    errno = ENOSYS;
    return 2;
}

static int cmd_cd(int argc, char *argv[])
{
    /* TODO: validar argc e chamar chdir(argv[1]) */
    (void)argc;
    (void)argv;

    if (argc != 2)
    {
        perror("argumento inválido: insira um endereço válido");
        return -1;
    }

    if (chdir(argv[1]) != 0)
    {
        perror("Erro ao mudar de diretório");
        return -1;
    }

    printf("Diretório alterado para: %s\n", argv[1]);
    return 0;
}

static int cmd_mkdir_(int argc, char *argv[])
{
    /* TODO: usar mkdir(argv[1], modo). Se não fornecer modo, usar 0777 (respeita umask) */
    (void)argc;
    (void)argv;

    if (argc != 2)
    {
        perror("argumento inválido: insira um nome de endereço");
        return -1;
    }

    if(mkdir(argv[1],0777)!=0){
        perror("Erro ao criar diretório");
        return -1;
    }

    printf("diretório criado com sucesso\n");
}

static int cmd_rmdir_(int argc, char *argv[])
{
    /* TODO: usar rmdir(argv[1]) */
    (void)argc;
    (void)argv;
    fprintf(stderr, "rmdir: não implementado. uso: rmdir <nome>\n");
    errno = ENOSYS;
    return 2;
}

static int cmd_stat_(int argc, char *argv[])
{
    /* TODO: usar lstat(argv[1], &st) e imprimir tipo, modo, tamanho etc. */
    (void)argc;
    (void)argv;
    fprintf(stderr, "stat: não implementado. uso: stat <alvo>\n");
    errno = ENOSYS;
    return 2;
}

static int cmd_ls(int argc, char *argv[])
{
    /* TODO: usar opendir("."), readdir(), imprimir nomes e closedir() */
    (void)argc;
    (void)argv;
    fprintf(stderr, "ls: não implementado.\n");
    errno = ENOSYS;
    return 1;
}

/* =============================================================
 * Loop principal
 * ============================================================= */
int main(void)
{
    char linha[4096];

    for (;;)
    {
        char **argv;
        int argc;
        int rc;

        fputs("minishell> ", stdout);
        fflush(stdout);

        if (fgets(linha, sizeof(linha), stdin) == NULL)
        {
            putchar('\n');
            break;
        }

        if (linha[0] == '\0' || linha[0] == '\n')
        {
            continue;
        }

        argv = NULL;
        argc = parse_line_simple(linha, &argv, 64);
        if (argc < 0)
        {
            /* erro já reportado */
            continue;
        }

        if (argc == 0)
        {
            free(argv);
            continue;
        }

        rc = dispatch(argc, argv);
        free_argv_simple(argc, argv);

        if (rc == DISPATCH_EXIT)
        {
            break;
        }
    }

    return 0;
}
