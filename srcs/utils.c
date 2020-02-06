/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:09:46 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/05 16:19:11 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_variable(char *match)
{
	int		i;
	char	**var;
	char	*cpy;

	i = 0;
	if (!(var = copy_tab()))
		return (NULL);
	while (var[i])
	{
		cpy = var[i];
		if (ft_strequ(ft_strrev(&ft_strchr(ft_strrev(var[i]), '=')[1]), match))
		{
			ft_strrev(cpy);
			if (!(cpy = ft_strdup(&ft_strchr(cpy, '=')[1])))
				return (NULL);
			ft_tabdel(var);
			return (cpy);
		}
		i++;
	}
	ft_tabdel(var);
	return (NULL);
}

static char	**free_copy(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_memdel((void **)&tab);
	return (NULL);
}

char		**copy_tab(void)
{
	int		i;
	char	**copy;

	i = ft_count_tab(g_env.v_env);
	if (!(copy = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (g_env.v_env[++i])
		if (!(copy[i] = ft_strdup(g_env.v_env[i])))
			return (free_copy(copy));
	copy[i] = NULL;
	return (copy);
}
