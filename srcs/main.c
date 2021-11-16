/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/17 00:31:36 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**getenvp2(char *env)
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

static void	getenvp(t_data *data, char **envp)
{
	int		i;
	char	**env;
	t_list	*el;

	i = 0;
	while (envp && envp[i])
	{
		env = getenvp2(envp[i]);
		el = ft_lstnew(env);
		if (!el)
			exit_error("get_envp");
		ft_lstadd_back(&(data->envlst), el);
		i++;
	}
	data->envlen = ft_lstsize(data->envlst);
}

	// print_lst(data->envlst, "envlst");

static void	data_init(t_data *data)
{
	data->toklst = NULL;
	data->envlst = NULL;
	data->proglst = NULL;
}

void	ft_free(t_data *data, int boolean)
{
	int		i;
	char	**strs;

	i = -1;
	ft_lstclear(&(data->toklst), free);
	ft_lstclear(&(data->proglst), free);
	while (++i < data->envlen && boolean == 1)
	{printf("%d\n", i);
		strs = (char **)data->envlst->content;
		free(strs[0]);
		free(strs[1]);
		data->envlst = data->envlst->next;
	}
	ft_lstclear(&(data->envlst), free);
	// free(data->toks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*tmp;
	t_data	*data;

	if (ac != 1 || av[1])
		exit_error("Error : minishell takes no arguments");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("malloc error");
	data_init(data);
	getenvp(data, envp);
	while (1)
	{
		tmp = readline("petit_shellito> ");
		if (!tmp)
			exit_error("readline error");
		add_history(tmp);
		line = ft_strtrim(tmp, " ");
		free(tmp);
		parsing(data, line);
		ft_free(data, 0);
	}
	ft_free(data, 1);
	free(line);
	return (0);
}
