/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:21 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 19:15:46 by ade-la-c         ###   ########.fr       */
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

void	execve_with_path(int index, t_cmd *cmd, t_env_l *env)
{
	int			i;
	char		**split;
	char		*join;
	struct stat	*buf;

	i = 0;
	join = NULL;
	splinter_shell(&buf, NULL, join, 1);
	split = ft_split_slash(ft_getenv("PATH", env->list), ':');
	if (split == NULL)
		no_is_b(index, join, env, cmd);
	while (split[i])
	{
		join = strjoinfree(split[i], cmd[index].builtin, 0);
		if (stat(join, buf) == 0)
		{
			splinter_shell(&buf, split, NULL, 0);
			execve(join, cmd[index].arg, env->list);
			free(join);
			return ;
		}
		i++;
	}
	splinter_shell(&buf, split, join, 0);
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
			g_glb[1] = WEXITSTATUS(status);
		if (g_glb[1] == 2)
			g_glb[1] = 127;
	}
	else if (pipe == 1)
		execpath_pipe(cmd, i, env);
}
