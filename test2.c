#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"


int main(int argc, char **argv) {
    // Caminho para o programa a ser executado
    char *program;
    
    program = ft_strjoin("/bin/", argv[1]);
    // Argumentos para o programa (o primeiro é o próprio nome do programa)
    char *const args[] = { program, NULL };
    
    // Variáveis de ambiente (vazio neste exemplo)
    char *env[] = { NULL };

    // Executa o programa
    if (execve(program, args, env) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Este código só será alcançado se execve falhar
    printf("execve falhou.\n");

    return EXIT_SUCCESS;
}
