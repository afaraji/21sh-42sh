/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:28:56 by chbravo-          #+#    #+#             */
/*   Updated: 2017/07/20 16:14:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <history/history.h>

/*
** @brief Helps initialize the history
** @param hists The t_array containing the history
** @param fd The fd of the history file
** @return Returns an appropriate return value (0|1) concording to the function
*/

int		sh_history_init_one(t_array *hists, int fd)
{
	t_hist	*h;
	char	*line;
	char	*cmd;
	int		ret;

	cmd = NULL;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) && line && ft_strlen(line) > 0
		&& (line[ft_strlen(line) - 1] == '\\'))
	{
		cmd = (cmd ? ft_strjoincl(cmd, "\n", 1) : cmd);
		cmd = ft_strjoincl(cmd, line, 3);
	}
	if (cmd && line)
		cmd = ft_strjoincl(cmd, "\n", 1);
	cmd = ft_strjoincl(cmd, line, 3);
	if ((h = sh_history_new(cmd)))
	{
		h->session = false;
		array_push(hists, (void *)h);
		ft_memdel((void **)&h);
	}
	else
		ft_strdel(&cmd);
	return (ret);
}

/*
** @brief Saves the choice you made if your history file is to big
**
** @param choice The number you've entered
**
** @return Returns a number between 1 and 5 if your choice is one of those.
** An error will be displayed if the number isnt between 1 and 5
*/

int		get_history_init_choice(int choice)
{
	static int save_choice = -1;

	if (choice <= 5 && choice >= 1)
		save_choice = choice;
	return (save_choice);
}

/*
** @brief Prints the choice Text User Interface
**
** @param limit The limit in bytes
*/

void	sh_history_print_choice(int limit)
{
	ft_dprintf(STDERR_FILENO, "%s: The history file is too big (%d/%d bytes)\n"
			"\t (1): Delete and create a new one\n"
			"\t (2): Save the file somewhere and create a new file\n\n"
			"\t ### DANGEROUS CHOICES ###\n"
			"\t (3): Force load, save the current file and create a new one\n"
			"\t (4): Force load and delete\n \t (5): Force load\n\n"
			"\t (?): Default: (1)\n", PROGNAME, limit, HISTORY_FILE_MAX);
}

/*
** @brief Initializes the history and diplay the choices
** @param fd The fd of the history file
** @param limit The limit in bytes
** @return Returns the fd of the file
*/

int		sh_history_init_choice(int fd, int limit)
{
	char *line;

	line = NULL;
	if (!isatty(STDIN_FILENO))
		return (open(history_get_path(NULL), O_RDWR | O_CREAT | O_TRUNC, 0644));
	sh_history_print_choice(limit);
	ft_putstr_fd(">", STDIN_FILENO);
	get_next_line(0, &line);
	get_history_init_choice(ft_atoi(line));
	if (ft_strequ(line, "2") || ft_strequ(line, "3"))
	{
		while (42)
		{
			ft_strdel(&line);
			ft_putstr_fd("Path ? (q == exit): ", STDIN_FILENO);
			get_next_line(0, &line);
			if (ft_strequ(line, "q") || !rename(history_get_path(NULL), line))
				break ;
			ft_putstr_fd("This path doesn't exists\n", STDERR_FILENO);
		}
	}
	ft_strdel(&line);
	if (get_history_init_choice(-1) <= 3)
		return (open(history_get_path(NULL), O_RDWR | O_CREAT | O_TRUNC, 0644));
	return (fd);
}

/*
** @brief Initializes the history module
**
** @param hists The t_array containing the history
**
** @return Returns the history array initialized
*/

t_array	*sh_history_init(t_array *hists)
{
	int			fd;
	struct stat bufstat;

	if (!(hists = sh_history_get()))
		return (NULL);
	if ((fd = open(history_get_path(NULL), O_RDWR | O_CREAT, 0644)) == -1)
		return (NULL);
	if (stat(history_get_path(NULL), &bufstat))
		return (NULL);
	if (bufstat.st_size >= HISTORY_FILE_MAX)
		fd = sh_history_init_choice(fd, (int)bufstat.st_size);
	if (fd == -1)
		return (NULL);
	log_dbg3("HISTORY init: choice = %d", get_history_init_choice(-1));
	if (get_history_init_choice(-1) >= 3)
		ft_putendl_fd("Force load, Be patient ;)", STDERR_FILENO);
	while (sh_history_init_one(hists, fd))
	{
		if (hists->used >= HISTORY_MAX)
			sh_history_remove_at(0);
	}
	close(fd);
	return (hists);
}
