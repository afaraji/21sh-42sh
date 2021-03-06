/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 09:59:15 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/14 14:58:10 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/sh_tests.h>

/*
** @brief Displays the ast for the test script to check
**
** @param cmd The ast to be displayed
*/

static void			test_aff(t_cmd *cmd)
{
	static int			i = 0;
	int					index;

	index = 0;
	ft_printf("[%d]{", i);
	while (cmd->av[index] && cmd->av[index + 1])
	{
		ft_printf("%s ", cmd->av[index]);
		index++;
	}
	if (cmd->av[index])
		ft_printf("%s", cmd->av[index], cmd->type);
	ft_putstr("} ");
	i++;
}

/*
** @brief Initializes the ast and lexer before the test starts
**
** @param input The input to be tested with the ast module
**
** @return Returns the token t_array containing the lexed input
*/

static t_array		init_tests_ast(char *input)
{
	t_automaton	automaton;
	t_array		tokens;

	if (ft_strlen(input) >= MAX_LEN_INPUT)
		sh_exit_printf("line is too long: %zu, MAX is %zu", ft_strlen(input),
					MAX_LEN_INPUT);
	else if (ft_strlen(input) && !is_printstr(input))
		sh_exit_printf("line: contains non-ascii characters.");
	if (lexer_init(&tokens) == NULL)
		sh_exit_error("Error initialising tokens");
	else if (automaton_init(&automaton) == NULL)
		sh_exit_error("Error Initialising automaton");
	else if (lexer_lex(&tokens, input))
	{
		if (automaton.stack)
			stack_destroy(&(automaton.stack), NULL);
		return (tokens);
	}
	else
		sh_exit_error("Fatal testing error : Couldn't Catch the error.");
	return (tokens);
}

/*
** @brief Main function to test the ast.
**
** @param av The args passed to the ast test
** @param environ The environ passed to the program
*/

void				sh_testing_ast(char *const *av, char **environ)
{
	t_btree		*ast;
	t_array		expands;
	t_array		tokens;
	char		*input;

	input = *av;
	ast = NULL;
	init_environ(environ);
	sh_history_init(sh_history_get());
	tokens = init_tests_ast(input);
	if (expand_init(&expands) == NULL)
		sh_exit_error("Expand init fail");
	expand(&tokens, &expands);
	if ((ast_create(&ast, &expands) != E_RET_AST_OK))
		ft_printf("AST NULL\n");
	else if (!av[1] || ft_strequ(av[4], "tree"))
		btree_print(ast, (char *(*)(void*))&ast_aff);
	else if (ft_strequ(av[1], "line"))
		btree_apply_prefix(ast, (void (*)(void*))&test_aff);
	exit(0);
}
