/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/09 19:40:31 by ade-la-c         ###   ########.fr       */
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
	ft_lstclear(&(data->toklst), free);
	return (tokens);
}

// /*

static void	welding(t_data *d)
{
	int		i;
	t_list	*el;
	char	*buffer;

	i = 0;
	while (i < d->toklen)
	{
		if ((!ft_strlen(d->toks[i].content) || d->toks[i].type == SPACE) && i++)
			continue ;
		else if (d->toks[i].type == WORD || d->toks[i].type == DQUOTE_STR
			|| d->toks[i].type == SQUOTE_STR)
		{
			buffer = ft_strdup(d->toks[i++].content);
			while (d->toks[i].type == WORD || d->toks[i].type == DQUOTE_STR
				|| d->toks[i].type == SQUOTE_STR)
				buffer = ft_strjoin(buffer, d->toks[i++].content);
			el = new_token(buffer, WORD);
		}
		else
		{
			el = new_token(d->toks[i].content, d->toks[i].type);
			i++;
		}
		ft_lstadd_back(&(d->toklst), el);
	}
	d->toklen = ft_lstsize(d->toklst);
}

// */

void	parsing(t_data *d, char *line)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	lexing(d, line);
	wordexpansion(d);
	d->toks = lsttotoken(d, d->toklst);
	welding(d);
	// print_tokens(d, d->toks);
	print_toklst(d->toklst, "printing : ");
}
