/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 01:35:41 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_glb = 0;

static void	data_init(t_data *data, char **envp)
{
	data->toklst = NULL;
	data->toklen = 0;
	data->envlst = NULL;
	data->envlen = 0;
	data->proglst = NULL;
	data->proglen = 0;
	ft_envpdup(data, envp, 0);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (g_glb == 0)
	{
		rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	readline_loop(t_data *data)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		g_glb = 0;
		tmp = readline("petit_shellito> ");
		g_glb = 1;
		if (!tmp)
			env_free(data->envlst);
		add_history(tmp);
		line = ft_strtrim(tmp, " ");
		free(tmp);
		if (!ft_strcmp(line, ""))
			continue ;
		getenvp(data);
		parsing(data, line);
		transfer_to_cmd(data, envptoenvl(data));
		ft_free(data);
		free(line);
	}
	ft_free(data);
	free(line);
	env_free(data->envlst);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 1 || av[1])
		exit_error("Error : minishell takes no arguments");
	data_init(&data, envp);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	readline_loop(&data);
	return (0);
}
