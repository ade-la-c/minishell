/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:56 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/17 18:51:29 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	data_init(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("malloc error");
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
		line = readline("petit_shellito>");
		if (!line)
			exit_error("readline error");
		free(line);
		parsing(&data, line);
	}
	free(line);
	return (0);
}
