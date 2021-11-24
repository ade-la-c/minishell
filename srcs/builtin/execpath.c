/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:21 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 18:52:43 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_is_path(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	execve_with_path(int index, t_cmd *cmd, t_env_l *env)
{
	int			i;
	char		**split;
	char		*join;
	struct stat	*buf;

	i = 0;
	buf = malloc(sizeof(struct stat));
	if (!buf)
		exit_error("malloc failed");
	split = ft_split_slash(ft_getenv("PATH", env->list), ':');
	if (split == NULL)
	{
		join = ft_strdup("");
		execve(join, cmd[index].arg, env->list);
		error_errno(cmd, errno, 1, env);
	}
	while (split[i])
	{
		join = ft_strjoin(split[i], cmd[index].builtin);
		if (!join)
			exit_error("malloc failed");
		if (stat(join, buf) == 0)
		{
			free(buf);
			if (split)
				free_split_join(split, join);
			execve(join, cmd[index].arg, env->list);
		}
		i++;
	}
	free(buf);
	if (split)
		free_split_join(split, join);
}

static void	execpath_no_pipe(int i, t_cmd *cmd, t_env_l *env)
{
	if (cmd[i].fdout != 1)
		if (dup2(cmd[i].fdout, 1) == -1)
			exit_error("dup2 failed");
	if (cmd[i].fdin != 0)
		if (dup2(cmd[i].fdin, 0) == -1)
			exit_error("dup2 failed");
	if (check_is_path(cmd[i].builtin) == 1)
		execve(cmd[i].builtin, cmd[i].arg, env->list);
	else
		execve_with_path(i, cmd, env);
	if (cmd[i].arg[0])
	{
		write(2, SHELL_NAME": ", ft_strlen(SHELL_NAME) + 2);
		write(2, cmd[i].arg[0], ft_strlen(cmd[i].arg[0]));
		write(2, ": command not found\n", 20);
	}
	error_errno(cmd, errno, 1, env);
}

void	execpath_pipe(t_cmd *cmd, int i, t_env_l *env)
{
	if (cmd[i].fdout != 1)
		if (dup2(cmd[i].fdout, 1) == -1)
			exit_error("dup2 failed");
	if (cmd[i].fdin != 0)
		if (dup2(cmd[i].fdin, 0) == -1)
			exit_error("dup2 failed");
	if (check_is_path(cmd[i].builtin) == 1)
		execve(cmd[i].builtin, cmd[i].arg, env->list);
	else
		execve_with_path(i, cmd, env);
	if (cmd[i].arg[0])
	{
		write(2, SHELL_NAME": ", ft_strlen(SHELL_NAME) + 2);
		write(2, cmd[i].arg[0], ft_strlen(cmd[i].arg[0]));
		write(2, ": command not found\n", 20);
	}
	error_errno(cmd, errno, 1, env);
}

void	execpath(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	pid_t		pid;
	int			status;

	if (pipe == 0)
	{
		pid = fork();
		if (pid < 0)
			exit_error("fork failed");
		if (pid == 0)
			execpath_no_pipe(i, cmd, env);
		waitpid(pid, &status, 0);
		if (ft_strlen(cmd[i].arg[0]) != 0)
			retval = WEXITSTATUS(status);
		if (retval == 2)
			retval = 127;
	}
	else if (pipe == 1)
		execpath_pipe(cmd, i, env);
}
