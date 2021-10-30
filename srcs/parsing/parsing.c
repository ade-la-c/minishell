/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:05:33 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/30 15:25:43 by ade-la-c         ###   ########.fr       */
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

/*

static char	*writeexpansion(char *content, int size, char **strs)
{
	char	*newcontent;
	int		i;
	int		j;

	newcontent = malloc(sizeof(char) * size);
	if (!newcontent)
		exit_error("malloc failed");
	i = 0;
	j = 0;
	while (content[i] && content[i] != '$')
		newcontent[j++] = content[i++];
	i += ft_strlen(strs[0]) + 1;
	while (*strs[1])
		newcontent[j++] = *strs[1]++;
	while (content[i])
		newcontent[j++] = content[i++];
				printf("%s\n", newcontent);
	return (newcontent);
}

static int	expandword(char **content, int pos, t_list *envlst)
{
	int		len;
	int		i;
	char	**strs;
	char	*newcontent;

	len = ft_lstsize(envlst);
	i = -1;
	while (++i < len)
	{
		strs = (char **)envlst->content;
		if (!ft_strncmp(content[pos], strs[0], ft_strlen(strs[0])))
		{
			newcontent = writeexpansion(*content, (ft_strlen(*content)
			- ft_strlen(strs[0]) + ft_strlen(strs[1])), strs);
			return (ft_strlen(strs[1]));
		}
		envlst = envlst->next;
	}
	return (1);
}

static void	wordexpansion(t_data *data)
{
	t_toklst	*tmptok;
	int			i;
	int			j;

	tmptok = data->toklst;
	i = 0;
	if (!(data->toklst))
		return ;
	while (i < data->toklen)
	{
		j = 0;
		if (data->toklst->type == WORD || data->toklst->type == DQUOTE_STR)
		{
			while (data->toklst->content[j])
			{
				if (data->toklst->content[j] == '$')
					j += expandword(&(data->toklst->content), j, data->envlst);
				else
					j++;
			}
		}
		i++;
	}
	data->toklst = tmptok;
}

// */

static char	*writeexpansion(char *str, char *expanded, int start, int end)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	new = ft_calloc(sizeof(char),
	((int)ft_strlen(str) - (end - start) + (int)ft_strlen(expanded) + 1));
	if (!new)
		exit_error("malloc failed");
	while (++i < start)
		new[i] = str[i];
	j = 0;
	while (j < (int)ft_strlen(expanded))
		new[i++] = expanded[j++];
	j = end;
	while (str[j])
		new[i++] = str[j++];
	free(str);
	return (new);
}

static int	expandword(t_toklst **toklst, t_list *envlst, int dollarpos)
{
	int		i;
	int		envlen;
	char	**strs;
	char	*token;
	char	*new;

	i = -1;
	envlen = ft_lstsize(envlst);
	token = (*toklst)->content;
	while (++i < envlen)
	{
		strs = (char **)envlst->content;
		printf("~ %s ~\n", strs[0]);
		if (!ft_strncmp(&token[dollarpos + 1], strs[0], ft_strlen(strs[0])))
		{
			printf("succes\n");			//!code to fix, printfs to move
			new = writeexpansion(token, strs[1], dollarpos,
			dollarpos + (int)ft_strlen(strs[0]));
			(*toklst)->content = new;
			return ((int)ft_strlen(strs[1]));
		}
		envlst = envlst->next;
	}
	return (0);
}

static void	wordexpansion(t_data *data)
{
	t_toklst	*tmptok;
	int			i;
	int			j;

	if (!(data->toklst))
		return ;
	tmptok = data->toklst;
	i = 0;
	while (i < data->toklen && data->toklst)
	{
		if (data->toklst->type == WORD || data->toklst->type == DQUOTE_STR)
		{
			j = -1;
			while (++j < (int)ft_strlen(data->toklst->content))
				if (data->toklst->content[j] == '$')
				{
					j += expandword(&(data->toklst), data->envlst, j);
				}
		}
		data->toklst = data->toklst->next;
		i++;
	}
	data->toklst = tmptok;
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
	print_toklst(d->toklst, "printing ou quoi");
	d->toks = lsttotoken(d, d->toklst);
}
