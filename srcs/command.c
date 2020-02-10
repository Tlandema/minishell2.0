/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:17:59 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/07 16:37:29 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		path_former(char *buff, char *path, char *arg)
{
	ft_strcpy(buff, path);
	ft_strcat(buff, "/");
	ft_strcat(buff, arg);
}

static int		exec_helper(char **com_arg, char **paths, int i)
{
	char	str[PATH_MAX];
	int		check;

	check = 0;
	while (paths[++i])
	{
		path_former(str, paths[i], com_arg[0]);
		if (!access(str, F_OK) && access(str, X_OK) == FAILURE)
			return (10);
		if ((check = access(str, X_OK)) == SUCCESS)
		{
			if (fork() == SUCCESS)
				execve(str, com_arg, g_env.v_env);
			else
			{
				wait(0);
				if (g_env.cat == 1)
					if (prompter_printer() == FAILURE)
						return (FAILURE);
			}
			return (check);
		}
		ft_strclr(str);
	}
	return (check);
}

static int8_t	check_and_exec(char **com_arg, char **paths)
{
	int8_t		check;

	if (!access(com_arg[0], F_OK) && access(com_arg[0], X_OK) == FAILURE)
		return (10);
	if ((check = access(com_arg[0], X_OK)) == SUCCESS)
	{
		if (fork() == SUCCESS)
		{
			execve(com_arg[0], com_arg, g_env.v_env);
			ft_tabdel(paths);
		}
		else
			wait(0);
	}
	else if (paths)
		check = exec_helper(com_arg, paths, -1);
	if (check == FAILURE)
		check = 4;
	return (check);
}

int8_t			command_parsing(char **arg)
{
	char	*paths_tmp;
	char	**paths;
	int		check;

	paths = NULL;
	if (ft_strequ("cat", arg[0]) && arg[1] == NULL)
		g_env.cat = 1;
	if ((paths_tmp = get_env_variable("PATH")) != NULL)
	{
		if ((paths = ft_strsplit(paths_tmp, ':')) == NULL)
			return (FAILURE);
		ft_strdel(&paths_tmp);
	}
	if ((check = check_and_exec(arg, paths)) != SUCCESS)
		error_message(check, arg[0]);
	if (paths)
		ft_tabdel(paths);
	return (SUCCESS);
}
