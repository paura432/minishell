/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:10 by pramos            #+#    #+#             */
/*   Updated: 2024/01/30 00:28:39 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal(char *readline)
{
	
}

int	main(int ac, char **av, char **env)
{
	if(ac > 2)
		return(0);
	env = 0;
	av = 0;
	while(1)
	{
		readline("Minishell->");
		signal(readline);
	}

	return(0);
}
