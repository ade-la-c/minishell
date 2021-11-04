/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:54:12 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/04 15:39:05 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "./parsing.h"

typedef struct s_token
{
	char			*content;
	int				type;
}	t_token;

typedef struct s_data
{
	t_list			*toklst;
	t_token			*toks;
	int				toklen;
	t_list			*envlst;
	int				envlen;
	char			**envp;
}	t_data;

//==========================UTILS==========================//

void				exit_error(char *error);
int					is_esymbol(char c);
int					is_number(char *str, int n);
t_list				*new_token(char *content, int type);
void				ft_removeelement(t_list **list, int type);
char				**get_env(t_list *envlst, char *str, int len);

void				print_lst(t_list *lst, char *str);
void				print_toklst(t_list *toklst, char *str);
void				print_tokens(t_data *data, t_token *tokens);

//=========================PARSING=========================//

void				lexing(t_data *data, char *line);
void				wordexpansion(t_data *data);
void				parsing(t_data *data, char *line);
void				print_tokens(t_data *data, t_token *tokens);

#endif
