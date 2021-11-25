/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:04 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 17:27:23 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_s(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] == '_')
				i++;
			else
				return (1);
			i--;
		}
		i++;
	}
	return (0);
}

char	**get_env_names(char **env_list)
{
	int		i;
	char	**env_names;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	if (!env_names)
		exit_error("malloc failed");
	while (env_list[i])
	{
		env_names[i] = ft_25(env_list[i], env_names[i]);
		i++;
	}
	env_names[i] = NULL;
	return (env_names);
}

int	var_exist(t_cmd cmd, int w_arg, char **env_list)
{
	int		i;
	char	**env_names;

	i = 0;
	env_names = get_env_names(env_list);
	if (check_s(cmd.arg[w_arg]))
		ft_print_unset(cmd.arg[w_arg]);
	while (env_names[i])
	{
		if (ft_strcmp(cmd.arg[w_arg], env_names[i]) == 0)
		{
			free_env(nb_env(env_names), env_names);
			return (i);
		}
		i++;
	}
	free_env(nb_env(env_names), env_names);
	return (-1);
}

void	del_env_var(t_env_l *env, int len, int to_del)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		exit_error("malloc failed");
	envdup_without(env->list, tmp, to_del);
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * len);
	if (!env->list)
		exit_error("malloc failed");
	envdup(env->list, tmp);
	free_env_unset(tmp);
}

void	builtin_unset(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	int	to_del;
	int	index;
	int	len;

	to_del = 0;
	index = 1;
	len = nb_env(env->list);
	g_glb[1] = 0;
	if (count_arg(cmd[i]) > 1)
	{
		while (index < count_arg(cmd[i]))
		{
			to_del = var_exist(cmd[i], index, env->list);
			if (to_del >= 0)
				del_env_var(env, len, to_del);
			index++;
		}
	}
	if (pipe == 1)
		exit(1);
}
