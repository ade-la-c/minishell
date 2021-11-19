/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:31 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/19 17:29:05 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_arg_size(int i, t_cmd *cmd)
{
	int	size;

	size = 0;
	while (cmd[i].arg[size])
		size++;
	return (size);
}

void	builtin_exit(int i, t_cmd *cmd, int pipe, t_env_l *env)
{
	int		size;

	size = get_arg_size(i, cmd);
	if (size == 1)
	{
		printf("%s\n", cmd[i].builtin);
		exit_free_env(env, 0); // VERIFIER CA FDP
	}
	if (size > 2)
	{
		write (2, "exit\nToo many arguments\n", 25);
		g_err = 1;
		return ;
	}
	if (ft_str_isdigit(cmd[i].arg[1]) == 1)
	{
		printf("%s\n", cmd[i].builtin);
		error_errno(cmd, ENOEXEC, 1, env);
	}
	if (pipe == 0)
		printf("%s\n", cmd[i].builtin);
	if (cmd[i].arg[1][0] == '-')
		exit_free_env(env, 255 - (ft_atoi(cmd[i].arg[1]) * -1) + 1);
	else
		exit_free_env(env, ft_atoi(cmd[i].arg[1]));
}
