/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:54:35 by pramos            #+#    #+#             */
/*   Updated: 2024/03/15 19:34:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_errors(t_mini *mini, char *input)
{
    printf("%i\n", mini->error);
    if (mini->error == 0)
        return ;
    else if (mini->error == 1)
        printf("%s : command not found\n", input);
    else if (mini->error == 2)
        printf("%s: `%s': not a valid identifier\n", mini->comand, input);
    else if (mini->error == 3)
        printf("%s: `%s': not a valid identifier\n", mini->comand, input);
    else if (mini->error == 4)
        printf("%s: '%s': Permission denied\n", mini->comand, input);
    else if(mini->error == 5)
        printf("%s: '%s': too many arguments\n", mini->comand, input);
    else if(mini->error == 6)
        printf("%s: 'himBHs': No such file or directory\n", mini->comand, input);
    else if (mini->error == 7)
        printf("%s: %s: No such file or directory\n", mini->comand, input);
    else if (mini->error == 8)
        printf("%s: %s: No such file or directory\n", mini->comand, input);
    else if (mini->error == 9)
        printf("%s: '\033[A\033[B\033[3~': No such file or directory\n", mini->comand);
    else if (mini->error == 10)
        printf("%s: %s: invalid option\n", mini->comand, input);
}
