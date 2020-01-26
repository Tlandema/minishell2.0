/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 08:22:52 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:29:18 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	environment_verification(char **envp)
{
	int	i;

	if (envp == NULL || envp[0] == NULL)
		return (FAILURE);
	if ((i = ft_count_tab(envp)) == FAILURE)
		return (FAILURE);
	if ((g_env.v_env = (char **)ft_memalloc(sizeof(char *) * (i + 1))) == NULL)
		return (FAILURE);
	i = 0;
	while (envp[i])
	{
		if ((g_env.v_env[i] = ft_strdup(envp[i])) && g_env.v_env[i] == NULL)
			return (FAILURE);
		++i;
	}
	return (SUCCESS);
}
