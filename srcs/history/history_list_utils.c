/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:00:49 by gpouyat           #+#    #+#             */
/*   Updated: 2017/06/13 14:11:03 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <history/history.h>

t_hist	*sh_history_new(char *cmd)
{
	t_hist	*h;

	if(sh_history_is_space_plus(cmd) || !sh_history_is_print(cmd))
		return (NULL);
	if ((h = ft_memalloc(sizeof(*h))) == NULL)
	{
		log_fatal("History: can't create new history command");
		ft_dprintf(STDERR_FILENO,"History: can't create new history command");
	}
	else if ((h->cmd = cmd) == NULL)
	{
		log_fatal("History: can't create new history command");
		ft_dprintf(STDERR_FILENO,"History: can't create new history command");
		ft_memdel((void**)&h);
	}
	h->buf = NULL;
	h->cur = -1;
	return (h);
}

void sh_history_del(void *i)
{
	t_hist *h;

	h = (t_hist *)i;
	if (h->cmd)
		ft_strdel(&(h->cmd));
	if (h->buf)
		ft_strdel(&(h->buf));
}

void sh_history_insert_buf(char *str)
{
	t_array	*hists;
	t_hist	*h;

	hists = sh_history_get();
		if ((h = (t_hist *)array_get_at(hists, 0)))
		{
			if (h->buf)
				ft_strdel(&(h->buf));
				h->buf = ft_strdup(str);
			h->cur = -1;
		}
}

void sh_history_destroy(void)
{
	t_array	*hists;

	if ((hists = sh_history_get()) != NULL)
		array_destroy(&hists, sh_history_del);
}

void	sh_history_var_session_reset(void)
{
	t_array	*hists;
	t_hist	*h;
	size_t	i;

	i = 0;
	if ((hists = sh_history_get()) == NULL)
		return ;
		while (i < hists->used && (h = (t_hist *)array_get_at(hists, i)))
		{
			h->session = false;
			i++;
		}
}