/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:50:09 by tlandema          #+#    #+#             */
/*   Updated: 2019/08/03 17:06:16 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	ft_check_env(char *check)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = 0;
	j = 0;
	k = FAIL_OK;
	while (g_env.v_env[i])
	{
		if ((copy = ft_strdup(g_env.v_env[i])) == NULL)
			return (FAILURE);
		if (ft_strequ(ft_strrev(&ft_strchr(ft_strrev(copy), '=')[1]), check))
			k = SUCCESS;
		ft_strdel(&copy);
		copy = NULL;
		i++;
	}
	if (k == SUCCESS)
		if ((g_env.v_env = (char **)ft_memalloc(sizeof(char *)
				* (ft_count_tab(g_env.v_env)))) == NULL)
			return (FAILURE);
	return (k);
}

int8_t			unsetenv_builtin(char *del, int32_t j)
{
	int32_t	i;
	int32_t	ret;
	char	***tab;
	char	*str;
	char	*str_tmp;

	i = -1;
	tab = &g_env.v_env;
	if ((ret = ft_check_env(del)) == SUCCESS)
	{
		while (*tab[++i])
		{
			if ((str_tmp = ft_strdup(*tab[i])) == NULL)
				return (FAILURE);
			str = ft_strrev(&ft_strchr(ft_strrev(*tab[i]), '=')[1]);
			if (!ft_strequ(del, str))
				g_env.v_env[j++] = str_tmp;
		}
		ft_tabdel(*tab);
	}
	else if (ret == FAIL_OK)
		error_message(6, NULL);
	return (ret);
}
