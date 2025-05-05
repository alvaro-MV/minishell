#include "parser.h"

void	print_AST(t_cmd_pipe *sequence); //testeo
void	buffer_AST(t_cmd_pipe *sequence, char **AST); //testeo

t_token	*parse_word(t_token **token_stream)
{
	t_token	*ret_token;

	ret_token = (*token_stream);
	if (ret_token->type != FILENAME && ret_token->type != END)
		return (NULL);
	if ((*token_stream)->type != END)
		(*token_stream)++;
	return (ret_token);
}

int	add_command(command **cmd, char *element, t_dictionary *env, int exp)
{
	char	**split;
	int		i;
	char	*expanded_cmd;
	char	*append_arg;

	(void) exp;
	i = -1;
	if (!element || (element && element[0] != '$')
		|| (element && element[0] == '$' && exp))
	{
		if (!append_darray(cmd, &element))
			return (0);
		return (1);
	}
	else
	{
		expanded_cmd = expand_str(element, env);
		if (!expanded_cmd)
			return (0);
		split = ft_split(expanded_cmd, ' ');
		if (!split)
			return (free(expanded_cmd), 0);
		while (split[++i])
		{
			append_arg = ft_strdup(split[i]);
			if (!append_darray(cmd, &append_arg))
				return (free(expanded_cmd), ft_free_array(split), 0);
		}
		(free(expanded_cmd), ft_free_array(split));
	}
	return (1);
}

void	print_from_diff(char *AST, char *expected)
{
	int	i;

	i = 0;
	while (AST[i] == expected[i] && AST[i] != '\0' && expected[i] != '\0')
		i++;
	ft_printf("A: %s\n", &AST[i]);
	ft_printf("e: %s\n", &expected[i]);
}

// void tester_parser(char *line, char *expected, int n)
// {
// 	t_darray	*tokens_array;
// 	char		**tokens_strings;
// 	t_token		*token_stream;
// 	char		*AST = ft_strdup("");

// 	ft_printf("[%d]: ", n);
// 	tokens_array = tokenizer_str(line);
// 	tokens_strings = (char **) tokens_array->darray;
// 	token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);

// 	//i = 0;
// 	//while (token_stream[i].type != END)
// 	//{
// 		//printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
// 		//i++;
// 	//}

// 	t_token	*tokens_for_free = token_stream;
// 	t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
// 	if (sequence)
// 	{
// 		print_AST(sequence);
// 		buffer_AST(sequence, &AST);

// 		if (!ft_strcmp(AST, expected))
//  			ft_printf("\033[32m%l[OK]\n\033[0m");
// 		else
// 		{
//  			ft_printf("\033[31m%l[KO]\n\033[0m");
// 			ft_printf("----------------------------\n");
// 			print_from_diff(AST, expected);
// 			ft_printf("----------------------------\n");
// 		}
// 	}

// 	free(AST);
// 	free_AST(sequence);
// 	free(tokens_array);
// 	free(tokens_for_free);
// 	ft_free_array(tokens_strings);
// }

// int	main(void)
// {
// 	tester_parser("ls | cat", "{ ls } | \n{ cat } ", 1);
// 	tester_parser("ls | cat | echo Hola", "{ ls } | \n{ cat } | \n{ echo Hola } ", 2);
	// tester_parser("export | sort | grep -v SHLVL | grep -v \"declare -x _\" | grep -v \"PS.=\"", 
	// 	"{ export } | \n{ sort } | \n{ grep -v SHLVL } | \n{ grep -v \"declare -x _\" } | \n{ grep -v \"PS.=\" } ", 3);
// 	tester_parser("echo hi | \"|\"", "{ echo hi } | \n{ \"|\" } ", 4);
// 	tester_parser("\"			\"", "{ \"			\" } ", 5);
// 	tester_parser("cat <\"./whatever\" >\"./whatever\"", "(< \"./whatever\") (> \"./whatever\") { cat } ", 6);
// 	tester_parser("\"ECho\" -n -nnn\"\" \"-\"nnnnn", "{ \"ECho\" -n -nnn\"\" \"-\"nnnnn } ", 7);
// 	tester_parser(">| echo sure", "minishell: syntax error near unexpected token", 8);
// 	tester_parser("<<| echo wtf", "(<< |) | \n{ echo wtf } ", 9);
// 	tester_parser("echo | |", "minishell: syntax error near unexpected token", 10);
// 	tester_parser("echo \"<| echo wtf\"", "{ echo \"<| echo wtf\" } ", 11);
// 	tester_parser("| | |", "minishell: syntax error near unexpected token", 12);
// 	tester_parser("|", "minishell: syntax error near unexpected token", 12);
// 	tester_parser(">> >> >> >>", "minishell: syntax error near unexpected token >>", 13);
// 	tester_parser("< >", "minishell: syntax error near unexpected token >", 14);
// 	tester_parser("<>", "minishell: syntax error near unexpected token >", 15);
// 	tester_parser("/bin/env | grep \"SHLVL\"", "{ /bin/env } | \n{ grep \"SHLVL\" } ", 16);
// 	tester_parser("echo hi >./test_files/invalid_permission | echo bye", "(> ./test_files/invalid_permission) { echo hi } | \n{ echo bye } ", 17);
// 	tester_parser("cat << lim''", "(<< lim'') { cat } ", 18);
// 	tester_parser("echo \"env | /usr/bin/wc -l\" | env -i $minishell_path\"/\"$executable", 
// 		"{ echo \"env | /usr/bin/wc -l\" } | \n{ env -i $minishell_path\"/\"$executable } ", 19);
// 	tester_parser("echo >>< 'echo'", "minishell: syntax error near unexpected token <", 20);
// 	tester_parser("echo segfault < \" < < < \" < < amazing", "minishell: syntax error near unexpected token <", 21);
// 	tester_parser("<'<'>hola>hola2 cat", "(< '<') (> hola) (> hola2) { cat } ", 22); //En este caso el cat lee, en vez de salir completamente de la ejecución o pasar a la siguiente pipe.
// 	tester_parser("<'>>' echo hola", "(< '>>') { echo hola } ", 23);
// 	tester_parser("<'<'cat>hola>hola2", "(< '<'cat) (> hola) (> hola2) { } ", 24); //En este caso tendría que salir con sytax error y pirarse.
// 	tester_parser("< infile", "(< infile) { } ", 25);
// 	tester_parser("<< $INEXISTENTE", "(<< $INEXISTENTE) { } ", 26);
// 	tester_parser("< README.md cat > outfile", "(< README.md) (> outfile) { cat } ", 27);
// 	tester_parser(">'<'>hola>hola2", "(> '<') (> hola) (> hola2) { } ", 28);
// 	tester_parser("cat <./test_files/infile_big ./test_files/infile", "(< ./test_files/infile_big) { cat ./test_files/infile } ", 29);
// }
