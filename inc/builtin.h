/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tristan <tristan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 00:56:16 by tristan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

char		**get_env_content(char **env_list);
void		execpath(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		execpath_pipe(t_cmd *cmd, int i, t_env_l *env);
void		builtin_echo(int index, t_cmd *cmd, int pipe);
void		builtin_cd(int index, t_cmd *cmd, int pipe, t_env_l *env);
void		builtin_pwd(int index, t_cmd *cmd, int pipe);
void		builtin_export(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_unset(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_env(int index, t_cmd *cmd, t_env_l *env, int pipe);
void		builtin_exit(int index, t_cmd *cmd, int pipe, t_env_l *env);

#endif