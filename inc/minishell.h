/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:54:12 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 18:10:47 by ade-la-c         ###   ########.fr       */
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
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "parsing.h"
# include "cmd.h"
# include "builtin.h"
# include "utils.h"

# define SHELL_NAME	"pequeño shell"

extern int		retval;

typedef struct s_token
{
	char			*content;
	int				type;
}	t_token;

typedef struct s_prog
{
	char			**av;
	int				fdin;
	int				fdout;
}	t_prog;

typedef struct s_data
{
	t_list			*toklst;
	t_token			*toks;
	int				toklen;
	t_list			*envlst;
	int				envlen;
	t_list			*proglst;
	t_prog			*progs;
	int				proglen;
	char			**envp;
}	t_data;

void				sigint_handler(int sig);

//==========================UTILS==========================//

void				exit_error(char *error);
int					is_esymbol(char c);
int					is_number(char *str, int n);
t_list				*new_token(char *content, int type);
int					remove_element(t_list **list, void *todelete);
char				**get_env(t_list *envlst, char *str, int len);
char				*strjoinfree(char *s1, char *s2, int x);

int					msh_parser_get_retval(void);
void				msh_parser_set_retval(int retval);

void				print_envlst(t_list *lst, char *str);
void				print_toklst(t_list *toklst, char *str);
void				print_tokens(t_data *data, t_token *tokens);
void				print_proglst(t_list *lst, char *str);

//=========================PARSING=========================//

int					parsing(t_data *data, char *line);
void				tokenizer(t_data *data, char *line);
void				wordexpansion(t_data *data);
int					lexing(t_data *data);

void				transfer_to_cmd(t_data *data, t_env_l *env);
t_env_l				*envptoenvl(t_data *data);
char				**envltoenvp(t_env_l *env);
void				ft_envpdup(t_data *data, char **envp, int bool);
void				getenvp(t_data *data);
char				**getenvp2(char *env);
int					heredoc(t_data *d, char *eof);
char				*expandheredoc(t_data *d, char *str);

//==========================FREEING==========================//

void				ft_free(t_data *data);
void				env_free(t_list *envlst);
void				free_tokel(void *ptr);
void				free_prog(void *ptr);
void				free_toks(t_data *data, t_token *toks);
void				free_null(void *ptr);
void				free_envel(void *content);

#endif
