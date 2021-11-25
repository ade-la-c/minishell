/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:43:45 by tzerates          #+#    #+#             */
/*   Updated: 2021/11/25 17:44:49 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_point_point(char *pwd, char *path)
{
	pwd = getcwd(pwd, PATH_MAX_SHELL);
	if (!pwd)
		exit_error("getcwd failed");
	path = go_back(pwd);
	free(pwd);
	chdir(path);
	free(path);
}

int	vive_la_norme(t_env_l *env, int check)
{
	check = chdir(ft_getenv("HOME", env->list));
	if (check == -1)
	{
		write(2, SHELL_NAME": cd: HOME not set\n",
			ft_strlen(SHELL_NAME) + 20);
		g_glb[1] = 1;
	}
	check = 0;
	return (check);
}
