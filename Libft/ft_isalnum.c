/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:35:58 by pramos            #+#    #+#             */
/*   Updated: 2023/01/12 12:11:29 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

int	ft_isalnum(int c)
{
	if (((c > 64 && c < 91) || (c > 96 && c < 123)) || (c > 47 && c < 58))
		return (1);
	return (0);
}