/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:30 by pramos            #+#    #+#             */
/*   Updated: 2024/03/09 14:56:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>

# define ERROR_1 "has taken a fork"

typedef struct s_env
{
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_token
{
	int i;
	struct s_token *prev;
	struct s_token *next;
	char *str;
	int  type;
} t_token;

typedef struct s_mini
{
	int		signin;
	int		signout;
	int     compound;
	char	**info;
	char	*input;
	int		error;
	int		info_position_i;
	int 	info_position_j;
	struct	s_env *env;
	struct	s_token *token;
} t_mini;

typedef struct mini_parse
{
	char	**content;
	char	*index;
}mini_parse;

//minishell.c
void	handle_signal(int sign);
void    signal_detecter(void);
int	    invalid_input(t_mini *mini, char **env, int i);

//invalid_input.c
void    free_split(char **inf);
int		change_path(char *paths, char *cmd);
int     no_comands(char *input);

//go_comands
int 	go_comands(t_mini *mini, char **env);
int 	simple_comand(t_mini *mini, char **env);
int 	compound_comand(t_mini *mini, char **env);
int 	pipe_comand(t_mini *mini, char **env);
int 	parse(t_mini *mini);

//mini_utils.c
int		execute_cmd_mini(char **cmd, char **envp);
char	*find_path_mini(char **envp);
char	*change_paths_mini(char *paths, char *cmd);

//created_comands
int 	created_comands(t_mini *mini, char **env);
int 	cd_comand(char *input, t_mini *mini);
int 	echo_comand(char *input, t_mini *mini);
int 	export_comand(char *input, t_mini *mini);
int 	unset_comand(char *input, t_mini *mini);
int 	pwd_comand(char *input, t_mini *mini);
int 	env_comand(char *input, t_mini *mini);

//check_errors
void	check_errors(t_mini *mini);

#endif
