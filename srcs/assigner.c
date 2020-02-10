/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 06:12:25 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/10 10:26:32 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int8_t	dollar_replacer(char *str, int i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*word;

	k = 0;
	while (str[k] && str[k] != ' ' && str[k]!= '\"')
		k++;
	if (!(word = ft_strndup(str + 1, k - 1)))
		return (FAILURE);
	if ((tmp = get_env_variable(word)) == NULL)
	{
		ft_strdel(&word);
		ft_strnclr(str, k);
		ft_memmove(str, str + k, j = ft_strlen(str + k));
		ft_strclr(str + j);
		return (FAIL_OK);
	}
	ft_strdel(&word);
	j = ft_strlen(tmp);
	ft_strnclr(str, k);
	ft_memmove(str + j, str + k, i = ft_strlen(str + k));
	ft_strncpy(str, tmp, j);
	ft_strclr(str + j + i);
	ft_strdel(&tmp);
	return (SUCCESS);
}

static int8_t	tild_replacer(char *str, int i)
{
	char	*tmp;
	int		len;

	if ((tmp = get_env_variable("HOME")) == NULL)
		return (FAIL_OK);
	len = ft_strlen(tmp);
	ft_memmove(&str[i + len], &str[i + 1], ft_strlen(&str[i + 1]));
	ft_strncpy(&str[i], tmp, len);
	ft_strdel(&tmp);
	return (SUCCESS);
}

int8_t			variable_assigner(void)
{
	int		i;
	char	*str;

	i = -1;
	str = g_env.str;
	while (str[++i])
	{
		if (i > PATH_MAX - 100)
			return (SUCCESS);
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\0'))
		{
			if (dollar_replacer(&str[i], 0) == FAILURE)
				return (FAILURE);
		}
		else if (str[i] == '~')
			if (tild_replacer(str, i) == FAIL_OK)
				return (FAIL_OK);
	}
	return (SUCCESS);
}
