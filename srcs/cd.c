/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:08:48 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/05 08:03:14 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int8_t	cd_helper(int8_t ret, char *str)
{
	char	buff[PATH_MAX];

	if (getenv("PWD"))
		unsetenv_builtin("PWD", 0);
	setenv_builtin("PWD", getcwd(buff, PATH_MAX), -1);
	ft_strdel(&str);
	return (ret);
}

static int8_t	move_dir(char *str)
{
	if (!access(str, X_OK))
	{
		ft_strclr(g_env.old_pwd);
		g_env.old_pwd = getcwd(g_env.old_pwd, PATH_MAX);
		chdir(str);
	}
	else
		return (FAIL_OK);
	return (SUCCESS);
}

static void		replace_in_pwd(char *str, char *to_rep, char *rep_by)
{
	char	copy[PATH_MAX];
	int32_t	i;

	i = ft_stristr(str, to_rep);
	ft_strncpy(copy, str, i);
	ft_strcat(copy, rep_by);
	i = i + ft_strlen(to_rep);
	ft_strcat(copy, &str[i]);
	if (move_dir(copy) == FAILURE)
		error_message(2, copy);
}

static int8_t	cd_2_arg(char **args)
{
    int32_t i;
    char    *tmp;
    char    *pwd;

    i = 0;
    if ((pwd = get_env_variable("PWD")) == NULL)
        return (FAILURE);
    if (!ft_strequ(pwd, STR_VERIF))
    {
        if (ft_strstr(pwd, args[1]))
        {
            if ((tmp = ft_strdup(pwd)) == NULL)
                return (FAILURE);
            replace_in_pwd(&ft_strchr(tmp, '=')[1], args[1], args[2]);
            ft_strdel(&tmp);
            ft_strdel(&pwd);
        }
        else
            error_message(3, args[1]);
    }
    return (FAIL_OK);
}

int8_t      cd_builtin(char **args)
{
    int32_t i;
    char    *tmp;

    tmp = NULL;
    i = ft_count_tab(args);
    if (i > 3)
        error_message(1, NULL);
    else if (i == 3)
        return (cd_helper(cd_2_arg(args), NULL));
    else if (args[1] == NULL)
    {
        if ((tmp = get_env_variable("HOME")) == NULL)
            return (FAILURE);
        return (cd_helper(move_dir(tmp), tmp));
    }
    else if (ft_strequ(args[1], "-"))
        return (cd_helper(move_dir(g_env.old_pwd), NULL));
    else
        return (cd_helper(move_dir(args[1]), NULL));
    return (SUCCESS);
}