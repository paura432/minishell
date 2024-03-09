/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_comands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:26:08 by pramos            #+#    #+#             */
/*   Updated: 2024/03/09 11:40:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int go_comands(t_mini *mini, char **env)
{
    int comands;
    int i;

    i = 0;
    mini->info = ft_split(mini->input, ' ');
    comands = parse(mini);
//    while(mini->info[i])
//        printf("%s\n", mini->info[i++]);
//    printf("%i\n", comands);
//    printf("%i\n", mini->compound);
    if(created_comands(mini, env))
        return(1);
    else if(comands == 0 && mini->compound == 1)
        i = simple_comand(mini, env);
    else if(comands == 0 && mini->compound > 1)
        i = compound_comand(mini, env);
    else if(comands > 0)
        i = pipe_comand(mini, env);
    return(i);
}

int parse(t_mini *mini)
{
    int comand;
    int i;

    i = 0;
    comand = 0;
    if(no_comands(mini->input))
        return(-1);
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
    if(!invalid_input(mini, env, 0))
        return(0);
//    i = execute_cmd_mini(mini->info, env);
    return(1);
}

int compound_comand(t_mini *mini, char **env)
{
    if(!invalid_input(mini, env, 0))
            return(0);
//    i = execute_cmd_mini(mini->info, env);
    return(1);
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
