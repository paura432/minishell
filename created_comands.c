/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 11:10:00 by marvin           ###   ########.fr       */
/*  (input > 8 && input < 13) ||                                                                           */
/* ************************************************************************** */

#include"minishell.h"

int created_comands(char *input, t_mini *mini, char **env, int info_pos)
{
	int i;
	int bol;

	i = 0;
	bol = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (!ft_strncmp("echo", input + i,  4))
		bol = echo_comand(input + i + 4, mini, info_pos);
	if (!ft_strncmp("cd", input + i, 2))
		bol = cd_comand(input + i + 2, mini, info_pos);
	else if (!ft_strncmp("pwd", input + i, 3))
		bol = pwd_comand(input + i + 3, mini, info_pos);
	else if (!ft_strncmp("export", input + i, 6))
		bol = export_comand(input + i + 6, mini, info_pos);
	else if (!ft_strncmp("unset", input + i, 5))
		bol = unset_comand(input + i + 5, mini, info_pos);
	else if (!ft_strncmp("env", input + i, 3))
		bol = env_comand(input + i + 3, mini, info_pos);
	return(bol);
}

int cd_comand(char *input, t_mini *mini, int info_pos)
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

int echo_comand(char *input, t_mini *mini, int info_pos)
{
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int export_comand(char *input, t_mini *mini, int info_pos)
{
	int i;
	int j;

	i = 0;
	// printf("dentro de export\n");
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if(!dolar_parse_export(input, mini, info_pos))
		return(0);
	i = info_pos;
	while (mini->info[++i] != 0)
	{
		j = -1;
		while (mini->info[i][++j] != 0)
		{
			if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
				mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
				mini->info[i][j] == '_') || (mini->info[i][0] >= '0' && mini->info[i][0] <= '9') ||
				mini->info[i][j] == 'ñ')
				return (mini->info_y_created = i - 1, mini->info_y_comand = i, mini->error = 2, check_errors(mini), 0);
		}
	}
	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[i] == '-')
	   return (mini->error = 10, check_errors(mini), 0);
	if (input[i] >= '0' && input[i] <= '9')
		return (mini->error = 2, check_errors(mini), 0);
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int unset_comand(char *input, t_mini *mini, int info_pos)
{
	int i;

	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int pwd_comand(char *input, t_mini *mini, int info_pos)
{
	int i;

	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	return (0);
}

int env_comand(char *input, t_mini *mini, int info_pos)
{
	int i;

	i = 0;
	// printf("dentro de env");
	if (input[0] != ' ' && input[0] != 0)
		return (mini->error = 1, check_errors(mini), 0);
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if(input[i] == '*')
	{
		while(input[i] == '*')
			i++;
		if(input[i] == 0)
			return(mini->error = 9, mini->info_y_comand = info_pos, check_errors(mini), 0);
	}
	i = 0;
	while ((input[i] > 8 && input[i] < 13) || input[i] == 32)
		i++;
	if (input[i] == '$')
	{
		//env $-
		//env $6
		if((input[i] >= '0' && input[i] <= '9') && input[i + 1] == 0)
			return(1);
		//env $caracter alfanumerico y _
		if(!dolar_parse_env( input, mini, info_pos))
			return (mini->error = 8, check_errors(mini), 0);
		else
			return (1);
	}
	if (input[0] == ' ' || input[0] == 0)
		return (1);
	if (mini->info[info_pos] != 0 && access(mini->info[info_pos], F_OK) == -1 && input[i] != '$')
		return (mini->error = 7, check_errors(mini), 0);
	else
		return (mini->error = 4, check_errors(mini), 0);
	return (0);
}

int dolar_parse_env(char *input, t_mini *mini, int info_pos)
{
	int i;
	int j;

	i = info_pos;
	j = 0;
	// printf("dentro de dolar parse export");
	while (mini->info[i++] != 0)
	{
		// if(mini->info[i][0] != '$')
		// 	return (mini->info_x_comand = 0, mini->info_y_comand = i, 0);
		if (!((mini->info[i][1] >= 'a' && mini->info[i][1] <= 'z') || (mini->info[i][1] >= 'A' &&
			mini->info[i][1] <= 'Z') || mini->info[i][1] == '_') || mini->info[i][1] == 'ñ' ||
			(mini->info[i][1] >= '0' && mini->info[i][1] <= '9'))
			{
				if(mini->info[i][1] >= '0' && mini->info[i][1] <= '9')
					j = 2;
				return (mini->info_x_comand = j, mini->info_y_comand = i, check_errors(mini), 0);
			}	
		j = 0;
		while (mini->info[i][++j] != 0)
		{
			if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
				mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
				mini->info[i][j] == '_') || mini->info[i][j] == 'ñ')
					return (mini->info_x_comand = j, mini->info_y_comand = i, check_errors(mini), 0);		
		}
	}
	return (1);
}

int dolar_parse_export(char *input, t_mini *mini, int info_pos)
{
	int i;
	int j;

	i = info_pos;
	// printf("dentrop de dolar parse\n");
	while (mini->info[++i] != 0)
	{
		j = 0;
		if(mini->info[i][0] == '$')
		{
			if((mini->info[i][1] >= '0' && mini->info[i][1] <= '9') && (mini->info[i][2] >= '0' && mini->info[i][2] <= '9'))
				return(mini->info_x_comand = 2, mini->info_y_comand = i, 0);
			while (mini->info[i][++j] != 0)
			{
				if (!((mini->info[i][j] >= 'a' && mini->info[i][j] <= 'z') || (mini->info[i][j] >= 'A' &&
					mini->info[i][j] <= 'Z') || (mini->info[i][j] >= '0' && mini->info[i][j] <= '9') ||
					mini->info[i][j] == '_') || mini->info[i][j] == 'ñ')
						return (mini->error = 3, mini->info_x_comand = j, mini->info_y_comand = i, check_errors(mini), 0);
			}
		}
	}
	return (1);
}

		// if (!((mini->info[i][1] >= 'a' && mini->info[i][1] <= 'z') || (mini->info[i][1] >= 'A' &&
		// 	mini->info[i][1] <= 'Z') || mini->info[i][1] == '_') || mini->info[i][1] == 'ñ' ||
		// 	(mini->info[i][1] >= '0' && mini->info[i][1] <= '9'))
		// 	{
		// 		if(mini->info[i][1] >= '0' && mini->info[i][1] <= '9')
		// 			j++;
		// 		return (mini->info_x_comand = (j + 1), mini->info_y_comand = i, 0);
		// 	}	
		// j = 0;
