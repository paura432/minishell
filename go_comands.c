/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_comands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:26:08 by pramos            #+#    #+#             */
/*   Updated: 2024/03/18 19:04:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int go_comands(t_mini *mini, char **env)
{
    int comands;
    int i;

    i = 0;
    comands = parse(mini);
    while(mini->token != 0 && mini->token->prev != 0)
        mini->token = mini->token->prev;
//    while(mini->info[i])
//        printf("%s\n", mini->info[i++]);
    // printf("%i\n", comands);
    // printf("%i\n", mini->compound);
    // while(mini->token->str != 0)
	// {
	// 	printf("%s\n", mini->token->str);
	// 	printf("%i\n", mini->token->type);
	// 	mini->token = mini->token->next;
	// }
    // printf("dentro de bucle\n");  
    if(comands == 0)
        i = simple_comand(mini, env);
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
    bol = 0;
    mini->compound = 0;
    while(mini->token != 0)
    {
        if(mini->token->str[0] == '|')
            return(1);
        else if(mini->token->str[0] == '>' || mini->token->str[0] == '<')
            bol = 2;
        mini->token = mini->token->next;
        mini->compound++;
    }
    return(bol);
}

int simple_comand(t_mini *mini, char **env)
{
    // printf("simple\n");
    if(no_comands(mini->input))
    {
        if(created_comands(mini->input, mini, env))
            return(1);
        else
            return(0);        
    }
    else if(!invalid_input(mini, mini->input, env, 0))
        return(0);
//    i = execute_cmd_mini(mini->info, env);
    return(1);
}

// int compound_comand(t_mini *mini, char **env)
// {
//     // printf("compound\n");
//     if(no_comands(mini->token->str))
//     {
//         if(created_comands(mini->token->str, mini, env, 0))
//             return(1);
//         else
//             return(0);        
//     }
//     else if(!invalid_input(mini, mini->token->str, env, 0))
//         return(0);
// //    i = execute_cmd_mini(mini->info, env);
//     return(1);
// }

int pipe_comand(t_mini *mini, char **env)
{
    // printf("pipe>>ssss>\n");
    int bol;
    
    bol = 1;
    // if(!invalid_input(mini, env, 0))
    //     return(0);
    while(mini->token != 0)
    {
        if((mini->token->str[0] == '|' || mini->token->str[0] == '>' || mini->token->str[0] == '<'))
                mini->token = mini->token->next;
        if(no_comands(mini->token->str))
        {
            // printf("dentro no_comands\n");
            created_comands(mini->token->str, mini, env);
            if(mini->token->next != 0 && mini->token->next->str[0] != '|')
                while(mini->token->next != 0 && (mini->token->next->str[0] != '|' ||
                        mini->token->next->str[0] != '>' || mini->token->next->str[0] != '<'))
                    mini->token = mini->token->next;

        }
        else if(!invalid_input(mini, mini->token->str, env, 0))
        {
            // printf("dentro de invalid input, dentro de pipi_comand\n");
            bol = 0;
        }
        // printf("%s", mini->token->str);
        mini->token = mini->token->next;
    }
    return(bol);
}

int redirecctions_comand(t_mini *mini, char **env)
{
    printf("redirecctions>>ssss>\n");
    return(1);
}
