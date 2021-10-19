/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:56:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/19 20:51:44 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	lexing(t_data *data, char *line)
{
	t_toklst	*tokel;
	t_toklst	**toklst;
	int			i;
	int			j;

	toklst = malloc(sizeof(t_toklst *));
	if (!toklst)
		exit_error("malloc failed");
	*toklst = NULL;
	i = 0;
	while (line && line[i])
	{
		j = 0;
		if (line[i] == ' ')
			i++;
		while (line[i + j] && ft_isalnum(line[i + j]))
			j++;
		tokel = toklstnew(ft_substr(line, i, j), WORD);
		if (!tokel)
			exit_error("toklstnew crash");
		toklstadd_back(toklst, tokel);
		i += j;
	}
		tokel = toklstnew(ft_substr(line, i, j), WORD);
		if (!tokel)
			exit_error("toklstnew crash");
		toklstadd_back(toklst, tokel);
	data->toklst = toklst;
	print_toklst(*toklst, "printing");
}

// void	parsing(t_data *data, char *line)
// {
// 	int			i;
// 	int			j;
// 	t_toklst	*tokel;
// 	t_toklst	**toklst;

// 	i = 0;
// 	j = 0;
// 	toklst = malloc(sizeof(t_toklst *));
// 	if (!toklst)
// 		exit_error("malloc failed");
// 	*toklst = NULL;
// 	while (line && line[i])
// 	{
// 		j = 0;
// 		if (ft_isalnum(line[i]) == 1)
// 		{
// 			while (ft_isalnum(line[i + j]))
// 				j++;
// 			tokel = toklstnew(ft_substr(line, i, j), WORD);
// 			i += j;
// 		}
// 		else if (line[i] == CHR_SPACE)
// 		{
// 			tokel = toklstnew(ft_strdup(" "), SPACE);
// 			i++;
// 		}
// 		else if (line[i] == CHR_DQUOTE)
// 		{
// 			i++;
// 			while (line[i + j] && line[i + j] != CHR_DQUOTE)
// 				j++;
// 			tokel = toklstnew(ft_substr(line, i, j), DQUOTE_STR);
// 			i += j;
// 		}
// 		else if (line[i] == CHR_SQUOTE)
// 		{
// 			i++;
// 			while (line[i + j] && line[i + j] != CHR_SQUOTE)
// 				j++;
// 			tokel = toklstnew(ft_substr(line, i, j), SQUOTE_STR);
// 			i += j;
// 		}
// 		else if (line[i] == CHR_LESS)
// 		{
// 			if (line && line[++i] == CHR_LESS)
// 				tokel = toklstnew(ft_strdup("<<"), DLESS);
// 			else
// 				tokel = toklstnew(ft_strdup("<"), LESS);
// 			i++;
// 		}
// 		else if (line[i] == CHR_MORE)
// 		{
// 			if (line && line[++i] == CHR_MORE)
// 				tokel = toklstnew(ft_strdup(">>"), DMORE);
// 			else
// 				tokel = toklstnew(ft_strdup(">"), MORE);
// 			i++;
// 		}
// 		else if (line[i] == CHR_PIPE)
// 		{
// 			tokel = toklstnew(ft_strdup("|"), PIPE);
// 			i++;
// 		}
// 		else
// 			exit_error("parsing");
// 		printf("~ %s\n", tokel->content);
// 		toklstadd_back(toklst, tokel);
// 	}
// 	data->toklst = *toklst;
// 	print_toklst(data->toklst, "printing");
// }
