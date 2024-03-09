/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:54:35 by pramos            #+#    #+#             */
/*   Updated: 2024/03/09 15:13:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_errors(t_mini *mini)
{
    if (mini->error == 0)
        return ;
    else if (mini->error == 1)
        printf("%s : command not found\n", mini->info[0]);
    else if (mini->error == 2)
        printf("%s: `%s': not a valid identifier\n", mini->info[0], mini->info[mini->info_position_i]);
    else if (mini->error == 3)
        printf("%s: %s: invalid option\n", mini->info[0], mini->info[1]);
    else if (mini->error == 4)
        printf("%s: '%s': Permission denied\n", mini->info[0], mini->info[1]);
    else if(mini->error == 5)
        printf("%s: '%s': too many arguments\n", mini->info[0], mini->info[1]);
    else if(mini->error == 6)
        printf("%s: 'himBHs': No such file or directory\n", mini->info[0]);
    else if (mini->error == 7)
        printf("%s: %s: No such file or directory\n", mini->info[0], mini->info[1]);
    else if (mini->error == 8)
        printf("%s: %s: No such file or directory\n", mini->info[0], mini->info[mini->info_position_i] + mini->info_position_j);
}
