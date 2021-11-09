/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/09 14:32:58 by ade-la-c         ###   ########.fr       */
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
	// ft_lstclear(&(data->toklst), free);
	return (tokens);
}

// /*

static void	tokenparser(t_data *data)
{
	int		i;
	t_list	*tmp;
	t_token	*token;

	i = 0;
	if (!data->toklst)
		return ;
	tmp = data->toklst;
	while (i < data->toklen && data->toklst)
	{
		token = (t_token *)data->toklst->content;
		if (token->type == PIPE)
		{
			remove_element(&(tmp), data->toklst->content);
			data->toklen--;
			data->toklst = data->toklst->next;
			continue ;
		}
		else
		{
			data->toklst = data->toklst->next;
			i++;
		printf("hello\n");
		}
	}
	data->toklst = tmp;
}

// */

// static void	token_parser(t_data *data)
// {

// }

void	parsing(t_data *d, char *line)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	lexing(d, line);
	wordexpansion(d);
	tokenparser(d);
	print_toklst(d->toklst, "printing : ");
	// d->toks = lsttotoken(d, d->toklst);
}
