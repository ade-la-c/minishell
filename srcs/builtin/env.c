/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:10 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 18:19:11 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_env(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	int	env_index;

	env_index = 0;
	if (count_arg(cmd[i]) > 1)
	{	
		retval = 127;
		write(2, "env: ", 5);
		write(2, cmd[i].arg[1], ft_strlen(cmd[i].arg[1]));
		write(2, ": No such file or directory\n", 28);
		if (pipe == 1)
			exit(1);
		return ;
	}
	else
		retval = 0;
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
