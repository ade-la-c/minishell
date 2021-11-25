/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:31:10 by tzerates          #+#    #+#             */
/*   Updated: 2021/11/25 18:22:57 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_s(char *cmd, char *s)
{
	if (ft_strclen(cmd, '=') == -1)
	{
		s = ft_strdup(cmd);
		if (!s)
			exit_error("substr failed");
	}
	else
	{
		s = ft_substr(cmd, 0, ft_strclen(cmd, '='));
		if (!s)
			exit_error("substr failed");
	}
	return (s);
}

char	*ft_tmp(char *cmd, char *tmp)
{
	if (ft_strclen(cmd, '=') == -1)
	{
		tmp = ft_substr(cmd, 0, ft_strlen(cmd));
		if (!tmp)
			exit_error("substr failed");
	}
	else
	{
		tmp = ft_substr(cmd, 0, ft_strclen(cmd, '='));
		if (!tmp)
			exit_error("substr failed");
	}
	return (tmp);
}

void	no_is_b(int i, char *join, t_env_l *env, t_cmd *cmd)
{
	join = ft_strdup("");
	if (!join)
		exit_error("strdup failed");
	execve(join, cmd[i].arg, env->list);
	error_errno(cmd, errno, 1, env);
}

void	splinter_shell(struct stat **buf, char **split, char *join, int xd)
{
	if (xd == 0)
	{
		free(*buf);
		if (split)
			free_split_join(split, join);
	}
	else
	{
		*buf = malloc(sizeof(struct stat));
		if (!*buf)
			exit_error("malloc failed");
	}
}
