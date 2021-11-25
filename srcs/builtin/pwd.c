/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 14:30:10 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_pwd(int i, t_cmd *cmd, int pipe)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, PATH_MAX_SHELL);
	if (!buff)
			exit_error("malloc failed");
	g_glb[1] = 0;
	write (cmd[i].fdout, buff, ft_strlen(buff));
	write (cmd[i].fdout, "\n", 1);
	free(buff);
	if (pipe == 1)
		exit(1);
}
