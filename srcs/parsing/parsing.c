/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:05:42 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:38 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lsttotoken(t_data *data, t_toklst *toklst)
{
	t_token		*tokens;
	int			i;

	if (!toklst)
		return (NULL);
	data->toklen = 0;
	while (toklst->next)
	{
		data->toklen++;
		toklst = toklst->next;
	}
	tokens = malloc(sizeof(t_token) * ++data->toklen);
	if (!tokens)
		exit_error("malloc failed");
	i = -1;
	while (++i < data->toklen)
	{
		tokens[i].content = data->toklst->content;
		tokens[i].type = data->toklst->type;
		data->toklst = data->toklst->next;
	}
	return (tokens);
}

void	parsing(t_data *data, char *line)
{
	int		i;
	t_token	*newtokens;

	i = 0;
	lexing(data, line);
	data->tokens = lsttotoken(data, data->toklst);
	while (data->tokens && data->tokens[i])
	{
		if (data->tokens[i].type == SPACE)
			i++;
	}
}
