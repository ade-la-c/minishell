/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:22:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/01 14:32:58 by ade-la-c         ###   ########.fr       */
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

int	is_esymbol(char c)
{
	if (c == CHR_SPACE || c == CHR_PIPE || c == CHR_SQUOTE
		|| c == CHR_DQUOTE || c == CHR_LESS || c == CHR_MORE)
		return (1);
	return (0);
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
		toklst = toklst->next;
	}
	token = (t_token *)toklst->content;
	printf("[%s]", token->content);
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
