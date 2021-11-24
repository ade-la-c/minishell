/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:09:38 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 14:27:46 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_char(char **str, char c)
{
	char	*tmp;
	int		i;

	if (!*str)
		i = 0;
	else
		i = ft_strlen(*str);
	tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	if (*str)
	{
		ft_strlcpy(tmp, *str, i + 1);
		free(*str);
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	*str = tmp;
	// free(tmp);
	return (1);
}

char	*get_arg(char *arg)
{
	int		print;
	int		i;
	char	c;
	char	*tmp;

	print = 0;
	i = 0;
	c = 0;
	tmp = NULL;
	while (arg && arg[i])
	{
		if (arg[i] == '\\' && print == 0)
			print = 1;
		else if ((arg[i] == '\'' || arg[i] == '\"') && print == 0)
		{
			c = arg[i];
			print = 1;
		}
		else if (print == 1 && arg[i] == c)
			print = 0;
		else if (arg[i] == '$' && c != '\'')
			tmp = getenv(&arg[i]); // get $
		else
			add_char(&tmp, arg[i]);
		i++;
	}
	return (tmp);
}

int	heredoc(const char *eof)
{
	int			fd[2];
	char		*newline;
	char		*tmp;
	pid_t		pid;
	int			ret;

	if (pipe(fd) == -1)
		exit_error("pipe error");
	pid = fork();
	newline = NULL;
	if (pid < 0)
		exit_error("malloc failed");
	else if (pid == 0)
	{

		while (1)
		{
			// signal(SIGINT, &sigint_handler);
			signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT, SIG_DFL);
			if (newline)
			{
				free(newline);
				newline = NULL;
			}
			if (!eof)
				break ;
			newline = readline("> "); // soit ça soit "heredoc> "
			tmp = get_arg(newline); // Gérer les $$
			if (ft_strncmp(newline, eof, ft_strlen(eof)) == 0)
				break ;
			write(fd[1], newline, ft_strlen(newline));
			write(fd[1], "\n", 1);
		}
	}
	else
	{
		waitpid(pid, &ret, 0);
		close(fd[1]);
		if (ret != 0)
		{
			close(fd[0]);
			return (-1);
		}
	}
	// close(fd[1]);
	// free(newline);
	// free(tmp);
	return (fd[0]);
}
