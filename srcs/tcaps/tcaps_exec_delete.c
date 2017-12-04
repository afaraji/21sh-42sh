/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_exec_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 13:04:39 by chbravo-          #+#    #+#             */
/*   Updated: 2017/09/18 21:49:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/tcaps.h>

static BOOL		exec_delete2(void)
{
	tcaps_bell();
	tputs(tgetstr("vb", NULL), 0, &ft_putc_in);
	return (false);
}

BOOL			exec_delete(const t_key *key, t_input *input)
{
	t_window	*wd;
	size_t		pos;
	t_input		*del;

	(void)key;
	if (!(wd = get_windows(0)))
		return (false);
	if ((wd->autocomp && wd->autocomp->active))
		return (false);
	if (get_select()->is)
		return (false);
	log_dbg1("exec delete.");
	pos = pos_in_str(input);
	if (input->str->len > pos)
		string_remove_char(input->str, pos);
	else if (input->str->len == pos && input->next)
	{
		input->str = string_join_cl(&input->str, &input->next->str, true);
		del = input->next;
		input->next = del->next;
		if (input->next)
			input->next->prev = input;
		del->next = NULL;
		input_destroy(&del);
	}
	else
		return (exec_delete2());
	redraw_input(input);
	return (false);
}
