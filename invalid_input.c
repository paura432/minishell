/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:33:32 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 21:33:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    free_split(char **inf)
{
    int i;

    i = 0;
	while (inf[++i] != 0)
		free(inf[i]);
	free(inf);
}

int	invalid_input(char *input)
{
	int i;
    char **inf;

    i = 0;
    inf = ft_split(input, ' ');
    while(inf[i])
    {
        printf("%s : command not found\n", inf[0]);
        if(access(inf[i], X_OK) != 0)
        {
            printf("%s : command not found\n", inf[0]);
            free_split(inf);
            return(0);
        }
        i++;
    }
}