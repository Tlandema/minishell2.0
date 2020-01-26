/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 08:17:12 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:11:57 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	if (environment_verification(envp) == FAILURE)
		return (free_env());
	signals_initializer();
	/*while (1)
	{
		if (looper() == FAILURE)
			break;
	}
	return (free_env());*/
}
