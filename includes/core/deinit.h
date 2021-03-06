/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlasne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 16:00:24 by jlasne            #+#    #+#             */
/*   Updated: 2017/11/21 08:30:34 by jlasne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEINIT_H
# define DEINIT_H

# include "data.h"

/*
** @file   deinit.h
**
** @brief  Function prototypes for the deinit part of the program
**
** This contains the prototypes for the program,
** and eventually any macros, constants,
** or global variables you will need.
*/

/*
** @file       deinit.c
**
** @brief      Functions to uninitialize the program before exiting it
*/

int		sh_restore_tattr(struct termios *tattr);
void	sh_deinit(t_sh_data *data);

#endif
