/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int created_comands(t_mini *mini, char **env)
{
    int i;

    i = 0;
    while((mini->input > 8 && mini->input < 13) || mini->input == 32)
        mini->input++;
//    printf("%s\n", mini->input);
    if(!ft_strncmp("echo", mini->input,  4))
        i = echo_comand(mini->input + 4);
    if(!ft_strncmp("cd", mini->input, 2))
        i = cd_comand(mini->input + 2);
    // else if(!ft_strncmp("pwd", mini->input, 3))
    //     i = cd_comand(mini->input + 3);
    // else if(!ft_strncmp("export", mini->input, 6))
    //     i = cd_comand(mini->input + 7);
    // else if(!ft_strncmp("unset", mini->input, 5))
    //     i = cd_comand(mini->input + 6);
    // else if(!ft_strncmp("env", mini->input, 3))
    //     i = cd_comand(mini->input + 3);
    return(i);
}

int cd_comand(char *input)
{
    int i;

    i = 0;
    //saltamos todos los espacios
    printf("%s\n", input);
    if(input[i] != 32 && input[i] != 0)
        return(0);
    while((input[i] > 8 && input[i] < 13) || input[i] == 32)
        i++;
//    if(input[i] == '.'  && input[i + 1] == '.')
//        return(1);
    printf("%s\n", input);
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
