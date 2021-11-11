/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:50:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/11 18:58:32 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_prog	*init_prog(t_data *d, int index)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (index + i < d->toklen && d->toks[index + i].type != PIPE)
		i++;
	prog = malloc(sizeof(t_prog));
	prog->av = calloc(sizeof(char *), (i + 1));
	prog->fdin = STDIN_FILENO;
	prog->fdout = STDOUT_FILENO;
	return (prog);
}

static void	tokentoprog(t_data *d)
{
	int		i;
	int		j;
	t_prog	*prog;
	t_list	*el;

	i = 0;
	prog = NULL;
	if (d->toks[0].type == PIPE || d->toks[d->toklen].type == PIPE)
		exit_error("pipes");
	while (i < d->toklen)
	{
		j = 0;
		if (!prog)
			prog = init_prog(d, i);
		while (d->toks[i].type != PIPE && i < d->toklen)
			prog->av[j++] = ft_strdup(d->toks[i++].content);
		if (i == d->toklen || d->toks[i++].type == PIPE)
		{
			el = ft_lstnew((void *)prog);
			ft_lstadd_back(&(d->proglst), el);
			prog = NULL;
		}
	}
	d->proglen = ft_lstsize(d->proglst);
	print_proglst(d->proglst, "imprimiendo");
}

static t_prog	*lsttoprog(t_data *data, t_list *proglst)
{
	t_prog	*prog;
	t_prog	*progs;
	int		i;

	if (!proglst || !(data->proglst))
		return (NULL);
	i = -1;
	progs = malloc(sizeof(t_prog) * data->proglen);
	if (!progs)
		exit_error("maloc error");
	while (++i < data->proglen)
	{
		prog = (t_prog *)proglst->content;
		progs[i].av = prog->av;
		progs[i].fdin = prog->fdin;
		progs[i].fdout = prog->fdout;
		proglst = proglst->next;
	}
	return (progs);
}

void	checkpipes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->proglen)
	{
		if (d->progs[i].av)
		i++;
	}
}

void	lexing(t_data *d)
{
	int	i;

	i = 0;
	tokentoprog(d);
	printf("proglen %d\n", d->proglen);
	d->progs = lsttoprog(d, d->proglst);
	checkpipes(d);
}
