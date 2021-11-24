/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:42:28 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 19:05:52 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static char	*writeexpansion(char *str, char *expanded, int start, int end)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	new = ft_calloc(sizeof(char),
			(ft_strlen(str) - (end - start) + ft_strlen(expanded)));
	if (!new)
		exit_error("malloc failed");
	while (++i < start)
		new[i] = str[i];
	j = 0;
	while (j < (int)ft_strlen(expanded))
		new[i++] = expanded[j++];
	j = end + 1;
	while (str[j])
		new[i++] = str[j++];
	free(str);
	return (new);
}

static int	expandword(char **tok, t_list *envlst, int dpos)
{
	int		lim;
	char	**strs;
	char	*token;
	char	*retstr;

	lim = 1;
	token = *tok;
	while (token[dpos + lim] != '$'
		&& (token[dpos + lim] == '_' || ft_isalnum(token[dpos + lim])))
		lim++;
	lim += dpos;
	if (token[dpos + 1] == '?')
	{
		retstr = ft_itoa(retval);
		if (!retstr)
			exit_error("itoa failed");
		token = writeexpansion(token, retstr, dpos, lim);
		free(retstr);
		*tok = token;
		return (1);
	}
	if (!token[dpos + 1] || lim == dpos + 1)
		return (1);
	strs = get_env(envlst, &token[dpos + 1], lim - dpos - 1);
	if (!strs)
	{
		token = writeexpansion(token, "", dpos, lim - 1);
		*tok = token;
		return (0);
	}
	token = writeexpansion(token, strs[1], dpos, lim - 1);
	*tok = token;
	return (ft_strlen(strs[1]));
}

char	*expandheredoc(t_data *d, char *str)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] == '$')
		{
			i += expandword(&(str), d->envlst, i) - 1;
		}
	return (str);
}

void	wordexpansion(t_data *data)
{
	t_list		*tmptok;
	t_token		*token;
	int			i;
	int			j;
	char		*tok;

	if (!(data->toklst))
		return ;
	tmptok = data->toklst;
	i = 0;
	while (i < data->toklen && data->toklst)
	{
		token = (t_token *)data->toklst->content;
		if (token->type == WORD || token->type == DQUOTE_STR)
		{
			tok = token->content;
			j = -1;
			while (++j < (int)ft_strlen(tok))
				if (tok[j] == '$')
				{
					j += expandword(&(tok), data->envlst, j) - 1;
				}
			token->content = tok;
		}
		data->toklst = data->toklst->next;
		i++;
	}
	data->toklst = tmptok;
}
