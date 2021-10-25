/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/25 16:24:05 by ade-la-c         ###   ########.fr       */
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
	toklstclear(&(data->toklst), free);
	return (tokens);
}

static void	wordexpansion(t_data *data)
{
	t_toklst	*tmptok;
	t_list		*tmplist;
	char		**strs;
	int			i;

	tmptok = data->toklst;
	tmplist = data->envlst;
	i = 0;
	while (data->toklst->next)
	{
		if (data->toklst->type == WORD || data->toklst->type == DQUOTE_STR)
		{
			while (data->envlst->next)
			{
				strs = (char **)data->envlst->content;
				if (!ft_strncmp(strs[0], (ft_strchr(data->toklst->content, '$') + 1), ft_strlen(strs[0])))
					printf("Success\n");
				data->envlst = data->envlst->next;
			}
		}
		data->toklst = data->toklst->next;
	}
	data->toklst = tmptok;
	data->envlst = tmplist;
}

void	parsing(t_data *d, char *line)
{
	int			i;
	int			j;
	// t_toklst	*tokel;

	i = 0;
	j = 0;
	lexing(d, line);
	wordexpansion(d);
	d->toks = lsttotoken(d, d->toklst);
}
