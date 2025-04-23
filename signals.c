#include "minishell.h"



// FUNCIONAN DE MANERA DIFERENTE EN LA TERMINAL QUE EN EL HEREDOC



// // funcion permitida signal
// // signal(SIGINT, manejador_para_ctrl_c);  // Captura Ctrl+C


// // FUNCION main:
// //     // Configurar manejadores de señales
// //     CONFIGURAR manejador para SIGINT (Ctrl+C): Llamar a handle_sigint
// //     CONFIGURAR manejador para SIGQUIT (Ctrl+\): Llamar a handle_sigquit
// //     ENTRAR en un bucle para leer entradas:
// //         LEER entrada del usuario
// //         SI entrada es EOF (Ctrl+D):
// //             IMPRIMIR mensaje "exit"
// //             TERMINAR el shell
// //         PROCESAR el comando normalmente

// // FUNCION handle_sigint:
// //     IMPRIMIR una nueva línea (esto equivale a simular un prompt vacío)

// // FUNCION detectar_ctrl_d:
// //     SI resultado de lectura es NULL:
// //         IMPRIMIR "exit"
// //         TERMINAR el shell

// // FUNCION handle_sigquit:
// //     NO HACER NADA (ignorar SIGQUIT)


// // Manejador para SIGINT (Ctrl+C)
void handle_sigint(int sig)
{
    (void)sig; // Ignorar la variable 'sig'
    write(1, "\n", 1); // Imprimir una nueva línea
    rl_on_new_line(); // Preparar readline para mostrar el prompt en una nueva línea
    rl_replace_line("", 0); // Limpiar la línea actual
    rl_redisplay(); // Mostrar el nuevo prompt
}

// Manejador para SIGQUIT (Ctrl+\)
void handle_sigquit(int sig)
{
    (void)sig; // Ignorar SIGQUIT, no hacemos nada
}

// Función principal del shell
void signals(char **input)
{
    // char *input;

    // Configurar manejadores de señales
    signal(SIGINT, handle_sigint);  // Capturar Ctrl+C
    signal(SIGQUIT, handle_sigquit); 

    // Bucle principal para el shell interactivo
    // while (1)
        *input = readline("minishell> "); // Mostrar prompt y leer entrada

        // Manejar Ctrl+D (EOF)

        if (!*input) // Si readline devuelve NULL, se presionó Ctrl+D
        {
            ft_printf("exit\n");
            exit (0); // Terminar el bucle y cerrar el shell
        }

        // Si se proporciona una entrada válida, agregarla al historial
        if (**input)
            add_history(*input);

        // Procesar el comando (puedes implementar tu lógica aquí)
        //ft_printf("Comando: %s\n", input); // Por ahora, simplemente imprime el comando

        // Liberar la memoria de readline
        // free(input);
}



// SIGINT: Se activa con Ctrl+C.

// SIGQUIT: Se activa con Ctrl+\.

// SIG_IGN: Usada para ignorar señales, como harás con SIGQUIT.

// readline() o getchar():
// Detectan EOF (Ctrl+D) porque devuelven NULL o -1.

// signal(int signum, void (*handler)(int)):
// Configura un manejador para una señal específica (SIGINT, SIGQUIT).
