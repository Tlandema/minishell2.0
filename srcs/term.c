/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:27:01 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/03 06:28:58 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	terminal_initializer(void)
{
	struct termios	tattr;
	
	if (tgetent(NULL, getenv("TERM")) < 1)
	{
		ft_putstr("\nThe terminal wille not work since it doesn't have a n en");
		ft_putendl("vironment variable called TERM set to a logical value.");
		return(FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, &tattr) == FAILURE)
		return (FAILURE);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	terminal_reseter(void)
{
	struct termios	tattr;

	if (tcgetattr(STDIN_FILENO, &tattr) == FAILURE)
		return (FAILURE);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tattr) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
