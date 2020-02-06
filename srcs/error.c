/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:12:44 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/06 08:37:46 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_message2(int i, char *name)
{
	if (i == 4)
	{
		ft_putstr("TomTomshell: command not found: ");
		ft_putendl(name);
	}
	else if (i == 5)
	{
		ft_putstr("Usage: \'setenv [VAR] [foo]\' will create a environmental ");
		ft_putstr("variable named VAR=foo. You can't put the sign \'=\' in ");
		ft_putendl("either the name or the value of the variable.");
	}
	else if (i == 6)
	{
		ft_putstr("Usage: \'unsetenv [VAR]\' will delete an environmental var");
		ft_putendl("iable called VAR if it exists.");
	}
	else if (i == 10)
	{
		ft_putstr("TomTomshell: permission denied: ");
		ft_putendl(name);
	}
	else if (i == 11)
	{
		ft_putendl("You are lost ? Use cd to go back to the home directory !");
	}
}

void		error_message(int i, char *name)
{
	g_env.rog = 1;
	if (i == 1)
		ft_putstr("cd: too many arguments\n");
	else if (i == 2 && name)
	{
		if (!access(name, F_OK) && access(name, X_OK) == -1)
			ft_putstr("cd: permission denied: ");
		else
			ft_putstr("cd: no such file or directory: ");
		ft_putstr(name);
		ft_putchar('\n');
	}
	else if (i == 3)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(name);
		ft_putchar('\n');
	}
	else
		error_message2(i, name);
}
