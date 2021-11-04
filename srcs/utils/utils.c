/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:22:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/04 17:05:45 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_error(char *error)
{
	ft_putstr("ERROR : ");
	ft_putstr(error);
	ft_putchar('\n');
	exit(0);
}

int		is_number(char *str, int n)
{
	int	i;

	i = -1;
	while (str[++i] && i < n)
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

t_list	*new_token(char *content, int type)
{
	t_token	*token;
	t_list	*el;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		exit_error("malloc failed");
	token->content = content;
	token->type = type;
	el = ft_lstnew((void *)token);
	return (el);
}

int	is_esymbol(char c)
{
	if (c == CHR_SPACE || c == CHR_PIPE || c == CHR_SQUOTE
		|| c == CHR_DQUOTE || c == CHR_LESS || c == CHR_MORE)
		return (1);
	return (0);
}

char	**get_env(t_list *envlst, char *str, int len)
{
	char	**strs;
	int		i;
	int		envlen;
	i = -1;
	if (len == 0)
		return (NULL);
	envlen = ft_lstsize(envlst);
	while (++i < envlen && envlst)
	{
		strs = (char **)envlst->content;
		// printf("%s = %s\n", strs[0], strs[1]);
		if (!ft_strncmp(str, strs[0], len))
			return (strs);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_removeelement(t_list **list, int type)
{
	t_list	*temp;
	t_list	*prev;
	t_token	*token;

	temp = *list;
	prev = NULL;
	token = (t_token *)temp->content;
	if (temp != NULL && token->type == type)
	{
		*list = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && token->type != type)
	{
		token = (t_token *)temp->content;
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp);
}

// provisoire

void	print_lst(t_list *lst, char *str)
{
	char	**strs;

	if (!lst)
		return ;
	printf("-%s-\n", str);
	while (lst->next)
	{
		strs = (char **)lst->content;
		printf("%s = %s\n", strs[0], strs[1]);
		lst = lst->next;
	}
	strs = (char **)lst->content;
	printf("%s = %s\n", strs[0], strs[1]);
	lst = lst->next;
}

void	print_toklst(t_list *toklst, char *str)
{
	t_token		*token;
	if (!toklst)
		return ;
	printf("{%s", str);
	while (toklst->next)
	{
		token = (t_token *)toklst->content;
		printf("[%s]", token->content);
		// printf("(%d)", token->type);
		toklst = toklst->next;
	}
	token = (t_token *)toklst->content;
	printf("[%s]", token->content);
	// printf("(%d)", token->type);
	printf("}\n");
}

void	print_tokens(t_data *data, t_token *tokens)
{
	int	i = 0;
	if (!tokens)
		return ;
	printf("printing : ");
	while (i < data->toklen)
	{
		printf("[%s](%d)", tokens[i].content, tokens[i].type);
		i++;
	}
	printf("\n");
}
