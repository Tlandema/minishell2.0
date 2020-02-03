/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 09:49:27 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 02:22:28 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int8_t	searching_in_dir(char *to_match, char *dir_name, char *add)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				len;

	len = ft_strlen(to_match);
	if (len == 0)
		return (SUCCESS);
	if (!(dirp = opendir(dir_name)))
		return (FAILURE);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (!ft_strncmp(dp->d_name, to_match, len))
		{
			if (!(add = ft_strdup(&dp->d_name[len])))
				return (FAILURE);
		}
		if (add != NULL)
			break ;
	}
	if (closedir(dirp) == - 1)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	path_filler(char **paths)
{
	char *tmp;

	if ((tmp = get_env_variable("PATH")) && tmp == NULL)
		return (SUCCESS);
	if ((paths = ft_strsplit(tmp, ':')) && paths == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	multiple_instructions(char *add)
{
	char	*buf;

	if ((buf = ft_strnew(PATH_MAX)) && buf == NULL)
		return (FAILURE);
	if (searching_in_dir(&strrchr(g_env.str, ' ')[1], getcwd(buf, PATH_MAX), add)
			== FAILURE)
		return (FAILURE);
	ft_strdel(&buf);
	return (SUCCESS);
}

void			autocomplete_helper(t_cur *cur, char *add, char **paths)
{
	int i;

	i = 0;
	if (add == NULL)
		return ;
	while (add[i])
	{
		character_insertion(cur, add[i]);
		i++;
	}
	i = 0;
	while (paths[i])
		ft_strdel(&paths[i++]);
	ft_memdel((void **)&paths);
	ft_strdel(&add);
}

int8_t			autocomplete_machine(t_cur *cur)
{
	char	*str;
	char	**paths;
	char	*add;
	int		i;

	str = g_env.str;
	paths = NULL;
	add = NULL;
	i = -1;
	if (cur->pos != cur->length || ft_last_char(str) == ' ')
		return (SUCCESS);
	if (path_filler(paths) == FAILURE)
		return (FAILURE);
	if (paths == NULL)
		return (SUCCESS);
	if (ft_strrchr(str, ' '))
	{
		if (multiple_instructions(add) == FAILURE)
			return (FAILURE);
	}
	else
		while (paths[++i])
			if (searching_in_dir(str, paths[i], add) == FAILURE)
				return (FAILURE);//free paths
	autocomplete_helper(cur, add, paths);
	return (SUCCESS);
}
