/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:36 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 18:42:55 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_builtin(int i, t_cmd *cmd, t_env_l *env, int pipe)
{
	int		len;

	if (cmd[i].fdin == -1)
		return ;
	len = ft_strlen(cmd[i].builtin);
	if (ft_strncmp(cmd[i].builtin, "echo", len + 1) == 0)
		builtin_echo(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "cd", len + 1) == 0)
		builtin_cd(i, cmd, pipe, env);
	else if (ft_strncmp(cmd[i].builtin, "pwd", len + 1) == 0)
		builtin_pwd(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "export", len + 1) == 0)
		builtin_export(i, cmd, env, pipe);
	else if (ft_strncmp(cmd[i].builtin, "unset", len + 1) == 0)
		builtin_unset(i, cmd, env, pipe);
	else if (ft_strncmp(cmd[i].builtin, "env", len + 1) == 0)
		builtin_env(i, cmd, env, pipe);
	else if (ft_strncmp(cmd[i].builtin, "exit", len + 1) == 0)
		builtin_exit(i, cmd, pipe, env);
	else
	{
		execpath(i, cmd, env, pipe);
		return ;
	}
}

void	parse_cmd_array(t_cmd *cmd, t_env_l *env, int nb_cmd)
{
	int		i;
	int		nb_pipe;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i++].builtin == NULL)
			continue ;
		i--;
		nb_pipe = 0;
		if (cmd[i].pipe == 1)
		{
			while (cmd[i + nb_pipe].pipe == 1)
				nb_pipe++;
			if (nb_pipe == 1 && cmd[i + 1].builtin != NULL)
				i = single_pipe(i, cmd, env);
			else if (nb_pipe > 1)
				i = multi_pipe(i, cmd, env, nb_pipe);
			if (i >= nb_cmd)
				break ;
		}
		exec_builtin(i, cmd, env, 0);
		i++;
	}
}

void	cmd_loop(t_data *data, t_cmd *cmd, int *i, int j)
{
	while (data->progs[*i].av[j])
		j++;
	cmd[*i].arg = malloc(sizeof(char *) * (j + 1));
	if (!cmd[*i].arg)
		exit_error("malloc failed");
	if (data->progs[*i].av[0] == NULL)
		cmd[*i].builtin = NULL;
	else
	{
		cmd[*i].builtin = ft_strdup(data->progs[*i].av[0]);
		if (!(cmd[*i].builtin))
			exit_error("1 strdup failed");
	}
	j = -1;
	while (data->progs[*i].av[++j])
	{
		cmd[*i].arg[j] = ft_strdup(data->progs[*i].av[j]);
		if (!cmd[*i].arg[j])
			exit_error("2 strdup failed");
	}
	cmd[*i].arg[j] = NULL;
	cmd[*i].fdin = data->progs[*i].fdin;
	cmd[*i].fdout = data->progs[*i].fdout;
	cmd[*i].pipe = 1;
	*i += 1;
}

void	transfer_to_cmd(t_data *data, t_env_l *env)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd) * (data->proglen + 1));
	if (!cmd)
		exit_error("malloc failed");
	while (i < data->proglen)
	{
		cmd_loop(data, cmd, &i, 0);
	}
	cmd[i].builtin = NULL;
	cmd[i - 1].pipe = 0;
	parse_cmd_array(cmd, env, i);
	data->envp = envltoenvp(env);
	free(env);
	free_cmd(cmd);
}
