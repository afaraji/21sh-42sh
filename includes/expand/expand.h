/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 14:57:29 by guiforge          #+#    #+#             */
/*   Updated: 2017/07/06 17:18:53 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EXPAND_H__
# define __EXPAND_H__

#include <lexer/lexer.h>
#include <core/main.h>

typedef struct s_exp
{
	char 			    *str;
	t_token_type	type;
}               t_exp;

t_array *expand(t_array *tokens, t_array *array_exp);
t_array	*expand_init(t_array *expand_array);
t_exp *exp_create_new(t_token *tok);
void sh_expand_destroy(t_array *array_exp);
void expand_print(t_array *array_exp);
void sh_exp_del(void *i);
char	*ft_replace(char *src1, char *src2, int index, int size);

t_array *expand_exp(t_array *tokens, t_array **tokens_expended);
//t_array	*expand_init(t_array **tokens_expended);

void	test(t_array *toks);

#endif
