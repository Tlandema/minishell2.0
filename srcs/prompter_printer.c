/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:13:21 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 13:12:59 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	git_printer(char *path)
{
	char	tmpath[PATH_MAX];

	if (path == NULL || path[0] == '\0')
		return (SUCCESS);
	ft_strcpy(tmpath, path);
	ft_strcat(tmpath, "/.git");
	if (access(tmpath, X_OK) == 0)
	{
		if (git_checker(tmpath) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	else
	{
		tmpath = ft_strrev(&ft_strchr(ft_strrev(path), '/')[1]);
		if (git_printer(tmpath
	}
}

static void	red_or_green(int rog)
{
	if (rog)
		ft_putstr("\033[91m");
	else
		ft_putstr("\033[92m");
	ft_putstr("Tsh \033[39m(\033[96m");
}

int8_t		prompter_printer(void)
{
	char path[PATH_MAX];
	char *tmp;

	if (g_env.cat == -1)
	{
		g_env.cat = 0;
		return (SUCCESS);
	}
	red_or_green(g_env.rog);
	if (getcwd(path, PATH_MAX) == NULL)
	{
		ft_putstr("I'm in the depth of shell\033[39;49m)");
		return (SUCCESS);
	}
	if (ft_strequ(path, (tmp = get_env_variable("HOME"))))
		ft_putstr("~");
	else
		ft_putstr(&strrchr(path, '/')[1]);
	ft_putstr("\033[39;49m) ");
	if (ft_strequ(path, "/") == 0)
		if (git_printer(path) == FAILURE)
			return (FAILURE);
	ft_strdel(&tmp);
	return (SUCCESS);
}
