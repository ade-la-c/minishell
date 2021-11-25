/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:31 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 15:42:07 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_print(t_cmd *cmd, int i, t_env_l *env)
{
	write(2, SHELL_NAME": exit: ", ft_strlen(SHELL_NAME) + 8);
	write(2, cmd[i].arg[1], ft_strlen(cmd[i].arg[1]));
	write(2, ": Numeric argument required\n", 28);
	exit_free_env(env, ft_atoi(cmd[i].arg[1]));
}

static void	ft_print2(t_cmd *cmd, int i)
{
	write(2, cmd[i].builtin, ft_strlen(cmd[i].builtin));
	write(2, "\n", 1);
}

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
		write(2, cmd[i].builtin, ft_strlen(cmd[i].builtin));
		write(2, "\n", 1);
		exit_free_env(env, 0);
	}
	if (size > 2 && ft_str_isdigit(cmd[i].arg[1]) == 1)
	{
		write (2, "exit\nToo many arguments\n", 25);
		g_glb[1] = 1;
		return ;
	}
	if (pipe == 0)
		ft_print2(cmd, i);
	if (ft_str_isdigit(cmd[i].arg[1]) == 0 || cmd[i].arg[1][0] == '\0')
		ft_print(cmd, i, env);
	if (cmd[i].arg[1][0] == '-')
		exit_free_env(env, 255 - (ft_atoi(cmd[i].arg[1]) * -1) + 1);
	else
		exit_free_env(env, ft_atoi(cmd[i].arg[1]));
}
