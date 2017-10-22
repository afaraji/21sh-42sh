/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_exec_arrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:57:33 by chbravo-          #+#    #+#             */
/*   Updated: 2017/07/12 15:51:49 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/tcaps.h>
#include <core/input.h>
#include <history/history.h>

BOOL	exec_arrow_right(const t_key *key, t_input *input)
{
	struct winsize	*ts;
	t_select		*sel;

	log_dbg1("exec arrow right.");
	ts = get_ts();
	sel = get_select();
	if (((size_t) (input->cpos.cp_col + (input->offset_line  * ts->ws_col) - input->offset_col)) < input->str->len)
	{
		exec_select_arrows(key, input, "right");
		if (input->cpos.cp_col + 1 == ts->ws_col)
			input->offset_line += 1;
		move_cursor_right(&input->cpos, ts);
		if (sel->is)
			sel->cur_end = pos_in_str(input);
	}
	sh_history_insert_buf(input->str->s);
	return (false);
}

BOOL	exec_arrow_left(const t_key *key, t_input *input)
{
	struct winsize	*ts;
	t_select		*sel;

	log_dbg1("exec arrow left.");
	ts = get_ts();
	sel = get_select();
	if (((input->cpos.cp_col + ((input->offset_line ) * ts->ws_col) - input->offset_col)) > 0)
	{
		exec_select_arrows(key, input, "left");
		if (input->cpos.cp_col == 0)
			input->offset_line -= 1;
		move_cursor_left(&input->cpos, ts);
		if (sel->is)
			sel->cur_end = pos_in_str(input);
	}
	sh_history_insert_buf(input->str->s);
	return (false);
}

BOOL	exec_arrow_up(const t_key *key, t_input *input)
{
	(void)input;
	(void)key;
	log_dbg1("exec arrow up.");
	//TODO add history
	//tputs(tgetstr(key->key_code, NULL), 0, &ft_putchar2);
	//sh_history_up(input);
//	history_get_up();
	//redraw_line(input);
	return (false);
}

BOOL	exec_arrow_down(const t_key *key, t_input *input)
{
	(void)input;
	(void)key;
	log_dbg1("exec arrow down.");
	//TODO add history
	//tputs(tgetstr(key->key_code, NULL), 0, &ft_putchar2);
	sh_history_down(input);
	//redraw_line(input);
	return (false);
}
