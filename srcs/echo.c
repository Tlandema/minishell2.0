/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:04:49 by tlandema          #+#    #+#             */
/*   Updated: 2019/08/03 18:07:12 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	echo_helper(char **tab)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (tab[i])
		size += ft_strlen(tab[i++]) + 1;
	i = 0;
	if ((str = ft_strnew(size)) == NULL)
		return (FAILURE);
	ft_strcpy(str, tab[i]);
	while (tab[++i])
	{
		ft_strcat(str, " ");
		ft_strcat(str, tab[i]);
	}
	i = -1;
	while (str[++i])
		if (str[i] != '"' && str[i] != '\'')
			ft_putchar(str[i]);
	ft_strdel(&str);
	return (SUCCESS);
}

int8_t			echo_builtin(char **tab)
{
	int i;

	if (tab[1])
	{
		i = 1;
		if (ft_strequ(tab[1], "-n"))
			i = 2;
		if (echo_helper(&tab[i]) == FAILURE)
			return (FAILURE);
	}
	ft_putchar('\n');
	return (SUCCESS);
}
