/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 10:44:56 by gpouyat           #+#    #+#             */
/*   Updated: 2017/07/21 14:58:47 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <secure_memory/secure_memory.h>

/*
** @file ft_btree.h
**
** @brief Function prototypes for the binary trees
**
** This contains the prototypes for the program,
** and eventually any macros, constants,
** or global variables you will need.
*/

/*
** @struct s_btree
**
** @brief  Contains the nodes for the binary tree
**
** @param  parent  Contains the parent btree node
** @param  left    Contains the left btree node
** @param  right   Contains the right btree node
** @param  item    Contains the item in the node
*/

typedef struct		s_btree
{
	struct s_btree	*parent;
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

/*
** @file   btree_apply.c
**
** @brief  Contains all the apply functions for prefix, suffix, and infix
*/

void				btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_infix(t_btree *root, void (*applyf)(void *));

/*
** @file   btree_create_node.c
**
** @brief  Contains functions to create and insert data in node
*/

t_btree				*btree_create_node(void *item);
void				btree_insert_data(t_btree **root, void *item,
									int (*cmpf)(void *, void *));

/*
** @file   btree_utils.c
**
** @brief  Utility functions for the binary tree
*/

int					btree_level_count(t_btree *root);
void				*btree_search_item(t_btree *root, void *data_ref,
									int (*cmpf)(void *, void *));
void				btree_destroy(t_btree **root, void (*del)(void *));

/*
** @file    btree_print.c
**
** @brief   Functions to print a binary tree
*/

void				btree_print(t_btree *this, char *(*applyf)(void *));

#endif
