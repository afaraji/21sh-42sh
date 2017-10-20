/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbravo- <chbravo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:28:12 by chbravo-          #+#    #+#             */
/*   Updated: 2017/10/02 15:40:24 by jlasne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/input.h>
#include <core/tcaps.h>
#include <tools/tools.h>
#include <history/history.h>

t_input *g_input;

BOOL			remove_escaped_newline(char **input)
{
	size_t	len;

	len = ft_strlen(*input);
	if (*(*input + len - 1) == '\\')
	{
		*(*input + len - 1) = '\0';
		return (true);
	}
	return (false);
}

/*
** @brief      Read the input on standard entry
**
** @return     A pointer to the input string
*/

/*
**char			*sh_get_line_old(void)
**{
**	char	*line;
**	char	*input;
**
**	input = NULL;
**	(void)get_next_line(0, &line);
**	input = ft_strjoincl(input, line, 3);
**	while (remove_escaped_newline(&input))
**	{
**		ft_printf(">");
**		(void)get_next_line(0, &line);
**		input = ft_strjoincl(input, line, 3);
**	}
**	if (*input != '\0')
**		return (input);
**	ft_strdel(&input);
**	return (NULL);
**}
*/

/*
**void			tcaps_down(t_input *input)
**{
**	tputs(tgetstr("do", NULL), 1, ft_putchar2);
**	input->offset_line += 1;
**	input->cpos.cp_line += 1;
**	tputs(tgetstr("cr", NULL), 1, ft_putchar2);
**	input->cpos.cp_col = 0;
**}
*/

/*
**"do" descends une ligne puis
**"cr" goto debut de ligne
*/

/*
**static void	tcaps_insert_char(char *c)
**  {
**  tputs(tgetstr("im", NULL), 0, &ft_putchar2);
**  tputs(c, 1, &ft_putchar2);
**  tputs(tgetstr("ie", NULL), 0, &ft_putchar2);
** }
*/

static void		draw_char(t_input *input, char *c)
{
	int		len;

	len = 0;
	if (c)
		len = ft_strlen(c);
	redraw_line(input);
	while (len--)
		exec_arrow_right(NULL, input);
}

/*
** si je suis au milieu de la string j'insert le char sinon je le write
**if (input->str->len > (((((input->ts.ws_col * input->offset_line) - \
**															input->offset_col)
**	  + (input->cpos.cp_col - 1 + input->offset_line )))))
**	  tcaps_insert_char(c);
**	  else
**	  tputs(c, 1, &ft_putchar2);
**	  input->cpos.cp_col += 1;
**	  if (input->cpos.cp_col >= input->ts.ws_col)
**	  tcaps_down(input);
**	// si je suis au milieu de la string je la redraw
**	if (input->str->len > ((((input->ts.ws_col * input->offset_line) + \
**									input->cpos.cp_col) - input->offset_col)))
**	redraw_line(input);
*/

t_input	*input_new(void)
{
	t_input	*input;

	if (!(input = ft_memalloc(sizeof(*input))))
		return (NULL);
	input->next = NULL;
	input->prev = NULL;
	if (!(input->str = string_create()))
		ft_memdel((void**)&input);
	return (input);
}

t_input	*input_get(void)
{
	static t_input	*input = NULL;

	if (input == NULL)
		input = input_new();
	return (input);
}

t_input	*input_get_last(void)
{
	t_input	*input;

	input = input_get();
	while (input && input->next)
		input = input->next;
	return (input);
}

/*

#define INPUT_PREV true
#define INPUT_NEXT false

t_input	*get_input_line(t_inputBOOL direction)
{
	if (direction == INPUT_PREV && (input->prev)
		if )

			else
}
(...);
*/



char *sh_get_line(t_input *input, t_sh_opt *opts)
{
	char			buff[MAX_KEY_STRING_LEN + 1];
	t_key			key;
	BOOL			stop;


	stop = false;
	raw_terminal_mode();
	//reset_input(&input);
	while (stop == false)
	{
		ft_bzero((void *)buff, MAX_KEY_STRING_LEN);
		read(STDIN_FILENO, buff, (opts->tcaps) ? MAX_KEY_STRING_LEN : 1);
		key = key_get(buff, opts->tcaps);
		if (ft_strcmp(key.key_code, KEY_CODE_NONE))
			stop = key_exec(&key, input);
		else if (is_printstr(buff) && !input->select.is)
		{
			if (!string_insert(input->str, key.key, pos_in_str(input)))
				return (NULL);
			sh_history_insert_buf(input->str->s);
			draw_char(input, key.key);
		}
		key_del(&key);
	}
	default_terminal_mode();
	sh_history_insert_buf(NULL);
	return (NULL);
}
