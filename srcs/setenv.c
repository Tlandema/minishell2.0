/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:50:09 by tlandema          #+#    #+#             */
/*   Updated: 2019/08/03 17:06:16 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	setenv_builtin(char *left, char *right, int i)
{
	char	**tab;
	char	*str;

	if (!left || !right || ft_strchr(left, '=') || ft_strchr(right, '='))
		error_message(5, NULL);
	else
	{
		if ((str = ft_strnew(ft_strlen(left) + ft_strlen(right) + 1)) == NULL)
			return (FAILURE);
		tab = g_env.v_env;
		if ((g_env.v_env = (char **)ft_memalloc(sizeof(char *)
				* (ft_count_tab(tab) + 2))) == NULL)
			return (FAILURE);
			ft_putchar('a');
		while (tab[++i])
			if ((g_env.v_env[i] = ft_strdup(tab[i])) == NULL)
				return (FAILURE);
		ft_strcpy(str, left);
		ft_strcat(str, "=");
		ft_strcat(str, right);
		g_env.v_env[i] = str;
		ft_tabdel(tab);
	}
	return (SUCCESS);
}
