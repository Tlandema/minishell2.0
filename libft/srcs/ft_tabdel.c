/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:34:17 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 08:25:13 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_tabdel(char **tab)
{
	int32_t	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		ft_strclr((*tab)[i]);
		ft_strdel(&(*tab)[i]);
	}
	free(tab);
	tab = NULL;
}
