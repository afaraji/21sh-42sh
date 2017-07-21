/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secu_malloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 19:56:25 by gpouyat           #+#    #+#             */
/*   Updated: 2017/07/21 15:10:10 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ft_secu_malloc_H
# define ft_secu_malloc_H

#include <libft.h>

# define MALLOC_LVL_DEFAULT 0
# define MALLOC_LVL_FUNCTION 1
# define M_LVL_AST 3

struct          s_secu_malloc
{
	void                  *ptr;
	size_t								lvl;
	struct s_secu_malloc        *prev;
	struct s_secu_malloc        *next;
};

typedef struct s_secu_malloc t_secu_malloc;

typedef struct          s_mem
{
	t_secu_malloc             *first;
	t_secu_malloc             *last;
}                       t_mem;


t_mem *get_mem(void);
void *ft_secu_malloc_lvl(size_t size, size_t lvl);
void ft_secu_free_lvl(size_t lvl);
void *ft_secu_malloc(size_t size);
void ft_secu_free(void *ptr);
void ft_secu_free_all(void);

# define MALLOC(x) ft_secure_malloc(x)
# define FREE(x) ft_secure_free(x)
# define FREE_LVL(x) ft_secure_free_lvl(x)

#endif
