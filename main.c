#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <editline/readline.h>
#include <readline/history.h> // Include this header for add_history

int main() {
    char *line;

	while ((line = readline("> ")))
	{
		printf("La línea ingresada es: %s\n", line);
		add_history(line);
		free(line);
	}
	rl_clear_history();
    return 0;
}


