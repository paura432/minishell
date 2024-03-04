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
    printf("%s\n", (mini->input));
    if(!ft_strncmp("echo", mini->input + i,  4))
        bol = echo_comand(mini->input + i + 4, mini);
    if(!ft_strncmp("cd", mini->input + i, 2))
        bol = cd_comand(mini->input + i + 2, mini);
    else if(!ft_strncmp("pwd", mini->input + i, 3))
        bol = pwd_comand(mini->input + i + 3, mini);
    else if(!ft_strncmp("export", mini->input + i, 6))
        bol = export_comand(mini->input + i + 6, mini);
    else if(!ft_strncmp("unset", mini->input + i, 5))
        bol = unset_comand(mini->input + i + 5, mini);
    else if(!ft_strncmp("env", mini->input + i, 3))
        bol = env_comand(mini->input + i + 3, mini);
    return(bol);
}

int cd_comand(char *input, t_mini *mini)
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

int echo_comand(char *input, t_mini *mini)
{
    // int i;

    // i = 0;
    // while((input[i] > 8 && input[i] < 13) || input[i] == 32)
    //     i++;
    // if(input[i] == "-" && input[i] == "n")
    //     return(1);
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}

int export_comand(char *input, t_mini *mini)
{
    int i;

    i = 0;
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
    if(input[i] >= '0' && input[i] <= '9')
        return(0);
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}

int unset_comand(char *input, t_mini *mini)
{
    int i;

    i = 0;
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}

int pwd_comand(char *input, t_mini *mini)
{
    int i;

    i = 0;
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}

int env_comand(char *input, t_mini *mini)
{
    int i;

    i = 0;
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
    if(input[0] == ' ' || input[0] == 0)
        return(1);
    return(0);
}
