/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:42:28 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/02 19:11:42 by ade-la-c         ###   ########.fr       */
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

static int	expandword(t_token **token, t_list *envlst, int dollarpos)
{
	int		i;
	int		nextdollar;
	int		envlen;
	char	**strs;
	char	*tok;

	i = -1;
	nextdollar = 1;
	envlen = ft_lstsize(envlst);
	tok = (*token)->content;
	while (tok[dollarpos + nextdollar] && tok[dollarpos + nextdollar] != '$')
		nextdollar++;
	nextdollar += dollarpos;
	while (++i < envlen)
	{
		strs = (char **)envlst->content;
		if (!ft_strncmp(&tok[dollarpos + 1], strs[0], ft_strlen(strs[0])))
		{
			tok = writeexpansion(tok, strs[1], dollarpos,
					dollarpos + (int)ft_strlen(strs[0]));
			(*token)->content = tok;
			return ((int)ft_strlen(strs[1]));
		}
		envlst = envlst->next;
	}printf("~ %d %d\n", dollarpos, nextdollar);
	tok = writeexpansion(tok, "", dollarpos,
	nextdollar - 1);
	(*token)->content = tok;
	return (0);
}

void	wordexpansion(t_data *data)
{
	t_list		*tmptok;
	t_token		*token;
	int			i;
	int			j;

	if (!(data->toklst))
		return ;
	tmptok = data->toklst;
	i = 0;
	while (i < data->toklen && data->toklst)
	{
		token = (t_token *)data->toklst->content;
		if (token->type == WORD || token->type == DQUOTE_STR)
		{
			j = -1;
			while (++j < (int)ft_strlen(token->content))
				if (token->content[j] == '$')
					j += expandword(&(token), data->envlst, j) - 1;
		}
		data->toklst = data->toklst->next;
		i++;
	}
	data->toklst = tmptok;
}
