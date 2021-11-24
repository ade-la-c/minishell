/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 19:25:10 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lsttotoken(t_data *data, t_list *toklst)
{
	t_token		*token;
	t_token		*tokens;
	int			i;

	if (!toklst || !(data->toklst))
		return (NULL);
	tokens = malloc(sizeof(t_token) * data->toklen);
	if (!tokens)
		exit_error("malloc error");
	i = -1;
	while (++i < data->toklen && toklst)
	{
		token = (t_token *)toklst->content;
		tokens[i].content = ft_strdup(token->content);
		if (!tokens[i].content)
			exit_error("strdup failed");
		tokens[i].type = token->type;
		toklst = toklst->next;
	}
	data->toklen = i;
	// data->toklen = ft_lstsize(data->toklst);
	return (tokens);
}

static void	welding(t_data *d)
{
	int		i;
	t_list	*el;
	char	*buffer;

	i = 0;
	while (i < d->toklen)
	{
		if (d->toks[i].type >= WORD && d->toks[i].type <= SQUOTE_STR)
		{
			buffer = ft_strdup(d->toks[i++].content);
			if (!buffer)
				exit_error("strdup failed");
			while (i < d->toklen
				&& (d->toks[i].type >= WORD && d->toks[i].type <= SQUOTE_STR))
				buffer = strjoinfree(buffer, d->toks[i++].content, 1);
			el = new_token(buffer, WORD);
		}
		else if (d->toks[i].type == MYSPACE && ++i)
			continue ;
		else
		{
			el = new_token(ft_strdup(d->toks[i].content), d->toks[i].type);
			i++;
		}
		ft_lstadd_back(&(d->toklst), el);
	}
}

static int	checktokens(t_data *d)
{
	int	i;

	i = 0;
	if (d->toks[0].type == PIPE
		|| (d->toklen > 1 && d->toks[d->toklen - 1].type == PIPE))
	{
		return (write(STDERR_FILENO, "pipes must be between valid arguments\n", 39));
	}
	while (i < d->toklen)
	{
		if (d->toks[i].type <= DLESS && d->toks[i].type >= MORE)
		{
			if (++i < d->toklen && (d->toks[i].type <= DLESS
				&& d->toks[i].type >= MORE))
				return (write(STDERR_FILENO, "syntax error near unexpected token\n", 36));
		}
		else if (d->toks[i].type == PIPE)
		{
			if (++i < d->toklen && d->toks[i].type == PIPE)
				return (write(STDERR_FILENO, "syntax error near unexpected token\n", 36));
		}
		i++;
	}
	return (0);
}

int	parsing(t_data *data, char *line)
{
	int	i;

	i = 0;
	tokenizer(data, line);
	wordexpansion(data);
	data->toks = lsttotoken(data, data->toklst);
	data->toklen = ft_lstsize(data->toklst);
	ft_lstclear(&(data->toklst), free_tokel);
	welding(data);
	free_toks(data, data->toks);
	data->toks = lsttotoken(data, data->toklst);
	ft_lstclear(&(data->toklst), free_tokel);
	if (checktokens(data) == -1)
		return (-1);
	if (lexing(data) == -1)
		return (-1);
	return (0);
}
