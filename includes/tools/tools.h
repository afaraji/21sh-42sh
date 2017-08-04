/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 13:00:38 by gpouyat           #+#    #+#             */
/*   Updated: 2017/08/01 15:20:45 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <libft.h>
# include <ftprintf.h>
# include <btree/ft_btree.h>

void	ft_strdblfree(char **strdb);
BOOL  is_printstr(char const *line);
pid_t  sh_fork(void);
int    sh_pipe(int tube[2]);
int    sh_open_exec(t_btree *ast);
int    sh_open(char *file, int flags);
int    sh_ret(int status);
BOOL  ft_isdigit_str(char *str);
char	*ft_strnew_secu(size_t size, size_t lvl);
char		*ft_strsub_secu(char const *s, unsigned int start, size_t len, size_t lvl);
char		**ft_strsplit_secu(char const *s, char c, size_t lvl);


#endif