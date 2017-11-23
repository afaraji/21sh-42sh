/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 13:20:29 by gpouyat           #+#    #+#             */
/*   Updated: 2017/11/15 19:24:48 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec/exec.h>

int	sh_pipe(int tube[2])
{
	if (pipe(tube) != 0)
	{
		ft_putstr_fd("Error creation of pipe.\n", 2);
		log_fatal("EXEC: ERROR, pipe file: %s");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
