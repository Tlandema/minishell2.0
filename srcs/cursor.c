/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:39:43 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:47:43 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cursor_to_the_left(t_cur *cur)
{
	tputs(tgetstr("le", NULL), 1, printattr);
	cur->pos--;
}

void	cursor_to_the_right(t_cur *cur)
{
	tputs(tgetstr("nd", NULL), 1, printattr);
	cur->pos++;
}
