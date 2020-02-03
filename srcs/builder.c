/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 07:48:00 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 09:49:24 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	good_quote_number(char *str)
{
	int32_t	i;
	int32_t	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '"')
			j++;
	if (j % 2)
		return (FAILURE);
	return (SUCCESS);
}

static int32_t	count_word_number(char *str)
{
	int32_t	tab_size;
	int32_t	i;
	uint8_t	boolean;

	i = 0;
	boolean = 1;
	tab_size = 0;
	if (str)
		while (str[i])
		{
			if (str[i] == ' ')
				boolean = 1;
			else if (boolean == 1)
			{
				boolean = 0;
				tab_size++;
			}
			i++;
		}
	return (tab_size);
}

static int32_t	argument_counter(char **tab,  uint8_t boolean)
{
	int32_t count;
	int32_t	i;

	count = 0;
	i = 0;
	if (boolean == 1)
	{
		count = 1;
		i = 1;
	}
	while (tab[i])
	{
		count += count_word_number(tab[i]);
		i++;
		if (tab[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int8_t	tab_filler(char **arg_tab, char **tmp_tab, uint8_t boolean)
{
	char	**tmp_tab2;
	int32_t	i;
	int	j;

	i = 0;
	j = 0;
	if (boolean == 1)
	{
		if ((arg_tab[0] = ft_strdup(tmp_tab[0])) == NULL)
			return (FAILURE);
		i = 1;
		j = 1;
	}
	while (tmp_tab[i])
	{
		if ((tmp_tab2 = ft_split_white(tmp_tab[i])) == NULL)
			return (FAILURE);
		ft_join_tab(arg_tab, tmp_tab2, &j);
		ft_tabdel(tmp_tab2);
		if (tmp_tab[++i])
			if ((arg_tab[j++] = ft_strdup(tmp_tab[i++])) == NULL)
				return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			argument_finder(char *str, char **arg_tab)
{
	char		**tmp_tab;
	int32_t		counter;
	uint8_t		boolean;

	counter = 0;
	if (good_quote_number(str) == FAILURE)
		return (FAIL_OK);
	while (str[counter] == ' ')
		counter++;
	if (str[counter] == '\0')
		return (FAIL_OK);
	boolean = (str[counter] == '"') ? 1 : 0;
	if ((tmp_tab = ft_strsplit(str, '"')) == NULL)
		return (FAIL_OK);
	counter = argument_counter(tmp_tab, boolean);
	if (!(arg_tab = (char **)ft_memalloc(sizeof(char *) * (counter + 1))))
		return (FAILURE);
	if (tab_filler(arg_tab, tmp_tab, boolean) == FAILURE)
		return (FAILURE);
	ft_tabdel(tmp_tab);
	return (SUCCESS);
}
