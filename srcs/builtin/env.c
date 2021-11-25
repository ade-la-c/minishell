/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:10 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 14:29:56 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_print(t_cmd *cmd, int i)
{
	write(2, "env: ", 5);
	write(2, cmd[i].arg[1], ft_strlen(cmd[i].arg[1]));
	write(2, ": No such file or directory\n", 28);
}

void	builtin_env(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	int	env_index;

	env_index = 0;
	if (count_arg(cmd[i]) > 1)
	{	
		g_glb[1] = 127;
		ft_print(cmd, i);
		if (pipe == 1)
			exit(1);
		return ;
	}
	else
		g_glb[1] = 0;
	while (env->list[env_index])
	{
		if (ft_strclen(env->list[env_index], '=') != -1)
		{
			write(cmd[i].fdout, env->list[env_index],
				ft_strlen(env->list[env_index]));
			write(cmd[i].fdout, "\n", 1);
		}
		env_index++;
	}
	if (pipe == 1)
		exit(1);
}
