/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 06:12:25 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 09:50:55 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	dollar_replacer(char *str, int i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*word;

	j = i;
	k = 0;
	while (str[++i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'))
		k++;
	if (!(word = ft_strndup(&str[j + 1], k)))
		return (FAILURE);
	if ((tmp = get_env_variable(word)) == NULL)
	{
		ft_strdel(&word);
		return (FAIL_OK);
	}
	k = ft_strlen(tmp);
	ft_memmove(&str[j + k], &str[i], ft_strlen(&str[i]));
	ft_strcpy(&str[j], tmp);
	ft_strdel(&tmp);
	ft_strdel(&word);
	return (SUCCESS);
}

static int8_t	tild_replacer(char *str, int i)
{
	char	*tmp;
	int		len;

	if ((tmp = get_env_variable("HOME")))
		return (FAIL_OK);
	len = ft_strlen(tmp);
	ft_memmove(&str[i + len], &str[i + 1], ft_strlen(&str[i + 1]));
	ft_strcpy(&str[i], tmp);
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
		if (str[i] == '$' && (str[i + 1] != ' ' && str[i  + 1] != '\0'))
		{
			if (dollar_replacer(str, i) == FAILURE)
				return (FAILURE);
		}
		else if (str[i] == '~')
			if (tild_replacer(str, i) == FAILURE)
				return (FAILURE);
	}
	return (SUCCESS);
}
