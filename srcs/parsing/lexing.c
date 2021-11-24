/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:50:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 20:03:41 by ade-la-c         ###   ########.fr       */
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
	if (!prog)
		exit_error("malloc failed");
	prog->av = ft_calloc(sizeof(char *), (i + 1));
	if (!prog->av)
		exit_error("calloc failed");
	prog->fdin = STDIN_FILENO;
	prog->fdout = STDOUT_FILENO;
	return (prog);
}

static int	handleredirections(t_data *d, t_prog *p, int i)
{
	if (d->toklen <= 1 || d->toks[i + 1].type != WORD)
	{
		write(STDERR_FILENO, "redirection needs a valid argument\n", 36);
		return (-1);
	}
	if (d->toks[i].type == MORE)
		p->fdout = open(d->toks[i + 1].content,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (d->toks[i].type == LESS)
		p->fdin = open(d->toks[i + 1].content, O_RDONLY);
	else if (d->toks[i].type == DMORE)
		p->fdout = open(d->toks[i + 1].content,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (d->toks[i].type == DLESS)
	{
		p->fdin = heredoc(d, d->toks[i + 1].content);
		if (p->fdin < 0)
			return (-1);
	}
	if (p->fdin < 0 || p->fdout < 0)
	{
		write(STDERR_FILENO, "redirection error\n", 19);
		return (-1);
	}
	return (0);
}

static int	tokentoprog(t_data *d)
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
		while (i < d->toklen && d->toks[i].type != PIPE)
		{
			if (d->toks[i].type >= MORE && d->toks[i].type <= DLESS)
			{
				if (handleredirections(d, prog, i) == -1)
					return (-1);
				i += 2;
			}
			else if (d->toks[i].type == WORD)
			{
				prog->av[j] = ft_strdup(d->toks[i++].content);
				if (!prog->av[j])
					exit_error("strdup failed");
				j++;
			}
		}
		if (i == d->toklen || d->toks[i++].type == PIPE)
		{
			el = ft_lstnew((void *)prog);
			if (!el)
				exit_error("lstnew failed");
			ft_lstadd_back(&(d->proglst), el);
			prog = NULL;
		}
	}
	return (0);
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

int	lexing(t_data *d)
{
	int	i;

	i = -1;
	if (tokentoprog(d) == -1)
		return (-1);
	d->proglen = ft_lstsize(d->proglst);
	d->progs = lsttoprog(d, d->proglst);
	ft_lstclear(&(d->toklst), free_tokel);
	while (++i < d->toklen)
		free(d->toks[i].content);
	free(d->toks);
	return (0);
}
