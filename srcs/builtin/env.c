/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:10 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 01:41:10 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_env(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	int	env_index;

	env_index = 0;
	if (count_arg(cmd[i]) > 1)
		retval = 127;
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
