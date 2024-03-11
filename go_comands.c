/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_comands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:26:08 by pramos            #+#    #+#             */
/*   Updated: 2024/03/11 20:46:30 by marvin           ###   ########.fr       */
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
    if(comands == 0 && mini->compound == 1)
        i = simple_comand(mini, env);
    else if(comands == 0 && mini->compound > 1)
        i = compound_comand(mini, env);
    else if(comands == 1)
        i = pipe_comand(mini, env);
    else if(comands == 2)
        i = redirecctions_comand(mini, env);
    return(i);
}

int parse(t_mini *mini)
{
    int i;
    int bol;
    i = -1;
    bol = 0;
    // if(no_comands(mini->input))
    //     return(-1);
    while(mini->info[++i] != 0)
    {
        if(mini->info[i][0] == '|')
            return(1);
        else if(((mini->info[i][0] == '|' &&  mini->info[i][1] == '|' ) || (mini->info[i][0] == '&' &&  mini->info[i][1] == '&' )) &&
                bol != 2)
            bol = 3;
        else if(mini->info[i][0] == '>' || mini->info[i][0] == '<')
            bol = 2;
    }
    mini->compound = i;
    return(bol);
}

int simple_comand(t_mini *mini, char **env)
{
    // printf("simple\n");
    if(no_comands(mini->input))
    {
        if(created_comands(mini->input, mini, env, 0))
            return(1);
        else
            return(0);        
    }
    else if(!invalid_input(mini, env, 0))
        return(0);
//    i = execute_cmd_mini(mini->info, env);
    return(1);
}

int compound_comand(t_mini *mini, char **env)
{
    // printf("compound\n");
    if(no_comands(mini->input))
    {
        if(created_comands(mini->input, mini, env, 0))
            return(1);
        else
            return(0);        
    }
    else if(!invalid_input(mini, env, 0))
        return(0);
//    i = execute_cmd_mini(mini->info, env);
    return(1);
}

int pipe_comand(t_mini *mini, char **env)
{
    // printf("pipe>>ssss>\n");
    int i;
    int bol;

    i = 0;
    bol = 1;
    // if(!invalid_input(mini, env, 0))
    //     return(0);
    while(mini->info[i])
    {
        if((mini->info[i][0] == '|' || (mini->info[i][0] == '&' && mini->info[i][1] == '&') ||
                (mini->info[i][0] == '|' && mini->info[i][1] == '|') || mini->info[i][0] == '>' || mini->info[i][0] == '<'))
                printf("");
        else if(no_comands(mini->info[i]))
        {
            printf("dentro no_comands\n");
            if(!created_comands(mini->info[i], mini, env, i))
            {
                bol = 0;
                if(mini->info[i + 1] != 0 && ((mini->info[i + 1][0] != '|' || !(mini->info[i + 1][0] == '&' && mini->info[i + 1][1] == '&') ||
                !(mini->info[i + 1][0] == '|' && mini->info[i + 1][1] == '|') || mini->info[i + 1][0] != '>' || mini->info[i + 1][0] != '<')))
                    i++;
            }
            else if(mini->info[i + 1] != 0 && ((mini->info[i + 1][0] != '|' || !(mini->info[i + 1][0] == '&' && mini->info[i + 1][1] == '&') ||
                !(mini->info[i + 1][0] == '|' && mini->info[i + 1][1] == '|') || mini->info[i + 1][0] != '>' || mini->info[i + 1][0] != '<')))
                i++; //estariamos pensando en que solo nos colocan 1 input en cada comando creado, revisar
        }
        else if(!invalid_input(mini, env, i))
        {
            bol = 0;
            if(mini->info[i + 1] != 0 && ((mini->info[i + 1][0] != '|' || !(mini->info[i + 1][0] == '&' && mini->info[i + 1][1] == '&') ||
            !(mini->info[i + 1][0] == '|' && mini->info[i + 1][1] == '|') || mini->info[i + 1][0] != '>' || mini->info[i + 1][0] != '<')))
                i++;
        }
        else if(mini->info[i + 1] != 0 && ((mini->info[i + 1][0] != '|' || !(mini->info[i + 1][0] == '&' && mini->info[i + 1][1] == '&') ||
            !(mini->info[i + 1][0] == '|' && mini->info[i + 1][1] == '|') || mini->info[i + 1][0] != '>' || mini->info[i + 1][0] != '<')))
            i++;
        i++;
    }
    return(bol);
}

int redirecctions_comand(t_mini *mini, char **env)
{
    printf("redirecctions>>ssss>\n");
    return(1);
}
