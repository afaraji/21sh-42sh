/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 09:59:15 by gpouyat           #+#    #+#             */
/*   Updated: 2017/06/20 22:03:19 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/ast_tests.h>

void sh_testing_ast(char *const *av)
{
	t_btree	*ast;
	t_automaton	automaton;
	t_array		tokens;
	char *input;

	input = ft_strclean(av[3]);//TODO à faire pour le main ;)
	ast = NULL;
	if (lexer_init(&tokens) == NULL)
	{
			ft_printf("Error initialising tokens");
			exit (1);
	}
	else if (automaton_init(&automaton) == NULL)
	{
			ft_printf("Error Initialising automaton");
			exit (1);
	}
	else if (lexer_lex(&tokens, &automaton, input))
	{
			if(parser_parse(&tokens))
			{
				if (!(ast = ast_create(&tokens)))
					ft_printf("AST NULL\n");
				else
					btree_print(ast, (char * (*)(void*))&ast_aff);
				btree_destroy(&ast, (void (*) (void*))&ast_del_cmd);
				free(input);
				exit (0);
			}
			exit (1);
	}
	else
	{
			ft_printf("Fatal testing error : Couldn't Catch the error.");
			exit (1);
	}
}
