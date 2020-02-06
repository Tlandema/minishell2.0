/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:40:59 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/06 07:40:45 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	tabdel_ret(char **paths, int8_t ret)
{
	ft_tabdel(paths);
	return (ret);
}

uint8_t	free_env(void)
{
	int i;

	i = 0;
	while (g_env.v_env[i])
	{
		ft_strdel(&g_env.v_env[i]);
		i++;
	}
	ft_memdel((void **)&g_env.v_env);
	ft_strdel(&g_env.old_pwd);
	return (1);
}
