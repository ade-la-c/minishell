/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:31:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/30 16:40:55 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_list	*new_token(char *content, int type)
{
	t_token	*token;
	t_list	*el;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		exit_error("malloc failed");
	token->content = content;
	token->type = type;
	el = ft_lstnew((void *)token);
	return (el);
}

static int	handle_more_less(t_list **el, char *line)
{
	if (line[0] && line[1] && line[0] == CHR_MORE
		&& line[1] == CHR_MORE)
	{
		*el = new_token(ft_strdup(">>"), DMORE);
		return (1);
	}
	else if (line[0] && line[0] == CHR_MORE)
	{
		*el = new_token(ft_strdup(">"), MORE);
		return (0);
	}
	else if (line[0] && line[1] && line[0] == CHR_LESS
		&& line[1] == CHR_LESS)
	{
		*el = new_token(ft_strdup("<<"), DLESS);
		return (1);
	}
	else if (line[0] && line[0] == CHR_LESS)
	{
		*el = new_token(ft_strdup("<"), LESS);
		return (0);
	}
	else
		exit_error("handle more less");
	return (0);
}

static int	handle_quotes(t_list **el, char *line, char c)
{
	int	i;
	int	type;

	i = 0;
	if (c == CHR_DQUOTE)
		type = DQUOTE_STR;
	else
		type = SQUOTE_STR;
	while (line && line[i] && line[i] != c)
		i++;
	if (!line[i])
		exit_error("quotes must be closed");
	*el = new_token(ft_substr(line, 0, i), type);
	return (i);
}

static int	handle_word(t_list **el, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !(is_esymbol(line[i])))
		i++;
	*el = new_token(ft_substr(line, 0, i), WORD);
	return (i - 1);
}

void	lexing(t_data *data, char *line)
{
	int		i;
	t_list	*el;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == CHR_SPACE)
			el = new_token(ft_strdup(" "), SPACE);
		else if (line[i] == CHR_PIPE)
			el = new_token(ft_strdup("|"), SPACE);
		else if (line[i] == CHR_LESS || line[i] == CHR_MORE)
			i += handle_more_less(&(el), &line[i]);
		else if (line[i] == CHR_SQUOTE || line[i] == CHR_DQUOTE)
		{
			i += handle_quotes(&(el), &line[i + 1], line[i]);
			i++;
		}
		else
			i += handle_word(&(el), &line[i]);
		ft_lstadd_back(&(data->toklst), el);
		i++;
	}
	data->toklen = ft_lstsize(data->toklst);
}

	// print_toklst(data->toklst, "printing ou quoi");
