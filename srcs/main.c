/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/19 20:45:02 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	data_init(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("malloc error");
	data->toklst = NULL;
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char	*line;
	t_data	data;

	data_init(&data);
	while (1)
	{
		line = readline("petit_shellito> ");//printf("%s\n", line);
		if (!line)
			exit_error("readline error");
		add_history(line);
		lexing(&data, line);
		free(line);
	}
	free(line);
	return (0);
}
