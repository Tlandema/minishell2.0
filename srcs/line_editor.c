/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:42:50 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/27 16:06:31 by tlandema         ###   ########.fr       */
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
	return (SUCCESS);
}

static int	key_gatherer(int64_t key, t_cur *cur)
{
	int8_t ret;

	ret = 0;
	if ((key > 31 && key < 127))
		ret = character_insertion(cur, (char)key);
	else if (key == 4414235 && cur->pos < cur->length)
		ret = cursor_to_the_right(cur);
	else if (key == 4479771 && cur->pos != 0)
		ret = cursor_to_the_left(cur);
	else if (key == 127 && cur->length != 0)
		ret = character_deletion(cur);
	else if (key == 9)
		ret = autocomplete_machine(cur);
	else if (key == 10)
		ret = 1;
	return (ret);
}

int8_t		line_editor(void)
{
	int64_t	key;
	t_cur	cur;
	int		i;
	int		ret;

	i = 0;
	ft_bzero(&cur, sizeof(t_cur));
	cursor_initializer(&cur);
	g_env.pos = cur.pos;
	while (1)
	{
		key = 0;
		if ((ret = read(0, &key, 8)) < 0)
			return (FAILURE);
		if ((ret = key_gatherer(key, &cur)) == RECUP_LINE)
		{
			ft_putchar('\n');
			while (i++ < number_of_column())
				if (tputs(tgetstr("le", NULL), 0, printattr) == FAILURE)
					return (FAILURE);
			return (SUCCESS);
		}
		else if (ret == FAILURE)
			return (FAILURE);
	}
}
