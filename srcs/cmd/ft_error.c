/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:46 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 17:41:50 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd)
	{
		if (cmd->arg)
		{
			while (cmd[i].builtin)
			{
				j = 0;
				while (cmd[i].arg[j])
					free(cmd[i].arg[j++]);
				free(cmd[i].arg);
				if (cmd[i].builtin)
					free(cmd[i].builtin);
				i++;
			}
		}
		free(cmd);
	}
}

void	exit_free_env(t_env_l *env, int nb)
{
	int	i;

	i = 0;
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	i = 0;
	exit(nb);
}

void	error_errno(t_cmd *cmd, int error_code, int exit_bool, t_env_l *env)
{
	(void)error_code;
	if (cmd)
		free_cmd(cmd);
	if (exit_bool == 1)
		exit_free_env(env, error_code);
}
