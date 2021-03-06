/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 23:11:43 by chbravo-          #+#    #+#             */
/*   Updated: 2017/11/02 23:11:43 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/select.h>

void		display_word(t_sel_word *word, t_sel_display *dsp)
{
	t_cpos	dest;
	size_t	i;

	if (!word)
		return ;
	dest.cp_col = (USHRT)(((word->num - dsp->first->num) % dsp->col_num) *
														(dsp->col_size + 1));
	dest.cp_line = (USHRT)((word->num - dsp->first->num) / dsp->col_num);
	move_cursor_to(&dest, &dsp->cpos, &dsp->ts);
	display_print_word(word);
	dsp->cpos.cp_col += word->len;
	tcaps_video_underline(false);
	i = word->len;
	while (i++ < dsp->col_size)
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		dsp->cpos.cp_col += 1;
	}
	tcaps_video_default();
	ft_putstr_fd("\x1b[0m", STDIN_FILENO);
	ft_bzero(&dest, sizeof(dest));
	move_cursor_to(&dest, &dsp->cpos, &dsp->ts);
}

void		display_line(t_sel_word *lst, t_sel_display *dsp)
{
	size_t	i;

	while (lst->num % dsp->col_num)
		lst = lst->prev;
	i = lst->num + dsp->col_num;
	while (lst->num < i && lst->num < dsp->word_num)
	{
		display_word(lst, dsp);
		if (lst->num == dsp->word_num - 1)
			return ;
		lst = lst->next;
	}
}

static void	display_list_helper(t_sel_display *dsp)
{
	dsp->fixed_scroll = true;
	tputs(tparm(tgetstr("cs", NULL), 1, dsp->ts.ws_row), 1, &ft_putc_in);
	tputs(tparm(tgetstr("cm", NULL), 1, 0), 0, &ft_putc_in);
	dsp->cpos.cp_col = 0;
	dsp->cpos.cp_line = 0;
}

void		display_list(t_sel_word *lst, t_sel_display *dsp)
{
	t_sel_word	*save;

	if (!lst)
		return ;
	save = lst;
	display_word(lst, dsp);
	lst = lst->next;
	while (lst && lst != save)
	{
		if ((dsp->ts.ws_row - 1) <= (USHRT)(((lst->num - dsp->first->num) /
																dsp->col_num)))
		{
			if (!dsp->fixed_scroll)
			{
				display_list_helper(dsp);
			}
			return ;
		}
		display_word(lst, dsp);
		lst = lst->next;
	}
}

void		display_list_force(t_sel_word *lst, t_sel_display *dsp)
{
	t_sel_word	*head;
	size_t		i;
	size_t		j;

	if (!lst)
		return ;
	head = lst;
	head->prev->next = NULL;
	while (lst)
	{
		i = lst->num + dsp->col_num;
		while (lst && lst->num < i && lst->num < dsp->word_num)
		{
			display_print_word(lst);
			j = lst->len;
			while (j++ < dsp->col_size && dsp->col_num > 1)
				ft_putchar_fd(' ', STDIN_FILENO);
			lst = lst->next;
		}
		ft_putchar_fd('\n', STDIN_FILENO);
	}
	head->prev->next = head;
}
