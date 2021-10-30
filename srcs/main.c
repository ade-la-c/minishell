/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/30 15:15:57 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_env(char *env)
{
	char	**strs;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	strs = malloc(sizeof(char *) * 2);
	if (!strs)
		exit_error("malloc failed");
	while (env[i] && env[i] != '=')
		i++;
	strs[0] = ft_substr(env, 0, i);
	strs[1] = ft_substr(&env[i + 1], 0, ft_strlen(&env[i + 1]));
	return (strs);
}

static void	get_envp(t_data *data, char **envp)
{
	int		i;
	char	**env;
	t_list	*el;

	i = 0;
	while (envp && envp[i])
	{
		env = get_env(envp[i]);
		el = ft_lstnew(env);
		if (!el)
			exit_error("get_envp");
		ft_lstadd_back(&(data->envlst), el);
		i++;
	}
}

	// print_lst(data->envlst, "envlst");

static void	data_init(t_data *data)
{
	data->toklst = NULL;
	data->envlst = NULL;
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	toklstclear(&(data->toklst), free);
	ft_lstclear(&(data->envlst), free);
	// free(data->toks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	*data;

	(void)av;
	if (ac != 1)
		exit_error("Error : minishell takes no arguments");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("malloc error");
	data_init(data);
	while (1)
	{
		line = readline("petit_shellito> ");
		if (!line || !ft_strcmp(line, "\n"))
			exit_error("readline error");
		add_history(line);
		get_envp(data, envp);
		parsing(data, line);
		ft_free(data);
	}
	ft_free(data);
	free(line);
	return (0);
}
