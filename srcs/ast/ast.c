/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 09:47:39 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/07 20:04:29 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast/ast.h>

/*
** @brief Creates the ast
**
** Calls the ast_built function which will build the ast based on user input
** and tokens generated by the lexer.\n
** The limit lim set by the ast_create function is arbitrary (?TODO)
**
** @param expands Contains the token array
**
** @return Returns the ast in its final form, created from the tokens
**
** act_create may also return NULL if the ast failed to build due to a malloc
** error,\n
** Or whatever else may happen down the chain. (cf. ast_built)
*/

t_return		ast_create(t_btree **ast, t_array *expands)
{
	t_lim		lim;

	lim.cnt = 0;
	lim.lim = 10000;
	ast_built(ast, expands, lim, 1);
	log_dbg1("Ast created.");
	return (E_RET_AST_OK);
}
