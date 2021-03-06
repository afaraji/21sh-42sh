/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 10:09:19 by chbravo-          #+#    #+#             */
/*   Updated: 2017/10/10 18:15:48 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/init.h>
#include <libft.h>
#include <tests/sh_tests.h>
#include <core/help.h>
#include <sys/param.h>

extern char const	*g_optarg;

/*
** @brief     This function is called when a test is needed on one module
**
** @param[in] arg      Contains the module name to be tested
** @param[in] av       Contains the parameters needed for the test function
** @param[in] environ  Contains the env (Used when needed by the testing\
**                                        functions)
*/

void				sh_testing(const char *arg, char *const *av, char **environ)
{
	if (ft_strequ(arg, "env"))
		sh_testing_env(av, environ);
	else if (ft_strequ(arg, "lexer"))
		sh_testing_lexer(av);
	else if (ft_strequ(arg, "parser"))
		sh_testing_parser(av);
	else if (ft_strequ(arg, "ast"))
		sh_testing_ast(av, environ);
	else if (ft_strequ(arg, "expand"))
		sh_testing_expand(av, environ);
	else if (ft_strequ(arg, "var"))
		testing_local_vars(av, environ);
	else
	{
		ft_dprintf(STDERR_FILENO, "Unknown testing arg. %s\n", arg);
		sh_usage_help_exit();
	}
}

/*
** @brief     Initializes the program
**
** @param[in] data     Contains data such as options and env
** @param[in] ac       Argument count for av
** @param[in] av       Contains the arguments
** @param[in] environ  Contains the env
**
** @return    the modified t_sh_data
*/

static void			sh_multi_init(t_sh_data *data, int ac, char *const *av,
									char **environ)
{
	if (!data)
	{
		ft_dprintf(STDERR_FILENO, "%s: ERROR Intern Data is Empty\n", PROGNAME);
		return (sh_exit(NULL, NULL));
	}
	ft_bzero(data, sizeof(*data));
	sh_options(&(data->opts), ac, av, environ);
	init_environ(environ);
	init_local_var();
	sh_builtins_init();
	sh_history_init(sh_history_get());
	init_signals(&signals_handler);
	sh_store_tattr(data);
}

/*
** @brief Displays a message when the shell is started with `env -i`
*/

void				sh_check_env(char **environ)
{
	char	*tmp;

	tmp = NULL;
	if (!environ || !environ[0])
	{
		ft_dprintf(2, "%s: %sWarning%s, Starting without env may cause some "
		"features to not work proprelly.\n", PROGNAME, CL_RED, C_NONE);
		log_warn("was launched without an env provided. Using default.\n");
		set_var(get_envs(), "TERM", "xterm", true);
		set_var(get_envs(), "USER", "Marvin", true);
		set_var(get_envs(), "USERNAME", "Marvin", true);
		set_var(get_envs(), "PWD", (tmp = get_pwd()), true);
		ft_strdel(&tmp);
	}
	if (!(get_var(get_envs(), "SHLVL")) ||
							ft_strequ(get_var_value(get_envs(), "SHLVL"), ""))
		set_var(get_envs(), "SHLVL", "1", true);
	else
		set_var(get_envs(), "SHLVL",
				(tmp = ft_itoa(ft_atoi(get_var_value(
						get_envs(), "SHLVL")) + 1)), true);
	if (!(get_var(get_envs(), "TERM")))
		set_var(get_envs(), "TERM", "dump", true);
	ft_strdel(&tmp);
}

static BOOL			sh_init_get_path(char *const *argv)
{
	char		path_save[PATH_MAX];
	char		*p;
	t_sh_data	*data;

	if (!(data = get_data(NULL)))
		return (false);
	ft_bzero(data->cwd, sizeof(data->cwd));
	if (!(p = ft_strrchr(argv[0], '/')))
	{
		if (!getcwd(data->cwd, sizeof(data->cwd)))
			return (false);
	}
	else
	{
		*p = '\0';
		if (!getcwd(path_save, sizeof(path_save)) || chdir(argv[0]) ||
				!getcwd(data->cwd, sizeof(data->cwd)) || chdir(path_save))
			return (false);
	}
	return (true);
}

/*
** @brief     Initializes the program
**
** @param[in] data     Contains data such as options and env
** @param[in] ac       Argument count for av
** @param[in] av       Contains the arguments
** @param[in] environ  Contains the env
**
** @return    the modified t_sh_data
*/

t_sh_data			*sh_init(t_sh_data *data, int ac, char *const *av,
							char **environ)
{
	sh_multi_init(data, ac, av, environ);
	if (!sh_init_get_path(av))
		sh_exit_error("Error when getting current working directory");
	sh_check_env(environ);
	if ((tgetent(STDIN_FILENO, get_var_value(get_envs(), "TERM"))) != 1)
	{
		ft_dprintf(2, "%s: can't find terminal definition for %s.\n", PROGNAME,
				get_var_value(get_envs(), "TERM"));
		exit(EXIT_FAILURE);
	}
	tcaps_check_needed();
	log_info("INIT: DONE");
	return (data);
}
