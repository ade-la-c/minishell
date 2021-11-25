/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:38:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 19:18:22 by ade-la-c         ###   ########.fr       */
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
char		*ft_25(char *env_list, char *env_names);
void		ft_print_unset(char *s);
char		*ft_s(char *cmd, char *s);
char		*ft_tmp(char *cmd, char *tmp);
void		free_env_unset(char **tmp);
int			vive_la_norme(t_env_l *env, int check);
void		ft_point_point(char *pwd, char *path);
char		*go_back(char *pwd);
void		no_is_b(int i, char *join, t_env_l *env, t_cmd *cmd);
void		execve_with_path(int index, t_cmd *cmd, t_env_l *env);
void		splinter_shell(struct stat **buf, char **split, char *join, int xd);
void		free_env_unset(char **env_list);

#endif