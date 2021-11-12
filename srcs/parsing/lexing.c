/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:50:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/12 16:23:23 by ade-la-c         ###   ########.fr       */
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
		if (d->toks[index + i].type >= MORE && d->toks[index + i].type <= DLESS)
			index += 2;
		i++;
	}
	prog = malloc(sizeof(t_prog));
	prog->av = ft_calloc(sizeof(char *), (i + 1));
	prog->fdin = STDIN_FILENO;
	prog->fdout = STDOUT_FILENO;
	return (prog);
}

static int	handleredirections(t_data *d, t_prog *prog, int i)
{
	if (d->toks[i + 1].type != WORD)
		exit_error("redirection needs a valid argument");
	if (d->toks[i].type == MORE)
	{
		prog->fdout = open(d->toks[i + 1].content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (prog->fdout < 0)
			exit_error("redirection error");
	}
	else if (d->toks[i].type == LESS)
	{
		prog->fdin = open(d->toks[i + 1].content, O_RDONLY);
		if (prog->fdin < 0)
			exit_error("redirection error");
	}
	else if (d->toks[i].type == DMORE)
	{
		prog->fdout = open(d->toks[i + 1].content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (prog->fdout < 0)
			exit_error("redirection error");
	}
	//TODO else if (d->toks[i].type == DLESS)
	return (2);
}

static void	tokentoprog(t_data *d)
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
			if (d->toks[i].type >= MORE && d->toks[i].type <= DLESS)
				i += handleredirections(d, prog, i);
			else
				prog->av[j++] = ft_strdup(d->toks[i++].content);
		}
		if (i == d->toklen || d->toks[i++].type == PIPE)
		{
			el = ft_lstnew((void *)prog);
			ft_lstadd_back(&(d->proglst), el);
			prog = NULL;
		}
	}
	d->proglen = ft_lstsize(d->proglst);
	// print_proglst(d->proglst, "imprimiendo");
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

// void	handlepipes(t_data *d)
// {
// 	int		i;
// 	t_prog	*prog;
// 	t_prog	*nextprog;
// 	int		pipefd[2];

// 	i = 0;
// 	while (i < d->proglen)
// 	{
// 		if (ft_strlen(*(d->progs[i].av)))
		
// 		i++;
// 	}
// }

void	lexing(t_data *d)
{
	int	i;

	i = 0;
	tokentoprog(d);
	d->progs = lsttoprog(d, d->proglst);
	// handlepipes(d);
}
