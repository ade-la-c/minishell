/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/11 15:36:10 by ade-la-c         ###   ########.fr       */
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
	tokens = malloc(sizeof(t_token) * ++data->toklen);
	if (!tokens)
		exit_error("malloc failed");
	i = -1;
	while (++i < data->toklen && toklst)
	{
		token = (t_token *)toklst->content;
		tokens[i].content = token->content;
		tokens[i].type = token->type;
		toklst = toklst->next;
	}
	data->toklen = ft_lstsize(data->toklst);
	return (tokens);
}

// /*.

static void	welding(t_data *d)
{
	int		i;
	t_list	*el;
	char	*buffer;

	i = 0;
	while (i < d->toklen)
	{
		if (d->toks[i].type == WORD || d->toks[i].type == DQUOTE_STR
			|| d->toks[i].type == SQUOTE_STR)
		{
			buffer = ft_strdup(d->toks[i++].content);
			while ((d->toks[i].type == WORD || d->toks[i].type == DQUOTE_STR
				|| d->toks[i].type == SQUOTE_STR) && d->toklen)
				buffer = ft_strjoin(buffer, d->toks[i++].content);
			el = new_token(buffer, WORD);
		}
		else if (d->toks[i].type == SPACE && ++i)
			continue ;
		else
		{
			el = new_token(ft_strdup(d->toks[i].content), d->toks[i].type);
			i++;
		}
		ft_lstadd_back(&(d->toklst), el);
	}
}

// */

static void	checktokens(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->toklen)
	{
		if (d->toks[i].type == DLESS || d->toks[i].type == DMORE
			|| d->toks[i].type == LESS || d->toks[i].type == MORE)
			if (++i < d->toklen && (d->toks[i].type == DLESS
				|| d->toks[i].type == DMORE || d->toks[i].type == LESS
				|| d->toks[i].type == MORE))
				exit_error("too many redirections");
		i++;
	}
}

void	parsing(t_data *data, char *line)
{
	int	i;

	i = 0;
	tokenizer(data, line);
	wordexpansion(data);
	data->toks = lsttotoken(data, data->toklst);
	ft_lstclear(&(data->toklst), free);
	welding(data);
	data->toklen = ft_lstsize(data->toklst);
	while (i < data->toklen)
		free(data->toks[i++].content);
	free(data->toks);
	data->toks = lsttotoken(data, data->toklst);
	checktokens(data);
	lexing(data);
	print_toklst(data->toklst, "printing : ");
}

	// print_tokens(d, d->toks);
