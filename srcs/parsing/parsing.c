/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:56:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/18 13:44:41 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		j = 0;
		if (ft_isalnum(line[i]))
		{
			while (ft_isalnum(line[i + j]))
				j++;
			toklstadd_back(&(data->toklst), toklstnew(ft_substr(line, i, j), WORD));
			i += j;
		}
		else if (line[i] == CHR_SPACE)
		{
			toklstadd_back(&(data->toklst), toklstnew(ft_strdup(" "), SPACE));
			i++;
		}
		else if (line[i] == CHR_DQUOTE)
		{
			i++;
			while (line[i + j] && line[i + j] != CHR_DQUOTE)
				j++;
			toklstadd_back(&(data->toklst), toklstnew(ft_substr(line, i, j), DQUOTE_STR));
			i += j;
		}
		else if (line[i] == CHR_SQUOTE)
		{
			i++;
			while (line[i + j] && line[i + j] != CHR_SQUOTE)
				j++;
			toklstadd_back(&(data->toklst), toklstnew(ft_substr(line, i, j), SQUOTE_STR));
			i += j;
		}
		else if (line[i] == CHR_LESS)
		{
			if (line && line[++i] == CHR_LESS)
				toklstadd_back(&(data->toklst), toklstnew(ft_strdup("<<"), DLESS));
			else
				toklstadd_back(&(data->toklst), toklstnew(ft_strdup("<"), LESS));
			i++;
		}
		else if (line[i] == CHR_MORE)
		{
			if (line && line[++i] == CHR_MORE)
				toklstadd_back(&(data->toklst), toklstnew(ft_strdup("<<"), DMORE));
			else
				toklstadd_back(&(data->toklst), toklstnew(ft_strdup("<"), MORE));
			i++;
		}
		else if (line[i] == CHR_PIPE)
		{
			toklstadd_back(&(data->toklst), toklstnew(ft_strdup("|"), PIPE));
			i++;
		}
		else
			exit_error("parsing");
	}
	// printf("oui\n");
	print_toklst(data->toklst);
}
