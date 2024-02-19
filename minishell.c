/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:10 by pramos            #+#    #+#             */
/*   Updated: 2024/02/18 22:38:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sign)
{
	if(sign == SIGINT)
	{
		printf("\nMinishell->");
	}
}

void    signal_detecter(void)
{
	//SIGINT es la señal cntrl + c
    signal(SIGINT, handle_signal);
	//SIG_ING ignora la señal en este caso cntrl + "\"
    signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini));
	if(ac > 2 && av == 0 && env == 0)
		return(0);

	signal_detecter();
	while(1)
	{
		mini->input = readline("Minishell->");
		//detecta si es null y hace un exit cntrl + d
		if(mini->input == 0)
			exit(0);
		go_comands(mini, env);
		free(mini->input);
	}
	return(0);
}
