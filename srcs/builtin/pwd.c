/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 01:47:45 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_pwd(int i, t_cmd *cmd, int pipe)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, PATH_MAX_SHELL);
	retval = 0;
	write (cmd[i].fdout, buff, ft_strlen(buff));
	write (cmd[i].fdout, "\n", 1);
	free(buff);
	if (pipe == 1)
		exit(1);
}
