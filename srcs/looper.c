/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:08:27 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 13:12:59 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	line_parser(char **argument)
{
	if (ft_strequ(argument[0], "cd"))
		return (cd_builtin(argument));
	else if (ft_strequ(argument[0], "exit"))
		return (FAILURE);
	else if (ft_strequ(argument[0], "env") && argument[1] == NULL)
		return (env_builtin());
	else if (ft_strequ(argument[0], "setenv"))
		return (setenv_builtin(argument[1], argument[2], 0));
	else if (ft_strequ(argument[0], "unsetenv"))
		return (unsetenv_builtin(argument[1], 0));
	else if (ft_strequ(argument[0], "echo"))
		return (echo_builtin(argument));
	else
		return (command_parsing(argument));
	return (FAIL_OK);
}

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
	char	**command_tab;
	char	**arg_tab;
	int		i;

	i = -1;
	arg_tab = NULL;
	if (instruction_gatherer() == FAILURE)
		return (FAILURE);
	if (variable_assigner() == FAILURE)
		return (FAILURE);
	if ((command_tab = ft_strsplit(g_env.str, ';')) == NULL)
		return (FAILURE);
	while (command_tab[++i])
	{
		g_env.rog = 0;
		if ((argument_finder(command_tab[i], &arg_tab)) == FAILURE)
			return (FAILURE);
		if (arg_tab)
			if ((line_parser(arg_tab)) == FAILURE)
				return (FAILURE);
	}
	ft_strclr(g_env.str);
	return (SUCCESS);
}
