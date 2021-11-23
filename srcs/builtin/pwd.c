/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:37:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/23 18:34:24 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_pwd(int i, t_cmd *cmd, int pipe)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, PATH_MAX_SHELL);
	g_err = 0;
	write (cmd[i].fdout, buff, ft_strlen(buff));
	write (cmd[i].fdout, "\n", 1);
	free(buff);
	if (pipe == 1)
		exit(1);
	return (0);		//TODO changer les valeurs de retour
}
