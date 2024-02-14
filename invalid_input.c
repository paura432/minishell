/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:33:32 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 21:33:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    free_split(char **inf)
{
    int i;

    i = -1;
	while (inf[++i] != 0)
		free(inf[i]);
}

char	*find_path_mini(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

int	change_path(char *paths, char *cmd)
{
	char	**tmp_paths;
	char	*tmp;
	char	*path;

    if(cmd)
	tmp_paths = ft_split(paths, ':');
	while (*tmp_paths)
	{
		tmp = ft_strjoin(*tmp_paths, "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK & R_OK) == 0)
			return (1);
		free(path);
		tmp_paths++;
	}
	return (0);
}

int created_comands(char *input)
{
    int i;

    i = 0;
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        input++;
    if(!ft_strncmp("echo ", input,  5))
        return(1);
    if(!ft_strncmp("cd ", input, 4))
        return(1);
    if(!ft_strncmp("pwd", input, 3))
        return(1);
    if(!ft_strncmp("export ", input, 7))
        return(1);
    if(!ft_strncmp("unset ", input, 6))
        return(1);
    if(!ft_strncmp("exit", input, 4))
        exit(0);
    return(0);
}

int	invalid_input(t_mini *mini, char **env)
{
    char *path;

    if(created_comands(mini->input))
        return(1);
    mini->info = ft_split(mini->input, ' ');
    path = find_path_mini(env);
    if(!change_path(path, mini->info[0]))
    {
        printf("%s : command not found\n", mini->info[0]);
        free_split(mini->info);
        return(0);
    }
    return(1);
}
