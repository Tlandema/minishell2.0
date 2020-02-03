/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:39:43 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 02:14:20 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	character_insertion(t_cur *cur, char key)
{
	char	*str;

	str = g_env.str;
	if (cur->length >= PATH_MAX - 1)
		return (SUCCESS);
	ft_memmove(str + cur->pos + 1, str + cur->pos, PATH_MAX - cur->pos - 1);
	str[cur->pos] = key;
	tputs(tgetstr("im", NULL), 1, printattr);
	ft_putchar_fd(key, 0);
	tputs(tgetstr("ei", NULL), 1, printattr);
	cur->length++;
	cur->pos++;
	return (SUCCESS);
}

void	cursor_initializer(t_cur *cur)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	cur->start_row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	cur->start_col = ft_atoi(answer + i + 1);
	cur->pos = 0;
	cur->length = 0;
}

int8_t	cursor_to_the_left(t_cur *cur)
{
	tputs(tgetstr("le", NULL), 1, printattr);
	cur->pos--;
	return (SUCCESS);
}

int8_t	cursor_to_the_right(t_cur *cur)
{
	tputs(tgetstr("nd", NULL), 1, printattr);
	cur->pos++;
	return (SUCCESS);
}

int8_t	character_deletion(t_cur *cur)
{
	char	*str;

	str = g_env.str;
	if (cur->pos != 0)
		cursor_to_the_left(cur);
	else
		return (SUCCESS);
	ft_memmove(str + cur->pos, str + cur->pos + 1, PATH_MAX - cur->pos - 1);
	tputs(tgetstr("cd", NULL), 0, printattr);//protect
	tputs(tgetstr("sc", NULL), 0, printattr);
	ft_putstr_fd(str + cur->pos, 0);
	tputs(tgetstr("rc", NULL), 0, printattr);
	cur->length--;
	return (SUCCESS);
}
