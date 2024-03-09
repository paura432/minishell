/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:00 by marvin           ###   ########.fr       */
/*  (mini->input > 8 && mini->input < 13) ||                                                                           */
/* ************************************************************************** */

#include"minishell.h"

int created_comands(t_mini *mini, char **env)
{
	int i;
	int bol;

	i = 0;
	bol = 0;

	while ((mini->input[i] > 8 && mini->input[i] < 13) || mini->input[i] == 32)
		i++;
	if (!ft_strncmp("echo", mini->input + i,  4))
		bol = echo_comand(mini->input + i + 4, mini);
	if (!ft_strncmp("cd", mini->input + i, 2))
		bol = cd_comand(mini->input + i + 2, mini);
	else if (!ft_strncmp("pwd", mini->input + i, 3))
		bol = pwd_comand(mini->input + i + 3, mini);
	else if (!ft_strncmp("export", mini->input + i, 6))
		bol = export_comand(mini->input + i + 6, mini);
	else if (!ft_strncmp("unset", mini->input + i, 5))
		bol = unset_comand(mini->input + i + 5, mini);
	else if (!ft_strncmp("env", mini->input + i, 3))
		bol = env_comand(mini->input + i + 3, mini);
	return(bol);
}

int cd_comand(char *input, t_mini *mini)
{
	int i;

	i = 0;
	//saltamos todos los espacios
	//printf("%s\n", input);
	if (mini->info[2] != 0)
		return(mini->error = 5, 0);
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[i] == 0)
		return(1);
	if ((chdir(input + i)))
		return (mini->error = 7, 0);
	return (1);
}

int echo_comand(char *input, t_mini *mini)
{
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int export_comand(char *input, t_mini *mini)
{
	int i;
	int j;

	i = 0;
	if(input[i] == '$')
		if(dolar_parse_export(input, mini))
			return(0);
	while (mini->info[++i] != 0)
	{
		j = -1;
		while (mini->info[i][++j] != 0)
		{
			if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
				mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
				mini->info[i][j] == '_') || (mini->info[i][0] >= '0' && mini->info[i][0] <= '9') ||
				mini->info[i][j] == 'ñ')
				return (mini->info_position_i = i, mini->error = 2, i, 0);
		}
	}
	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	
	if (input[i] == '-')
	   return (mini->error = 3, 0);
	if (input[i] >= '0' && input[i] <= '9')
		return (mini->error = 2, 0);
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int unset_comand(char *input, t_mini *mini)
{
	int i;

	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int pwd_comand(char *input, t_mini *mini)
{
	int i;

	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int env_comand(char *input, t_mini *mini)
{
	int i;

	i = 0;
	if (input[0] != ' ' && input[0] != 0)
		return (mini->error = 1, 0);
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if(input[i] == '*')
	{
		while(input[i] == '*')
			i++;
		if(input[i] == 0)
			return(mini->error = 9, 0);
	}
	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[i] == '$')
	{
		//env $-
		if(input[++i] == '-')
			return (mini->error = 6, i, 0);
		//env $6
		if((input[i] >= '0' && input[i] <= '9') && input[i + 1] == 0)
			return(1);
		//env $caracter alfanumerico y _
		if(!dolar_parse_env( input, mini))
			return (mini->error = 8, 0);
		else
			return (1);
	}
	if ((input[0] == ' ' || input[0] == 0) && mini->info[1] == 0 )
		return (1);
	if (mini->info[1] != 0 && access(mini->info[1], F_OK) == -1 && input[i] != '$')
		return (mini->error = 7, 0);
	else
		return (mini->error = 4, 0);
	return (0);
}

int dolar_parse_env(char *input, t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->info[++i] != 0)
	{
		if(mini->info[i][0] != '$')
			return (mini->info_position_j = 0, mini->info_position_i = i, 0);
		if (!((mini->info[i][1] >= 'a' && mini->info[i][1] <= 'z') || (mini->info[i][1] >= 'A' &&
			mini->info[i][1] <= 'Z') || mini->info[i][1] == '_') || mini->info[i][1] == 'ñ' ||
			(mini->info[i][1] >= '0' && mini->info[i][1] <= '9'))
			{
				if(mini->info[i][1] >= '0' && mini->info[i][1] <= '9')
					j = 2;
				return (mini->info_position_j = j, mini->info_position_i = i, 0);
			}	
		j = 0;
		while (mini->info[i][++j] != 0)
		{
			if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
				mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
				mini->info[i][j] == '_') || mini->info[i][j] == 'ñ')

					return (mini->info_position_j = j, mini->info_position_i = i, 0);		
		}
	}
	return (1);
}

int dolar_parse_export(char *input, t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->info[++i] != 0)
	{
		if (!((mini->info[i][1] >= 'a' && mini->info[i][1] <= 'z') || (mini->info[i][1] >= 'A' &&
			mini->info[i][1] <= 'Z') || mini->info[i][1] == '_') || mini->info[i][1] == 'ñ' ||
			(mini->info[i][1] >= '0' && mini->info[i][1] <= '9'))
			{
				if(mini->info[i][1] >= '0' && mini->info[i][1] <= '9')
					j++;
				return (mini->info_position_j = (j + 1), mini->info_position_i = i, 0);
			}	
		j = 0;
		while (mini->info[i][++j] != 0)
		{
			if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
				mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
				mini->info[i][j] == '_') || mini->info[i][j] == 'ñ')

					return (mini->info_position_j = j, mini->info_position_i = i, 0);		
		}
	}
	return (1);
}
