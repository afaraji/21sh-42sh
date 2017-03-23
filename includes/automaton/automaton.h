/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:50:20 by chbravo-          #+#    #+#             */
/*   Updated: 2017/03/05 09:25:37 by chbravo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <types/stack.h>

enum	e_stack_state
{
	E_STATE_NONE,
	E_STATE_ERROR,
	E_STATE_START,
	E_STATE_WORD,
	E_STATE_SQUOTE,
	E_STATE_BQUOTE,
	E_STATE_DQUOTE,
	E_STATE_SEMI
};

typedef uint32_t	t_stack_state;
typedef uint32_t	t_automaton_step;

enum 	e_automaton_step
{
	E_UNKNOWN,
	E_POP,
	E_PUSH
};

struct	s_automaton
{
	t_stack			*stack;
	t_stack_state	cur_state;
};

typedef struct s_automaton	t_automaton;

t_automaton *automaton_init(void);
void automaton_destroy(t_automaton **automaton);
void automaton_step(t_automaton	*a, t_stack_state state,t_automaton_step step);

#endif