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
#include <fcntl.h>

static int8_t	git_checker(char *tmpath)
{
	int		fd;
	char	*str;

	ft_strcat(tmpath,"/HEAD");
	if (access(tmpath, R_OK) != 0)
		return (FAILURE);
	if ((fd = open(tmpath, O_RDONLY)) == -1)
		return (FAILURE);
	if (get_next_line(fd, &str) == -1)
		return (FAILURE);
	if (close(fd) == -1)
		return (FAILURE);
	ft_putstr("git:(\033[31;49m");
	ft_putstr(&ft_strchr(&ft_strchr(str, '/')[1], '/')[1]);
	if (ft_strstr(str, "ref : refs/heads/"))
		ft_putstr(ft_strchr(ft_strchr(str, '/'), '/'));
	ft_putstr("\033[39;49m) ");
	ft_strdel(&str);
	return (SUCCESS);
}

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
		ft_strclr(tmpath);
		ft_strcpy(tmpath, ft_strrev(&ft_strchr(ft_strrev(path), '/')[1]));
		if (git_printer(tmpath) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
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
