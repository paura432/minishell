/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:10 by pramos            #+#    #+#             */
/*   Updated: 2024/02/06 22:05:24 by marvin           ###   ########.fr       */
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
	char *input;

	if(ac > 2 && av == 0 && env == 0)
		return(0);

	signal_detecter();
	while(1)
	{
		input = readline("Minishell->");
		//detecta si es null y hace un exit cntrl + d
		if(input == 0)
			exit(0);
		invalid_input(input, env);
		free(input);
	}
	return(0);
}
