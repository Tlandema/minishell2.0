/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:42:50 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:49:15 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			number_of_column(void)
{
	struct winsize	w;
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int			printattr(int value)
{
	ft_putchar_fd((char)value, STDERR_FILENO);
	return (0);
}

static int	key_gatherer(int64_t key, t_cur *cur)
{
	if ((key > 31 && key < 127))
		ft_ins_char(cur, (char)key);
	else if (key == 4414235 && cur->pos < cur->length)
		cursor_to_the_right(cur);
	else if (key == 4479771 && cur->pos != 0)
		cursor_to_the_left(cur);
	else if (key == 127 && cur->length != 0)
		ft_del_char(cur);
	else if (key == 9)
		ft_autocomplete(cur);
	else if (key == 10)
		return (1);
	return (0);
}

int8_t		line_editor(void)
{
	int64_t	key;
	t_cur	cur;
	int		i;

	i = 0;
	ft_bzero(&cur, sizeof(t_cur));
	cursor_initializer(&cur);
	g_env.pos = cur.pos;
	while (1)
	{
		key = 0;
		if (read(0, &key, 8) < 0)
			return (FAILURE);
		if (key_gatherer(key, &cur))
		{
			ft_putchar('\n');
			while (i++ < number_of_column())
			{
				if (tputs(tgetstr("le", NULL), 0, printattr) == FAILURE)
					return (FAILURE);
			}
			return (SUCCESS);
		}
	}
}