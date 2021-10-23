/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:56:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/23 13:11:07 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_more_less(t_toklst **tokel, char *line)
{
	if (line[0] && line[1] && line[0] == CHR_MORE
		&& line[1] == CHR_MORE)
	{
		*tokel = toklstnew(ft_strdup(">>"), DMORE);
		return (1);
	}
	else if (line[0] && line[0] == CHR_MORE)
	{
		*tokel = toklstnew(ft_strdup(">"), MORE);
		return (0);
	}
	else if (line[0] && line[1] && line[0] == CHR_LESS
		&& line[1] == CHR_LESS)
	{
		*tokel = toklstnew(ft_strdup("<<"), DLESS);
		return (1);
	}
	else if (line[0] && line[0] == CHR_LESS)
	{
		*tokel = toklstnew(ft_strdup("<"), LESS);
		return (0);
	}
	else
		exit_error("handle more less");
	return (0);
}

static int	handle_quotes(t_toklst **tokel, char *line, char c)
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
	*tokel = toklstnew(ft_substr(line, 0, i), type);
	return (i);
}

static int	handle_word(t_toklst **tokel, char *line)
{
	int	i;

	i = 0;
	while (line[i] && !(is_esymbol(line[i])))
		i++;
	*tokel = toklstnew(ft_substr(line, 0, i), WORD);
	return (i - 1);
}

void	lexing(t_data *data, char *line)
{
	int			i;
	t_toklst	*tokel;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == CHR_SPACE)
			tokel = toklstnew(ft_strdup(" "), SPACE);
		else if (line[i] == CHR_PIPE)
			tokel = toklstnew(ft_strdup("|"), PIPE);
		else if (line[i] == CHR_LESS || line[i] == CHR_MORE)
			i += handle_more_less(&(tokel), &line[i]);
		else if (line[i] == CHR_SQUOTE || line[i] == CHR_DQUOTE)
		{
			i += handle_quotes(&(tokel), &line[i + 1], line[i]);
			i++;
		}
		else
			i += handle_word(&(tokel), &line[i]);
		toklstadd_back(&(data->toklst), tokel);
		i++;
	}
}

	// print_toklst(data->toklst, "printing");
