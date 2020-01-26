/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:33:26 by tlandema          #+#    #+#             */
/*   Updated: 2020/01/26 15:46:56 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "define.h"
# include <libft.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

typedef struct		s_env
{
	
	char			**v_env;
	char			*old_pwd;
	char			str[PATH_MAX];
	int				cat;
	int				rog;
	int				pos;
}					t_env;

typedef struct		s_cur
{
	int				start_row;
	int				start_col;
	int				pos;
	int				length;
}					t_cur;

t_env				g_env;

/*
***************************INITIALIZATION_FUNCTIONS*****************************
*/

int8_t	environment_verification(char **envp);
void	signals_initializer(void);

/*
 **************************LOOP_FUNCTIONS***************************************
*/


/*
 **************************PROMPT_FUNCTIONS*************************************
*/

int8_t	prompter_printer(void);

/*
 **************************BUILTIN_FUNCTIONS************************************
*/


/*
 **************************EXEC_FUNCTION****************************************
*/


/*
 **************************FREE_FUNCTIONS***************************************
*/

uint8_t	free_env(void);

/*
 **************************TERM_FUNCTIONS***************************************
*/

int8_t	terminal_initializer(void);
int8_t	terminal_reseter(void);

/*
 **************************CURS_FUNCTIONS***************************************
*/

void	cursor_initializer(t_cur *cur);
void	cursor_to_the_left(t_cur *cur);
void	cursor_to_the_right(t_cur *cur);

/*
 **************************UTILITY_FUNCTIONS************************************
*/

int		number_of_column(void);
int		printattr(int value);

/*
 **************************SIGNALS_FUNCTION*************************************
*/


/*
 **************************LINE_FUNCTIONS***************************************
*/

int8_t	line_editor(void);

/*
 *************************ERORR_FUNCTIONS**************************************
*/


#endif
