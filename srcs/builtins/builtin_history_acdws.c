/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_acdws.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 12:53:12 by gpouyat           #+#    #+#             */
/*   Updated: 2017/10/10 19:21:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins/builtin_history.h>

/*
** @brief th option -a  Append the ``new'' history lines
**(history lines entered since the beginning
**of the current bash session) to the history file.
**
** @param str is filename
*/

void	sh_history_builtin_a(char *str)
{
	t_array	*hists;
	t_hist	*h;
	int		fd;
	size_t	i;

	i = 0;
	if ((fd = open(history_get_path(str), O_RDWR | O_CREAT | O_APPEND, 0644))\
			== -1)
	{
		log_warn("History: History was not save no open");
		ft_putstr_fd("History was not save", 2);
		return ;
	}
	if ((hists = sh_history_get()) == NULL)
		return ;
	while (i < hists->used)
	{
		h = (t_hist *)array_get_at(hists, i);
		if (h->session == true)
			ft_dprintf(fd, "%s\n", h->cmd);
		i++;
	}
	sh_history_var_session_reset();
}

/*
** @brief Clear the history list by deleting all the entries.
*/

void	sh_history_builtin_c(void)
{
	t_array		*hist;

	ft_printf("clear history\n");
	hist = sh_history_get();
	while (hist && hist->used)
		hist = array_pop(hist, NULL);
}

/*
** @brief th option -d Delete the history entry at position offset.
**
** @param arg The args passed to history (offset)
*/

void	sh_history_builtin_d(const char *arg)
{
	int			nb;
	t_array		*hists;

	nb = -1;
	hists = sh_history_get();
	if (!hists)
		return ;
	if (ft_isdigit(arg[0]))
		nb = ft_atoi(arg) - 1;
	if (nb == -1 || sh_history_remove_at((size_t)nb) == NULL)
		ft_printf("%s: history: %s: history position out of range\n",
																PROGNAME, arg);
}

/*
** @brief th option -w  Write the current history to the history file,
** overwriting the historyfile's contents.
**
** @param path is filename
*/

void	sh_history_builtin_w(char *path)
{
	t_array	*hists;
	t_hist	*h;
	int		fd;
	size_t	i;

	i = 0;
	if ((fd = open(history_get_path(path), O_RDWR | O_CREAT, 0644)) == -1)
	{
		log_warn("History: History was not save no open");
		ft_putstr_fd("History was not save", 2);
		return ;
	}
	if ((hists = sh_history_get()) == NULL)
		return ;
	while (i < hists->used)
	{
		h = (t_hist *)array_get_at(hists, i);
		ft_dprintf(fd, "%s\n", h->cmd);
		i++;
	}
	close(fd);
}

/*
** @brief th option -s Store the args in the history list as a single entry.
** The last  command in the history list is removed before the args are added.
**
** @param path is filename
*/

void	sh_history_builtin_s(char **argv, int index)
{
	char	*cmd_join;
	char	*tmp;

	cmd_join = NULL;
	while (argv[index] && ft_isalnum(argv[index][0]))
	{
		if (cmd_join && !(cmd_join = ft_strjoincl(cmd_join, " ", 1)))
			sh_exit_error("Malloc Error");
		if ((tmp = ft_strchr(argv[index], '\n')))
		{
			*tmp = 0;
			cmd_join = ft_strjoincl(cmd_join, argv[index], 1);
			cmd_join = ft_strjoincl(cmd_join, "\\\n", 1);
			tmp++;
			cmd_join = ft_strjoincl(cmd_join, tmp, 1);
		}
		else
			cmd_join = ft_strjoincl(cmd_join, argv[index], 1);
		index++;
	}
	if (cmd_join && sh_history_get())
		sh_history_remove_at(sh_history_get()->used - 1);
	sh_history_set_new(&cmd_join);
}
