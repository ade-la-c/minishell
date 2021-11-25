/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:33:57 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 16:12:14 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	heredoc_proc(t_data *d, char *eof, int pipefd[2])
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline("> ");
		if (input == NULL || ft_strcmp(input, eof) == 0)
			break ;
		input = expandheredoc(d, input);
		write(pipefd[1], input, ft_strlen(input));
		write(pipefd[1], "\n", 1);
		free(input);
	}
	free(input);
	close(pipefd[1]);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

int	heredoc(t_data *d, char *eof)
{
	int		pipefd[2];
	pid_t	pid;
	int		retval;

	if (pipe(pipefd) < 0)
		exit_error("pipe failed");
	pid = fork();
	if (pid < 0)
		exit_error("fork failed");
	else if (pid == 0)
		heredoc_proc(d, eof, pipefd);
	else
	{
		waitpid(pid, &retval, 0);
		close(pipefd[1]);
		if (retval != EXIT_SUCCESS)
		{
			close(pipefd[0]);
			return (-1);
		}
	}
	return (pipefd[0]);
}

int	handleredirections(t_data *d, t_prog *p, int i)
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
