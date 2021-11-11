/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:50:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/11 15:36:07 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_prog	*init_prog(t_data *d, int index)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (index + i < d->toklen && d->toks[index + i].type != PIPE)
	{
		i++;
	}
	printf("i : %d\n", i);
	prog = malloc(sizeof(t_prog));
	prog->av = malloc(sizeof(char *) * (i + 1));
	prog->fdin = STDIN_FILENO;
	prog->fdout = STDOUT_FILENO;
	return (prog);
}

void	lexing(t_data *d)
{
	int		i;
	int		j;
	t_prog	*prog;
	t_list	*el;

	i = 0;
	prog = NULL;
	while (i < d->toklen)
	{
		j = 0;
		if (!prog)
			prog = init_prog(d, i);
		while (d->toks[i].type != PIPE && i < d->toklen)
		{
			prog->av[j++] = ft_strdup(d->toks[i++].content);
		}
		if (i == d->toklen || d->toks[i++].type == PIPE)
		{
			el = ft_lstnew((void *)prog);
			ft_lstadd_back(&(d->proglst), el);
			prog = NULL;
		}
	}
}
