/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/01 13:47:00 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lsttotoken(t_data *data, t_list *toklst)
{
	t_token		*token;
	t_token		*tokens;
	int			i;

	if (!toklst)
		return (NULL);
	tokens = malloc(sizeof(t_token) * ++data->toklen);
	if (!tokens)
		exit_error("malloc failed");
	i = -1;
	while (++i < data->toklen)
	{
		token = (t_token *)data->toklst->content;
		tokens[i].content = token->content;
		tokens[i].type = token->type;
		data->toklst = data->toklst->next;
	}
	ft_lstclear(&(data->toklst), free);
	return (tokens);
}

void	parsing(t_data *d, char *line)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	lexing(d, line);
	wordexpansion(d);
	print_toklst(d->toklst, "printing : ");
}

	// d->toks = lsttotoken(d, d->toklst);
