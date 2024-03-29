/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:34:42 by marvin            #+#    #+#             */
/*   Updated: 2024/03/12 17:34:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int next_alloc(char *line, int *i)
{
    int count;
    int j;
    char c;
    
    count = 0;
    j = 0;
    c = ' ';
    while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
            c = line[*i + j++];
        else if (c != ' ' && line[*i + j] == c)
        {
            count += 2;
            c = ' ';
            j++;
        }
        else
            j++;
        if (line[*i +j - 1] == '\\')
            count--;
    }
    return (j - count + 1);
}

int ft_alloc_created(char *line)
{
    int largo;

    largo = 0;
    while(line[largo] != 0)
    {
        // printf("%c", line[largo]);
        if(line[largo + 1] == '|' || line[largo + 1] == 0)
        {
            while ((line[largo] > 8 && line[largo] < 13) || line[largo] == 32)
		        largo--;
            break;
        }
        largo++;
    }
    return(largo);
}

t_token *created_token(char *line, int *i)
{
    t_token *token;
    int j;
    int k;

    j = ft_alloc_created(line + *i) + 1;
    k = 0;
    printf("\n%i\n", j);
    if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * j)))
        return (NULL);
    // printf("dentro\n");
    while(j-- > 0)
        token->str[k++] = line[(*i)++];
    token->str[k] = '\0';
    // printf("%s\n", token->str);
    return(token);
}

t_token *get_tokens(char *line)
{
    t_token *next;
    t_token *prev;
    int i;
    int sep;
    
    next = NULL;
    prev = NULL;
    i = 0;
    ft_jump_space(line, &i);
    while (line[i])
    {
        sep = ignore_sep(line, i);
        if(!no_comands(line + i))
            next = next_token(line, &i);
        else
            next = created_token(line, &i);
        next->prev = prev;
        if (prev)
            prev->next = next;
        prev = next;
        type_token(next, sep);
        ft_jump_space(line, &i);
    }
    if (next)
        next->next = NULL;
    while (next && next->prev)
    {
        next = next->prev;
    }
    return next;
}

void    ft_jump_space(const char *str, int *i)
{
    while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') || (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
        (*i)++;
}

static int ignore_sep(char *line, int i)
{
    if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
        return (1);
    else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
            && line[i + 2] && line[i + 2] == '>')
        return (1);
    return (0);
}

t_token *next_token(char *line, int *i)
{
    t_token *token;
    int j;
    int c;
    
    j = 0;
    c = ' ';
    if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
    {
        return (NULL);
    }
    while (line[*i] && (line[*i] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
            c = line[(*i)++];
        else if (c != ' ' && line[*i] == c)
        {
            c = ' ';
            (*i)++;
        }
        else if(line[*i] == '\\' && (*i)++)
        {
            token->str[j++] = line[(*i)++];
        }
        else
            token->str[j++] = line[(*i)++];
    }
    token->str[j] = '\0';
    return (token);
}

void type_token(t_token *token, int separator)
{
    if (ft_strcmp(token->str, "") == 0)
        token->type = EMPTY;
    else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
        token->type = TRUNC;
    else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
        token->type = APPEND;
    else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
        token->type = INPUT;
    else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
        token->type = PIPE;
    else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
        token->type = END;
    else if(token->prev == NULL || token->prev->type >= TRUNC)
        token->type = CMD;
    else
        token->type = ARG;
}