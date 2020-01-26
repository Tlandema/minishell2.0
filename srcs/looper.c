/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:08:27 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:25:55 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	instruction_gatherer(void)
{
	if (g_env.cat == 0)
	{
		if (prompter_printer() == FAILURE)
			return (FAILURE);
	}
	g_env.rog = 0;
	g_env.cat = 0;
	if (terminal_initializer() == FAILURE)
		return (FAILURE);
	if (line_editor() == FAILURE)
		return (FAILURE);
	if (terminal_reseter() == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			looper(void)
{
	//char	**tab_f;
	//char	**tab;
	//int		i;
	
	if (instruction_gatherer() == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
