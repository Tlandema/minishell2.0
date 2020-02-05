/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:33:26 by tlandema          #+#    #+#             */
/*   Updated: 2020/02/05 05:41:38 by tlandema         ###   ########.fr       */
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

int8_t	looper(void);

/*
 **************************PROMPT_FUNCTIONS*************************************
*/

int8_t	prompter_printer(void);

/*
 **************************BUILTIN_FUNCTIONS************************************
*/

int8_t	cd_builtin(char **args);
int8_t	setenv_builtin(char *left, char *right, int i);
int8_t	unsetenv_builtin(char *del, int32_t j);
int8_t	echo_builtin(char **tab);
int8_t	env_builtin(void);

/*
 **************************EXEC_FUNCTION****************************************
*/

int8_t		command_parsing(char **arg);

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
int8_t	cursor_to_the_left(t_cur *cur);
int8_t	cursor_to_the_right(t_cur *cur);

/*
 **************************UTILITY_FUNCTIONS************************************
*/

int		number_of_column(void);
int		printattr(int value);
char	*get_env_variable(char *match);
char	**copy_tab(void);

/*
 **************************SIGNALS_FUNCTION*************************************
*/


/*
 **************************LINE_FUNCTIONS***************************************
*/

int8_t	argument_finder(char *str, char ***arg_tab);
int8_t	variable_assigner(void);
int8_t	line_editor(void);
int8_t	character_deletion(t_cur *cur);
int8_t	character_insertion(t_cur *cur, char key);
int8_t	autocomplete_machine(t_cur *cur);

/*
 *************************ERORR_FUNCTIONS**************************************
*/

void	error_message(int i, char *name);

#endif
