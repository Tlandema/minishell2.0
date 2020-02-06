/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <tlandema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:47:47 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/05 16:21:24 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static void	stop_signal_handler(void)
{
	terminal_reseter();
	exit(1);
}

static void	int_signal_handler(void)
{
	int i;

	i = 0;
	g_env.rog = 1;
	ft_putchar('\n');
	while (i++ < number_of_column())
		tputs(tgetstr("le", NULL), 0, printattr);
	prompter_printer();
	if (g_env.cat == 1)
		g_env.cat = -1;
	g_env.rog = 0;
	g_env.pos = 0;
	ft_strclr(g_env.str);
}

static void	suspend_signal_handler(void)
{
	terminal_reseter();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

static void	signal_handler(int signal)
{
	char *str;

	if (signal == SIGCONT)
	{
		terminal_initializer();
		signals_initializer();
		prompter_printer();
		str = g_env.str;
		if (str != NULL)
			ft_putstr(str);
	}
	else if (signal == SIGABRT || signal == SIGSTOP || signal == SIGKILL
			|| signal == SIGQUIT || signal == SIGTERM)
		stop_signal_handler();
	else if (signal == SIGINT)
		int_signal_handler();
	else if (signal == SIGTSTP)
		suspend_signal_handler();
}

void		signals_initializer(void)
{
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}
