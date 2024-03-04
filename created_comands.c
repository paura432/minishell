/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:00 by marvin           ###   ########.fr       */
/*  (mini->input > 8 && mini->input < 13) ||                                                                           */
/* ************************************************************************** */

#include"minishell.h"

int created_comands(t_mini *mini, char **env)
{
    int i;
    int bol;

    i = 0;
    bol = 0;
    while((mini->input[i] > 8 && mini->input[i] < 13) || mini->input[i] == 32)
        i++;
    if(!ft_strncmp("echo", mini->input + i,  4))
        bol = echo_comand(mini->input + i + 4);
    if(!ft_strncmp("cd", mini->input + i, 2))
        bol = cd_comand(mini->input + i + 2);
    // else if(!ft_strncmp("pwd", mini->input, 3))
    //     bol = cd_comand(mini->input + 3);
    // else if(!ft_strncmp("export", mini->input, 6))
    //     bol = cd_comand(mini->input + 7);
    // else if(!ft_strncmp("unset", mini->input, 5))
    //     bol = cd_comand(mini->input + 6);
    // else if(!ft_strncmp("env", mini->input, 3))
    //     bol = cd_comand(mini->input + 3);
    return(bol);
}

int cd_comand(char *input)
{
    int i;

    i = 0;
    //saltamos todos los espacios
    //printf("%s\n", input);
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
    if(input[i] == 0)
        return(1);
    if((chdir(input + i)))
        return(0);
    return(1);
}

int echo_comand(char *input)
{
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}
