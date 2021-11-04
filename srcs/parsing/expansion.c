/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:42:28 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/04 19:34:21 by ade-la-c         ###   ########.fr       */
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
			printf("new malloc : %d\n", (int)(ft_strlen(str) - (end - start) + ft_strlen(expanded)));
	while (++i < start)
		new[i] = str[i];
	j = 0;printf("expanded : %s\n", expanded);
	while (j < (int)ft_strlen(expanded))
		new[i++] = expanded[j++];
	j = end + 1;
	while (str[j])
		new[i++] = str[j++];
	free(str);
	return (new);
}

/*

static int	expandword(t_token **token, t_list *envlst, int dollarpos)
{
	int		i;
	int		nextdollar;
	int		varlimit;
	char	**strs;
	char	*tok;
	int		envlen;

	i = -1;
	nextdollar = 0;
	varlimit = 0;
	envlen = ft_lstsize(envlst);
	tok = (*token)->content;
	while (++nextdollar && tok[dollarpos + nextdollar] && tok[dollarpos + nextdollar] != '$')
		if (ft_isalnum(tok[dollarpos + nextdollar]) || tok[dollarpos + nextdollar] == '_')
			varlimit++;
	nextdollar += dollarpos;printf("%d\n", varlimit);
	while (++i < envlen)
	{
		strs = (char **)envlst->content;
		if (!tok[dollarpos + 1])
			return (1);
		if (!ft_strncmp(&tok[dollarpos + 1], strs[0], varlimit))
		{printf("nextdollar : %d\n", nextdollar);
			tok = writeexpansion(tok, strs[1], dollarpos,
					dollarpos + (int)ft_strlen(strs[0]));
			(*token)->content = tok;
			return ((int)ft_strlen(strs[1]));
		}
		envlst = envlst->next;
	}//printf("~ %d %d\n", dollarpos, nextdollar);
	tok = writeexpansion(tok, "", dollarpos,
	nextdollar - 1);
	(*token)->content = tok;
	return (1);
}

// */

static int	expandword(t_token **token, t_list *envlst, int dolpos)
{
	int		nextdol;
	int		limit;
	char	**strs;
	char	*tok;
	nextdol = 1;
	limit = 1;
	tok = (*token)->content;
// printf("::> %s\n", &tok[dolpos]);
	while (tok[dolpos + nextdol] && tok[dolpos + nextdol] != '$')
		nextdol++;
		nextdol += dolpos;
	while (tok[dolpos + limit] &&
		(ft_isalnum(tok[dolpos + limit]) || tok[dolpos + limit] == '_'))
		limit++;
	limit += dolpos;
printf("$P : %d[%c], L : %d[%c], N$ : %d[%c]\n", dolpos, tok[dolpos], limit, tok[limit], nextdol, tok[nextdol]);
	if (tok[dolpos + 1])
	{
		strs = get_env(envlst, &tok[dolpos + 1]);//! don't test limit - 1
		if (!strs)
		{
			if (limit == dolpos + 1)
				return (0);
			tok = writeexpansion(tok, "", dolpos, limit - 1);
			(*token)->content = tok;
			return (0);
		}
		printf("key : %s\n", strs[0]);
		tok = writeexpansion(tok, strs[1], dolpos, limit - 1);
		(*token)->content = tok;
		return (ft_strlen(strs[1]));
	}
	return (1);
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
				{
					j += expandword(&(token), data->envlst, j) - 1;
					printf("j : %d\n", j);
				}
		}
		data->toklst = data->toklst->next;
		i++;
	}
	data->toklst = tmptok;
}
