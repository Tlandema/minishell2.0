/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 09:49:27 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/06 07:43:25 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <stdio.h>

static int8_t	searching_in_dir(char *to_match, char *dir_name, char **add)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				len;

	len = ft_strlen(to_match);
	if (len == 0)
		return (SUCCESS);
	if (!(dirp = opendir(dir_name)))
		return (FAILURE);
	while ((dp = readdir(dirp)) != NULL && *add == NULL)
	{
		if (!ft_strncmp(to_match, dp->d_name, len))
			if (!(*add = ft_strdup(&dp->d_name[len])))
				return (FAILURE);
	}
	if (closedir(dirp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	path_filler(char ***paths)
{
	char *tmp;

	if ((tmp = get_env_variable("PATH")) && tmp == NULL)
		return (FAIL_OK);
	if ((*paths = ft_strsplit(tmp, ':')) && *paths == NULL)
		return (FAILURE);
	ft_strdel(&tmp);
	return (SUCCESS);
}

static int8_t	multiple_instructions(char **add)
{
	char	buf[PATH_MAX];

	if (searching_in_dir(&strrchr(g_env.str, ' ')[1],
			getcwd(buf, PATH_MAX), add) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	autocomplete_helper(t_cur *cur, char *add, char **paths)
{
	int i;

	i = 0;
	if (add == NULL)
		return (FAIL_OK);
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
	return (SUCCESS);
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
		return (FAIL_OK);
	if (path_filler(&paths) == FAILURE)
		return (FAILURE);
	if (paths == NULL)
		return (FAIL_OK);
	if (ft_strrchr(str, ' '))
	{
		if (multiple_instructions(&add) == FAILURE)
			return (FAILURE);
		return (autocomplete_helper(cur, add, paths));
	}
	while (paths[++i] && add == NULL)
		if (searching_in_dir(str, paths[i], &add) == FAILURE)
			return (tabdel_ret(paths, FAILURE));
	return (autocomplete_helper(cur, add, paths));
}
