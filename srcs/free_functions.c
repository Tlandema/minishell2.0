/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:40:59 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:29:59 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
