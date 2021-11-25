/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:51:01 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 13:05:05 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strclen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

int	wait_forks(pid_t *pid, int nb_pipe)
{
	int	i;
	int	ret;

	i = 0;
	while (i < nb_pipe)
	{
		waitpid(pid[i], &ret, 0);
		i++;
	}
	msh_parser_set_retval(ret);
	free(pid);
	return (i);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	free_split_join(char **split, char *join)
{	
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (join)
		free(join);
}

void	init_token(t_env_l *env)
{
	char	**var_contents;
	int		i;

	env->token = malloc(sizeof(char **) * (nb_env(env->list) + 1));
	if (!env->token)
		exit_error("malloc failed");
	var_contents = get_env_content(env->list);
	i = 0;
	while (var_contents[i])
	{
		env->token[i] = ft_split(var_contents[i], ' ');
		if (!env->token[i])
			exit_error("split failed");
		i++;
	}
	env->token[i] = NULL;
	i = 0;
	while (var_contents[i])
	{
		free(var_contents[i]);
		i++;
	}
	free(var_contents);
}
