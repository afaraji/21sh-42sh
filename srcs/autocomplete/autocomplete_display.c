/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_display.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:30:33 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/04 14:27:51 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <autocomplete/autocomplete.h>

static char	*autocomplete_disp_one(t_string *string)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!string || !string->s)
		return ("");
	if (!ft_strchr(string->s, '/'))
		return (string->s);
	ret = string->s;
	while (string->s[i] && i < string->len - 2)
	{
		if (string->s[i] == '/')
			ret = &string->s[i + 1];
		i++;
	}
	return (ret);
}

void		autocomplete_display(t_array *content)
{
	size_t		i;
	t_string	*tmp;

	if (!content || !content->used)
		return ;
	i = 0;
	default_terminal_mode();
	if (!content)
		return ;
	ft_putstr("\n");
	if (content->used > 42)
		ft_printf("%s: too many possibilities (%d possibilities)", PROGNAME,\
				content->used);
	while (content->used <= 42 && i < content->used)
	{
		tmp = (t_string *)array_get_at(content, i);
		if (tmp && tmp->s)
			ft_printf(" %s ", autocomplete_disp_one(tmp));
		i++;
	}
	ft_printf("\n");
	autocomplete_display_prompt(g_input);
	raw_terminal_mode();
}