/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:22:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/20 20:43:42 by ade-la-c         ###   ########.fr       */
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

void	print_toklst(t_toklst *toklst, char *str)
{
	if (!toklst)
		return ;
	printf("{%s}", str);
	while (toklst->next)
	{
		printf("[%s]", toklst->content);
		toklst = toklst->next;
	}
	printf("[%s]", toklst->content);
	printf("\n");
}
