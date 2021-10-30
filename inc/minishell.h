/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:54:12 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/30 15:29:55 by ade-la-c         ###   ########.fr       */
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

// typedef struct s_toklst	t_toklst;

// struct s_toklst
// {
// 	char			*content;
// 	int				type;
// 	t_toklst		*next;
// };

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
	char			**envp;
}	t_data;

//==========================UTILS==========================//

// t_toklst			*toklstnew(void *content, int type);
// void				toklstadd_back(t_toklst **toklst, t_toklst *new);
// void				toklstclear(t_toklst **toklst, void (*del)(void *));
// void				toklstdelone(t_toklst *toklst, void (*del)(void *));
void				exit_error(char *error);
int					is_esymbol(char c);

void				print_lst(t_list *lst, char *str);
void				print_toklst(t_list *toklst, char *str);

//=========================PARSING=========================//

void				lexing(t_data *data, char *line);
void				parsing(t_data *data, char *line);
void				print_tokens(t_data *data, t_token *tokens);

#endif
