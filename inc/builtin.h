/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/23 18:30:18 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

char		**get_env_content(char **env_list);
void		execpath(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		execpath_pipe(t_cmd *cmd, int i, t_env_l *env);
int			builtin_echo(int index, t_cmd *cmd, int pipe);
int			builtin_cd(int index, t_cmd *cmd, int pipe, t_env_l *env);
int			builtin_pwd(int index, t_cmd *cmd, int pipe);
int			builtin_export(int index, t_cmd *cmd, t_env_l *env, int pipe);
int			builtin_unset(int index, t_cmd *cmd, t_env_l *env, int pipe);
int			builtin_env(int index, t_cmd *cmd, t_env_l *env, int pipe);
int			builtin_exit(int index, t_cmd *cmd, int pipe, t_env_l *env);

#endif