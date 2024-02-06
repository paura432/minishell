/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:30 by pramos            #+#    #+#             */
/*   Updated: 2024/02/06 22:17:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include "Pipex/pipex.h"
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

//minishell.c
void	handle_signal(int sign);
void    signal_detecter(void);
int	    invalid_input(char *input, char **env);

//invalid_input.c
void    free_split(char **inf);
int	    change_path(char *paths, char *cmd);
char	*find_path_mini(char **envp);
int     created_comands(char *input);

#endif
