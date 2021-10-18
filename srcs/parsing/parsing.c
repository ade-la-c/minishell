/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:56:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/18 17:48:27 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing(t_data *data, char *line)
{
	int			i;
	int			j;
	t_toklst	*toklst;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		j = 0;
		if (ft_isalnum(line[i]) == 1)
		{
			while (ft_isalnum(line[i + j]))
				j++;
			toklst = toklstnew(ft_substr(line, i, j), WORD);
			i += j;
		}
		else if (line[i] == CHR_SPACE)
		{
			toklst = toklstnew(ft_strdup(" "), SPACE);
			i++;
		}
		else if (line[i] == CHR_DQUOTE)
		{
			i++;
			while (line[i + j] && line[i + j] != CHR_DQUOTE)
				j++;
			toklst = toklstnew(ft_substr(line, i, j), DQUOTE_STR);
			i += j;
		}
		else if (line[i] == CHR_SQUOTE)
		{
			i++;
			while (line[i + j] && line[i + j] != CHR_SQUOTE)
				j++;
			toklst = toklstnew(ft_substr(line, i, j), SQUOTE_STR);
			i += j;
		}
		else if (line[i] == CHR_LESS)
		{
			if (line && line[++i] == CHR_LESS)
				toklst = toklstnew(ft_strdup("<<"), DLESS);
			else
				toklst = toklstnew(ft_strdup("<"), LESS);
			i++;
		}
		else if (line[i] == CHR_MORE)
		{
			if (line && line[++i] == CHR_MORE)
				toklst = toklstnew(ft_strdup(">>"), DMORE);
			else
				toklst = toklstnew(ft_strdup(">"), MORE);
			i++;
		}
		else if (line[i] == CHR_PIPE)
		{
			toklst = toklstnew(ft_strdup("|"), PIPE);
			i++;
		}
		else
			exit_error("parsing");
		printf("%s\n", toklst->content);
		toklstadd_back(&(data->toklst), toklst);
	}
	// print_toklst(data->toklst);
}
