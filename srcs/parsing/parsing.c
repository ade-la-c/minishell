/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/04 18:57:03 by ade-la-c         ###   ########.fr       */
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

void	parsetokens(t_data *data)
{
	int	i;
	t_list	*head;
	t_list	*head2;
	t_token	*token;

	i = -1;
	head = data->toklst;
	head2 = data->toklst;
	while (++i < data->toklen && data->toklst->next)
	{
		token = (t_token *)data->toklst->content;
		if (token->type == SPACE)
		{
			ft_removeelement(&(head), SPACE);
			data->toklen = ft_lstsize(data->toklst);
		}
		data->toklst = data->toklst->next;//printf("oui\n");
	}
	data->toklst = head2;
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
	// parsetokens(d);
	// d->toks = lsttotoken(d, d->toklst);
}

