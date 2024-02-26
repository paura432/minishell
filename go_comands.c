/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_comands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:26:08 by pramos            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int go_comands(t_mini *mini, char **env)
{
    int comands;
    
    mini->info = ft_split(mini->input, ' ');
    comands = parse(mini);
    if(comands == 0 && mini->compound == 1)
        simple_comand(mini, env);
    else if(comands == 0 && mini->compound > 1)
        compound_comand(mini, env);
    else if(comands > 0)
        pipe_comand(mini, env);  
}

int parse(t_mini *mini)
{
    int comand;
    int i;

    i = 0;
    comand = 0;
    while(mini->info[i])
    {
        if(mini->info[i][0] == '|')
            comand++;
        i++;
    }
    mini->compound = i;
    return(comand);
}

int simple_comand(t_mini *mini, char **env)
{
	int i;

    i = invalid_input(mini, env, 0);
    return(i);
}

int compound_comand(t_mini *mini, char **env)
{
    int i;

    i = invalid_input(mini, env, 0);
    return(i);
}

int pipe_comand(t_mini *mini, char **env)
{
    int i;

    i = 0;
    if(!invalid_input(mini, env, 0))
        return(0);
    while(mini->info[i])
    {
        if(mini->info[i][0] == '|')
            if(!invalid_input(mini, env, ++i))
                return(0);
        i++;
    }
    return(1);
}
