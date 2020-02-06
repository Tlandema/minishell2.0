/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:50:09 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/06 08:38:27 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	check_setenv_in_cd(char *left, char *right, int i)
{
	if (!right)
		error_message(11, NULL);
	else
		return (setenv_builtin(left, right, i));
	return (FAIL_OK);
}

int8_t			setenv_builtin(char *left, char *right, int i)
{
	char	**tab;
	char	*str;

	if (i == 0)
		return (check_setenv_in_cd(left, right, -1));
	if (!right || !left || ft_strchr(left, '=') || ft_strchr(right, '='))
		error_message(5, NULL);
	else
	{
		if ((str = ft_strnew(ft_strlen(left) + ft_strlen(right) + 1)) == NULL)
			return (FAILURE);
		tab = g_env.v_env;
		if ((g_env.v_env = (char **)ft_memalloc(sizeof(char *)
				* (ft_count_tab(tab) + 2))) == NULL)
			return (FAILURE);
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
