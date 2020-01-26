/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memoline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 11:01:44 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:51:10 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insertor_char(t_cur *cur, char key)
{
	char *str;

	str = g_env.str;
	if (cur->length >= PATH_MAX - 1)
		return ;
	ft_memmove(str + cur->pos + 1, str + cur->pos, PATH_MAX - cur->pos - 1);
	str[cur->pos] = key;
	tputs(tgetstr("im", NULL), 1, ft_printest);
	ft_putchar_fd(key, 0);
	tputs(tgetstr("ei", NULL), 1, ft_printest);
	cur->length++;
	cur->pos++;
}

void	deletor_char(t_cur *cur)
{
	char *str;

	str = g_env.str;
	if (cur->pos != 0)
		ft_cur_left(cur);
	else
		return ;
	ft_memmove(str + cur->pos, str + cur->pos + 1, PATH_MAX - cur->pos - 1);
	tputs(tgetstr("cd", NULL), 0, &ft_printest);
	tputs(tgetstr("sc", NULL), 0, &ft_printest);
	ft_putstr_fd(str + cur->pos, 0);
	tputs(tgetstr("rc", NULL), 0, &ft_printest);
	cur->length--;
}
